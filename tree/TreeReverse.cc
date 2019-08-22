#include <iostream>
#include <stdlib.h>
#include <stack>

using namespace std;

typedef int ElemType;

typedef struct _BiTNode
{
	ElemType data;
	struct _BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct _Node
{
	BiTree btnode;
	bool isfirst;
}Node, *node;

void PreOrderTraverse(BiTree root)
{
	if (root == NULL)
		return;
	cout << root->data << endl;
	PreOrderTraverse(root->lchild);
	PreOrderTraverse(root->rchild);
}

void PreOrder(BiTree pRoot)
{
	if (pRoot == NULL)
		return;

	BiTree p = pRoot;
	stack<BiTree> s;

	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);
			cout << p->data << " ";
			p = p->lchild;
		}

		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}

void SearchTreeNode(BiTree& root, BiTree& a)
{
	if (root == NULL)
		return;
	if (a->data > root->data)
	{
		cout << "[r-" << a->data << "]" << endl;
		if (root->rchild == NULL)
		{
			root->rchild = a;
			return;
		}
		SearchTreeNode(root->rchild, a);
	}
	else if (a->data < root->data)
	{
		cout << "[l-" << a->data << "]" << endl;

		if (root->lchild == NULL)
		{
			root->lchild = a;
			return;
		}
		SearchTreeNode(root->lchild, a);
	}
}

void InsertNode(BiTree& tree, BiTree& s)
{
	if (tree == NULL)
		tree = s;
	else
		SearchTreeNode(tree, s);
}

void CreateOrderBinaryTree(BiTree& tree, int* a, int len)
{
	for (int i = 0; i < len; i++)
	{
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = a[i];
		s->lchild = NULL;
		s->rchild = NULL;

		InsertNode(tree, s);
	}
}

int main()
{
	
	int a[] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93, 23, 27, 45, 21, 12 };

	BiTree tree = NULL;

	int len = sizeof(a)/sizeof(int);
	CreateOrderBinaryTree(tree, a, len);

	cout << "PreOrderTraverse" << endl;
	PreOrderTraverse(tree);
}