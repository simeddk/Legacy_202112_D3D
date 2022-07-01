#pragma once

template<typename T>
class DisjointSet
{
public:
	struct Set;

public:
	static Set* CreateSet(T data)
	{
		Set* set = new Set();
		set->Data = data;
		set->Parent = nullptr;

		return set;
	}

	static void DestroySet(Set* set)
	{
		delete set;
		set = nullptr;
	}

	static Set* FindSet(Set* set)
	{
		while (set->Parent != nullptr)
			set = set->Parent;

		return set;
	}

	static void UinionSet(Set* parent, Set* set)
	{
		set = FindSet(set);
		set->Parent = parent;
	}

	static bool IsSameGroup(Set* set1, Set* set2)
	{
		return FindSet(set1) == FindSet(set2);
	}

private:
	struct Set
	{
		T Data;
		Set* Parent;
	};
};