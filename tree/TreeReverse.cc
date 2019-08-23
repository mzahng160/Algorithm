#include <iostream>
#include <stdlib.h>
#include <stack>
#include <queue>

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
	cout << root->data << "   ";
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

void midOrderTranverse(BiTree tree)
{
	if (NULL == tree)
		return;
	midOrderTranverse(tree->lchild);
	cout << tree->data << " ";
	midOrderTranverse(tree->rchild);
}

void midOrder(BiTree tree)
{
}

void PostOrderTraverse(BiTree root)
{
	if (root == NULL)
		return;

	PostOrderTraverse(root->lchild);
	PostOrderTraverse(root->rchild);

	cout << root->data << " ";
}

void PostOrder(BiTree pRoot)
{
	if (pRoot == NULL)
		return;

	stack<BiTree> s;
	BiTree cur = pRoot, pre = NULL;
	s.push(pRoot);

	while (!s.empty())
	{
		cur = s.top();

		if((cur->lchild == NULL && cur->rchild == NULL) ||
			((pre == cur->lchild || pre == cur->rchild) && pre != NULL))
		{
			cout << cur->data << " ";
			s.pop();
			pre = cur;
		}
		else
		{
			if (cur->rchild != NULL)
				s.push(cur->rchild);

			if (cur->lchild != NULL)
				s.push(cur->lchild);
		}
	}
}

int levelOrderTraveral(BiTree pRoot)
{
	queue<BiTree> q;
	BiTree front;

	if (pRoot == NULL)
		return 0;

	q.push(pRoot);

	int nextLevel = 0;
	int toBePrinted = 1;
	int level = -1;
	int sum = 0;

	while (!q.empty())
	{
		front = q.front();
		q.pop();
		cout << front->data << " ";

		if (front->lchild)
		{
			q.push(front->lchild);
			nextLevel++;
		}
			

		if (front->rchild)
		{
			q.push(front->rchild);
			nextLevel++;
		}			

		toBePrinted--;
		if (toBePrinted == 0)
		{
			sum += 2 << level;			 

			cout << endl;
			toBePrinted = nextLevel;
			nextLevel = 0;			

			++level;
		}		
	}

	return sum+1;
}

int getHeight(BiTree root) {
	if (root == NULL) {
		return 0;
	}
	int leftheight = getHeight(root->lchild);
	int rightheight = getHeight(root->rchild);
	return leftheight > rightheight ? (leftheight + 1):(rightheight + 1);
}


void SearchTreeNode(BiTree& root, BiTree& a)
{
	if (root == NULL)
		return;

	if (a->data > root->data)
	{		
		if (root->rchild == NULL)
		{
			cout << "[r-" << a->data << "]" << endl;
			root->rchild = a;
			return;
		}
		SearchTreeNode(root->rchild, a);
	}
	else if (a->data < root->data)
	{
		if (root->lchild == NULL)
		{
			cout << "[l-" << a->data << "]" << endl;
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
	
	//int a[] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93, 23, 27, 45, 21, 12 };
	//int a[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'M' };
	int a[] = { 5,2,3,4,1,6,7,8,9 };

	BiTree tree = NULL;

	int len = sizeof(a)/sizeof(a[0]);
	CreateOrderBinaryTree(tree, a, len);

	cout << "tree heigh " << getHeight(tree) << endl;

	cout << len << "levelOrderTraveral" << endl;
	cout << levelOrderTraveral(tree) << endl;


	cout <<  "PostOrderTraverse" << endl;
	PostOrderTraverse(tree);
	cout << "PostOrder" << endl;
	PostOrder(tree);
	
}