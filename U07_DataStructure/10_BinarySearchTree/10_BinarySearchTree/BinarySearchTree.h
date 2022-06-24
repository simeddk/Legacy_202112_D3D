#pragma once

template<typename T>
class BinarySearchTree
{
public:
	struct Node;

public:
	BinarySearchTree() {}

	~BinarySearchTree()
	{
		Destroy(root);
	}

	void Insert(Node** parent, Node* child)
	{
		if ((*parent)->Data < child->Data)
		{
			if ((*parent)->Right == nullptr)
				(*parent)->Right = child;
			else
				Insert(&(*parent)->Right, child);
		}
		else if ((*parent)->Data > child->Data)
		{
			if ((*parent)->Left == nullptr)
				(*parent)->Left = child;
			else
				Insert(&(*parent)->Left, child);
		}
	}

	Node* SearchMinValue(Node* node)
	{
		if (node == nullptr) return nullptr;

		if (node->Left == nullptr)
			return node;
		
		return SearchMinValue(node->Left);
	}

	Node* Remove(Node* node, Node* parent, T data)
	{
		Node* remove = nullptr;

		if (node == nullptr) return nullptr;

		if (node->Data > data)
			remove = Remove(node->Left, node, data);
		else if (node->Data < data)
			remove = Remove(node->Right, node, data);
		
		//지울 노드를 찾은 경우
		else
		{
			remove = node;

			//Leaf인 경우
			if (node->Left == nullptr && node->Right == nullptr)
			{
				if (parent->Left == node)
					parent->Left = nullptr;
				else
					parent->Right = nullptr;
			}
			//자식이 있는 경우
			else
			{
				//자식이 2개인 경우
				if (node->Left != nullptr && node->Right != nullptr)
				{
					Node* minNode = SearchMinValue(node->Right);

					minNode = Remove(node, nullptr, minNode->Data);
					node->Data = minNode->Data;

					return minNode;
				}
				
				//자식이 1개인 경우
				else
				{
					Node* temp = nullptr;

					if (node->Left != nullptr)
						temp = node->Left;
					else
						temp = node->Right;

					if (parent->Left == node)
						parent->Left = temp;
					else
						parent->Right = temp;
				}

			}//자식이 있는 경우


		}//지울놈을 찾은 경우

		return remove;
	}

	Node* Search(Node* node, T data, int& depth)
	{
		if (node == nullptr) return nullptr;
		depth++;

		if (node->Data == data)
			return node;
		else if (node->Data > data)
			return Search(node->Left, data, depth);
		else if (node->Data < data)
			return Search(node->Right, data, depth);

		return nullptr;
	}

	void InOrder(Node* node, int depth)
	{
		if (node == nullptr) return;
		depth++;

		InOrder(node->Left, depth);
		printf(" [%d]%d", depth, node->Data);
		InOrder(node->Right, depth);
	}

public:
	void Root(Node* node) { root = node; }

private:
	void Destroy(Node* node)
	{
		if (node == nullptr) return;

		Destroy(node->Left);
		Destroy(node->Right);
		DestroyNode(node);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Left = node->Right = nullptr;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

private:
	struct Node
	{
		T Data;
		Node* Left;
		Node* Right;
	};

private:
	Node* root;
};