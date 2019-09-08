#include "AVLTree.h"
#include <iostream>
#include <vector>

using namespace std;

AVLTree::AVLTree()
{
	pRoot = nullptr;
}

void AVLTree::insert(int key)
{
	pRoot = insert_real(key, pRoot);
}

int AVLTree::get_height(Node* p)
{
	if (p == nullptr)
		return 0;

	return p->height;
}

int AVLTree::get_balance(Node* p)
{
	if (p == nullptr)
		return 0;
	return get_height(p->left) - get_height(p->right);
}

Node* AVLTree::insert_real(int key, Node* p)
{
	if (p == nullptr)
	{
		Node* k = new Node(key);
		cout << "create new node" << endl;
		return k;
	}
		
	if (key < p->key)
		p->left = insert_real(key, p->left);
	else if (key > p->key)
		p->right = insert_real(key, p->right);
	else
		return p;
	
	p->height = max(get_height(p->left), get_height(p->right)) + 1;
	int balance = get_balance(p);

	if (balance > 1 && get_balance(p->left) > 0)
		return ll_ratate(p);

	if (balance < -1 && get_balance(p->right) < 0)
		return rr_ratate(p);

	if (balance > 1 && get_balance(p->left) < 0)
		return lr_ratate(p);

	if (balance < -1 && get_balance(p->right) > 0)
		return rl_ratate(p);

	return p;
}


Node* AVLTree::ll_ratate(Node* p)
{
	Node* k = p->left;
	p->left = k->right;
	k->right = p;

	p->height = max(get_height(p->left), get_height(p->right)) + 1;
	k->height = max(get_height(k->left), get_height(k->right)) + 1;

	return k;
}
Node* AVLTree::rr_ratate(Node* p)
{
	Node* k = p->right;
	p->right = k->left;
	k->left = p;

	p->height = max(get_height(p->left), get_height(p->right)) + 1;
	k->height = max(get_height(k->left), get_height(k->right)) + 1;	

	return k;
}

Node* AVLTree::lr_ratate(Node* p)
{
	Node *k = p->left;
	p->left = rr_ratate(k);
	return ll_ratate(p);
}

Node* AVLTree::rl_ratate(Node* p)
{
	Node *k = p->right;
	p->right = ll_ratate(k);
	return rr_ratate(p);
}

void AVLTree::destory(Node* p)
{
	if (p == nullptr)
		return;
	destory(p->left);
	destory(p->right);

	delete p;
	p = nullptr;
}

void AVLTree::print()
{
	Node* p = pRoot;
	cout << "preorder" << endl;
	preorder(p);
	cout << endl;

	cout << "midorder" << endl;
	midorder(p);
	cout << endl;
	
	cout << "postorder" << endl;
	postorder(p);
	cout << endl;
}

void AVLTree::preorder(Node* p)
{
	if (p != nullptr)
	{
		cout << "[" << p->key << "]";
		preorder(p->left);
		preorder(p->right);
	}
	
}
void AVLTree::midorder(Node* p)
{
	if (p != nullptr)
	{
		midorder(p->left);
		cout << "[" << p->key << "]";
		midorder(p->right);
	}	
}

void AVLTree::postorder(Node* p)
{
	if (p != nullptr)
	{
		midorder(p->left);		
		midorder(p->right);
		cout << "[" << p->key << "]";
	}
}

string AVLTree::getSpace(int num)
{
	string buf;
	for (int i = 0; i < num; i++)
	{
		buf.append(" ");
	}
	return buf;
}

void AVLTree::printInOrder(Node* p, int height, string to, int len)
{
	if (p == NULL)
		return;

	printInOrder(p->right, height + 1, "v", len);
	string val;
	val.append(to);
	val.append(std::to_string(p->key).c_str());
	val.append(to);

	int lenM = val.length();
	int lenL = (len - lenM) / 2;
	int lenR = len - lenM - lenL;
	val = getSpace(lenL) + val + getSpace(lenR);
	cout << getSpace(height*len) + val << endl;
	printInOrder(p->left, height + 1, "^", len);
}

void AVLTree::printTree_2()
{
	Node* p = pRoot;
	cout << "Binary tree" << endl;
	printInOrder(p, 0, "H", 17);
	cout << endl;
}

Node* AVLTree::find(int key)
{
	return find_real(key, pRoot->left);
}

Node* AVLTree::find_real(int key, Node*& p)
{
	if (p == nullptr)
		return p;

	if (key < p->key)
		find_real(key, p->left);
	else if (key > p->key)
		find_real(key, p->right);
	else
		return p;
}

Node* AVLTree::GetMinNode(Node* pRoot)
{
	if (pRoot != NULL)
	{
		while (pRoot&&pRoot->left != NULL)
			pRoot = pRoot->left;

		return pRoot;
	}
	else
	{
		return NULL;
	}
}
Node* AVLTree::GetMaxNode(Node* pRoot)
{
	if (pRoot != NULL)
	{
		while (pRoot&&pRoot->right != NULL)
			pRoot = pRoot->right;

		return pRoot;
	}
	else
	{
		return NULL;
	}
}

Node* AVLTree::remove(Node* p, int key)
{
	if (p == NULL)
		return NULL;

	if (key < p->key)	//look for node
	{
		p->left = remove(p->left, key);
		// adjust tree balance if it is unbalance after remove left node
		if (get_height(p->right) - get_height(p->left) == 2)
		{
			Node* pTmp = p->right;
			if (get_height(pTmp->left) < get_height(pTmp->right))
				p = rr_ratate(p);
			else
				p = rl_ratate(p);
		}
	}
	else if (key > p->key)
	{
		p->right = remove(p->right, key);

		// adjust tree balance if it is unbalance after remove right node
		if (get_height(p->left) - get_height(p->right) == 2)
		{
			Node* pTmp = p->left;
			if (get_height(pTmp->right) > get_height(pTmp->left))
				p = lr_ratate(p);
			else
				p = ll_ratate(p);
		}
	}
	else  // find node should be removed
	{		
		if ((p->left != NULL) && (p->right != NULL))
		{
			if (get_height(p->left) > get_height(p->right))
			{				
				Node* pTmp = GetMaxNode(p->left);
				p->key = pTmp->key;
				p->left = remove(p->left, pTmp->key);
			}
			else
			{
				Node* pTmp = GetMinNode(p->right);
				p->key = pTmp->key;				
				p->right = remove(p->right, pTmp->key);
			}
		}
		else
		{			
			Node* pTmp = p;
			p = (p->left != NULL) ? p->left : p->right;
			delete pTmp;
		}
	}
	return p;
}

Node* AVLTree::remove(int key)
{
	pRoot = remove(pRoot, key);
}

int main()
{
	//vector<int> intVec{3, 2, 1, 4, 4, 5, 6, 7, 10, 9, 7, 8};
	vector<int> intVec{ 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
	//vector<int> intVec{ 3,2,1,4,5,6,7,16,15 };
	AVLTree tree;
	for (auto i : intVec)
		tree.insert(i);

	tree.print();
	tree.printTree_2();

	tree.remove(13);
	tree.printTree_2();
}