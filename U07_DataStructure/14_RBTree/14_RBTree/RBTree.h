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
	}

	void RotateRight(Node** root, Node* pivot)
	{
		Node* left = pivot->Left;
		pivot->Left = left->Right;

		if (left->Right != nil)
			left->Right->Parent = pivot;

		if (parent->Parent != nullptr)
		{
			if (parent == parent->Parent->Left)
				parent->Parent->Left = left;
			else
				parent->Parent->Right = left;
		}
		else
			*pivot = left;
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