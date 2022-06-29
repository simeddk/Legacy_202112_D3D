#pragma once

/*
# Basic Rule
규칙1. 모든 노드는 Red이거나 Black이어야 함
규칙2. root 노드는 항상 Black
규칙3. leaf(nil)노드는 항상 Black
규칙4. 어느 nil노드에서 출발하던, root까지 가는 Black의 개수가 동일해야 함
규칙5. Red의 자식에는 항상 Black만 들어올 수 있음
*/

template<typename T>
class RBTree
{
public:
	struct Node;
	enum class Color { Red, Black };

public:
	RBTree()
	{
		nil = CreateNode(0);
	}

	Node* Search(Node* node, T data)
	{
		if (node == nullptr) return nullptr;

		if (node->Data > data)
			return Search(node->Left, data);
		else if (node->Data < data)
			return Search(node->Right, data);

		return node;
	}

	Node* SearchMinNode(Node* node)
	{
		if (node == nullptr) return nullptr;

		if (node->Left == nil)
			return node;

		return SearchMinNode(node->Left);
	}

private:
	void InsertInternal(Node** node, Node* newNode)
	{
		if (*node == nullptr)
			*node = newNode;

		if ((*node)->Data < newNode->Data)
		{
			if ((*node)->Right == nil)
			{
				(*node)->Right = newNode;
				newNode->Parent = *node;
			}
			else
				InsertInternal(&(*node)->Right, newNode);
		}
		else if ((*node)->Data > newNode->Data)
		{
			if ((*node)->Left == nil)
			{
				(*node)->Left = newNode;
				newNode->Parent = *node;
			}
			else
				InsertInternal(&(*node)->Left, newNode);
		}
	}

	void RebuildInsert(Node** root, Node* node)
	{
		while (node != (*root) && node->Parent->Color == Color::Red)
		{
			//위반노드의 부모가 Left인 경우
			if (node->Parent == node->Parent->Parent->Left)
			{
				Node* uncle = node->Parent->Parent->Right;

				//삽입 규칙1.(삼촌이 Red인 경우 -> 부모와 삼촌을 Black, 할아버지를 Red로)
				if (uncle->Color == Color::Red)
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else //삼촌이 Black인 경우
				{
					//삽입규칙2.(삼촌이 Black, node가 Right에 붙은 경우)
					if (node == node->Parent->Right)
					{
						node = node->Parent;
						RotateLeft(root, node);
					}
					
					//삽입규칙3.(삼촌이 Black, node가 Left에 붙은 경우)
					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;
					RotateRight(root, node->Parent->Parent);
				}
			} 
			//위반노드의 부모가 Right인 경우
			else
			{
				Node* uncle = node->Parent->Parent->Left;

				//삽입 규칙1.(삼촌이 Red인 경우 -> 부모와 삼촌을 Black, 할아버지를 Red로)
				if (uncle->Color == Color::Red)
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else //삼촌이 Black인 경우
				{
					//삽입규칙2.(삼촌이 Black, node가 Right에 붙은 경우)
					if (node == node->Parent->Left)
					{
						node = node->Parent;
						RotateRight(root, node);
					}

					//삽입규칙3.(삼촌이 Black, node가 Left에 붙은 경우)
					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;
					RotateLeft(root, node->Parent->Parent);
				}
			}
		}

		(*root)->Color = Color::Black;
	}

public:
	void Insert(Node** node, Node* newNode)
	{
		InsertInternal(node, newNode);

		/*
		삽입 규칙은 newNode의 부모가 Red인 경우에만 적용(Red밑에 Red가 붙는 상황)
		삽입 규칙1. Uncle이 Red인 경우, Parent->Black, Uncle->Black, Grand->Red
		삽입 규칙2. Uncle이 Black이고, newNode가 Right인 경우 -> Parent를 기준으로 좌회전
		삽입 규칙3. Uncle이 Black이고, newNode가 Left인 경우 
			-> Parent->Balck, Grand->Red, Grand를 기준으로 우회전
		*/

		newNode->Color = Color::Red;
		newNode->Left = nil;
		newNode->Right = nil;

		RebuildInsert(node, newNode);
	}

	//삭제 규칙(5가지)
	//(1) 형제가 Red인 경우 -> 부모를 Red로, 형제를 Black -> 왼쪽에 있었다면 부모 기준 좌회전, 오른쪽에 있었다면 부모 기준 우회전
	//(2) 형제가 Black인 경우 -> 아래 세가지로 파생
	//(2-1) 형제의 양쪽 자식이 모두 Black인 경우 -> 형제를 Red로
	//(2-2) 형제의 왼쪽 자식만 Red -> 형제의 왼쪽 자식을 Black, 형제를 Red, 형제를 기준으로 우회전
	//(2-3) 형제의 오른쪽 자식만 Red -> 부모를 Black으로, 형제의 오른쪽을 Black으로, 부모 기준 좌회전


	void RotateRight(Node** root, Node* pivot)
	{
		Node* left = pivot->Left;
		pivot->Left = left->Right;

		if (left->Right != nil)
			left->Right->Parent = pivot;

		left->Parent = pivot->Parent;

		if (pivot->Parent != nullptr)
		{
			if (pivot == pivot->Parent->Left)
				pivot->Parent->Left = left;
			else
				pivot->Parent->Right = left;
		}
		else
			*root = left;

		left->Right = pivot;

		pivot->Parent = left;
	}

	void RotateLeft(Node** root, Node* pivot)
	{
		Node* right = pivot->Right;
		pivot->Right = right->Left;

		if (right->Left != nil)
			right->Left->Parent = pivot;

		right->Parent = pivot->Parent;

		if (pivot->Parent != nullptr)
		{
			if (pivot == pivot->Parent->Left)
				pivot->Parent->Left = right;
			else
				pivot->Parent->Right = right;
		}
		else
			*root = right;

		right->Left = pivot;

		pivot->Parent = right;
	}

	void Print(Node* node, int depth)
	{
		if (node == nullptr || node == nil) return;

		if (node->Color == Color::Red)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		else 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		T parent = -1;
		char d = 'X';
		if (node->Parent != nullptr)
		{
			parent = node->Parent->Data;

			if (node->Parent->Left == node)
				d = 'L';
			else
				d = 'R';
		}

		string depthBar = "";

		for (int i = 0; i < depth; i++)
			depthBar += " - ";

		printf("%s %d [%c,%d]\n", depthBar.c_str(), node->Data, d, parent);

		Print(node->Left, depth + 1);
		Print(node->Right, depth + 1);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Parent = nullptr;
		node->Left = node->Right = nullptr;
		node->Color = Color::Black;
		node->Data = data;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

public:
	struct Node
	{
		Node* Parent;
		Node* Left;
		Node* Right;
		Color Color;

		T Data;
	};

private:
	Node* nil;
};