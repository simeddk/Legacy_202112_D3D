#pragma once

template<typename ValueType>
class Chaining
{
public:
	struct Node;
	typedef Node* List;

public:
	Chaining(int size)
		: size(size)
	{
		table = new List[size];
		memset(table, 0, sizeof(List) * size);
	}

private:
	int Hash(const char* key, int keyLength)
	{
		int hash = 0;

		for (int i = 0; i < keyLength; i++)
			hash = (hash << 3) + key[i];

		return hash % size;
	}

public:
	void Set(const char* key, ValueType value)
	{
		int hash = Hash(key, strlen(key));

		printf("Table[%d] = %d\n", hash, value);

		Node* newNode = CreateNode(key, value);
		if (table[hash] != nullptr)
		{
			Node* prev = table[hash];
			newNode->Next = prev;
			table[hash] = newNode;

			printf("경고! %s 가 [%d] 인덱스를 중복 참조합니다 -> 값 : %d\n"
				,key, hash, value);
		}
		else
			table[hash] = newNode;
	}

	ValueType Get(const char* key)
	{
		int hash = Hash(key, strlen(key));

		List hashList = table[hash];
		List target = nullptr;

		if (hashList == nullptr) return ValueType();

		while (true)
		{
			if (strcmp(hashList->Key, key) == 0)
			{
				target = hashList;
				break;
			}

			if (hashList->Next == nullptr)
				return ValueType();
			else
				hashList = hashList->Next;
		}


		return target->Value;
	}


public:
	static Node* CreateNode(const char* key, ValueType value)
	{
		Node* node = new Node();

		node->Key = (char*)malloc(sizeof(key) * strlen(key + 1));
		strcpy_s(node->Key, sizeof(key), key);

		node->Value = value;
		node->Next = nullptr;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		free(node->Key);

		delete node;
		node = nullptr;
	}

private:
	struct Node
	{
		char* Key;
		ValueType Value;

		Node* Next;
	};

private:
	List* table;
	int size;
};