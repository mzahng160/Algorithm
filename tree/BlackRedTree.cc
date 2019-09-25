#include "BlackRedTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

BlackRedTree::BlackRedTree()
{
	pRoot = nullptr;
}

BlackRedTree::~BlackRedTree()
{
}

#if 0
enum unbalance_type get_unbalance_type(NodePtr p, int val)
{
	if (val > p->value)
	{
		if (val > p->r_child->value)
			return TYPE_RR;
		return TYPE_RL;
	}
	else
	{
		if (val > p->l_child->value)
			return TYPE_LR;
		return TYPE_LL;
	}
}
#endif

int main()
{
//	std::vector<int> intVec{ 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
	std::vector<int> intVec{ 12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17};

	BlackRedTree rbTree;

	for (auto i : intVec)
		rbTree.insert(i);

	rbTree.printTree_2();

	for (auto i : intVec)
	{
		rbTree.deleteNode(i);
		rbTree.printTree_2();
	}		
	return 0;
}