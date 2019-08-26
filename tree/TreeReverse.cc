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

void midOrder(BiTree pRoot)
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
			
			p = p->lchild;
		}

		if (!s.empty())
		{
			p = s.top();
			cout << p->data << " ";
			s.pop();
			p = p->rchild;
		}
	}
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

/*
 * this function has not been written finsih, cannot print
 * all data in tree, it will be finish later.
 */
void printTree(BiTree pRoot, int dataPos, int len)
{
	queue<BiTree> q;
	BiTree front;

	if (pRoot == NULL)
		return ;

	q.push(pRoot);

	int nextLevel = 0;
	int toBePrinted = 1;
	int level = -1;
	int sum = 0;
	int dt = 0;
	for (int i = 0; i < len/2; i++)
	{
		cout << "*";
	}

	while (!q.empty())
	{
		front = q.front();
		q.pop();

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

		cout << front->data;

		toBePrinted--;

		if (toBePrinted == 0)
		{
			sum = 2 << (level+1);
			dt = (len + 1) / sum;

			cout << endl;
			toBePrinted = nextLevel;
			nextLevel = 0;

			++level;
		}

	}
}

string getSpace(int num)
{
	string buf;
	for (int i = 0; i < num; i++)
	{
		buf.append(" ");
	}

	return buf;
}

void printInOrder(BiTree pRoot, int height, string to, int len)
{
	if (pRoot == NULL)
		return;

	printInOrder(pRoot->rchild, height + 1, "v", len);
	string val;
	val.append(to);
	val.append(std::to_string(pRoot->data).c_str());
	val.append(to);

	int lenM = val.length();
	int lenL = (len - lenM) / 2;
	int lenR = len - lenM - lenL;
	val = getSpace(lenL) + val + getSpace(lenR);
	cout << getSpace(height*len) + val << endl;
	printInOrder(pRoot->lchild, height + 1, "^", len);
}

void printTree_2(BiTree pRoot)
{
	cout << "Binary tree" << endl;
	printInOrder(pRoot, 0, "H", 17);
	cout << endl;
}

void levelOrderTraveral(BiTree pRoot)
{
	queue<BiTree> q;
	BiTree front;

	if (pRoot == NULL)
		return ;

	q.push(pRoot);

	int nextLevel = 0;
	int toBePrinted = 1;
	int level = -1;

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
			cout << endl;
			toBePrinted = nextLevel;
			nextLevel = 0;			

			++level;
		}		
	}	
}

ElemType GetMinNode(BiTree pRoot)
{
	if (pRoot)
	{
		while (pRoot&&pRoot->lchild != NULL)
		{
			pRoot = pRoot->lchild;
		}
		return pRoot->data;
	}
}

ElemType GetMaxNode(BiTree pRoot)
{
	if (pRoot)
	{
		while (pRoot&&pRoot->rchild != NULL)
		{
			pRoot = pRoot->rchild;
		}
		return pRoot->data;
	}
}

bool Search(BiTree pRoot, ElemType key)
{
	if (pRoot == NULL)
		return false;
	if (key < pRoot->data)
		return Search(pRoot->lchild, key);
	else if (key > pRoot->data)
		return Search(pRoot->rchild, key);
	else
		return true;
}

void removeNode(BiTree& pRoot, ElemType key)
{
	
	if (pRoot == NULL)
		return;
	if (key < pRoot->data)
	{
		removeNode(pRoot->lchild, key);
	}
	else if (key > pRoot->data)
	{
		removeNode(pRoot->rchild, key);
	}
	else 
	{
		if (pRoot->rchild == NULL && pRoot->lchild == NULL)
		{
			cout << "****"<< pRoot->data << endl;
			pRoot = NULL;
			return;
		}
		else if (pRoot->lchild == NULL)
		{			
			pRoot = pRoot->rchild;
		}
		else if (pRoot->rchild == NULL)
		{
			pRoot = pRoot->lchild;
		}

		pRoot->data = GetMinNode(pRoot);

		removeNode(pRoot->rchild, pRoot->data);
	}
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

	cout << sizeof(long) << " " << sizeof(int) << " " << sizeof(char) << " " << sizeof(double) << " " << sizeof(float) << endl;
	
	//int a[] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93, 23, 27, 45, 21, 12 };
	//int a[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'M' };
	int a[] = { 5,2,3,4,1,6,7,8,9 };

	BiTree tree = NULL;

	int len = sizeof(a)/sizeof(a[0]);
	CreateOrderBinaryTree(tree, a, len);

	int treeHeight = getHeight(tree);
	cout << "tree heigh " << treeHeight << endl;	
#if 0
	int sum = 0;
	for (int i = 0; i < treeHeight-1; i++)
		sum += 2 << i;
	sum += 1;
	
	printTree(tree, sum/2, sum);
	cout << endl;
#endif

	cout << "levelOrderTraveral" << endl;
	levelOrderTraveral(tree);
	cout << endl;

	/******************************/
	cout << "PreOrderTraverse" << endl;
	PreOrderTraverse(tree);
	cout << endl;

	cout << "PreOrder" << endl;
	PreOrder(tree);
	cout << endl;

	/******************************/
	cout <<  "PostOrderTraverse" << endl;
	PostOrderTraverse(tree);
	cout << endl;

	cout << "PostOrder" << endl;
	PostOrder(tree);
	cout << endl;

	/******************************/
	cout << "midOrderTranverse" << endl;
	midOrderTranverse(tree);
	cout << endl;

	cout << "midOrder" << endl;
	midOrder(tree);	
	cout << endl;

	/******************************/
	cout << "min data" << endl;
	cout << GetMinNode(tree) << endl;

	cout << "max data" << endl;
	cout << GetMaxNode(tree) << endl;

	/******************************/	
	cout << "max data" << endl;
	cout << (Search(tree, a[8]) ? "true":"false") << endl;


	/******************************/
	cout << "delete" << endl;
	removeNode(tree, a[5]);
	levelOrderTraveral(tree);	
	cout << endl;

	printTree_2(tree);
}