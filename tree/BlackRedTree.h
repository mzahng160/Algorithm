#ifndef BLACK_RED_TREE_H
#define BLACK_RED_TREE_H

#include <iostream>
#include <string>

using namespace std;

enum color {
	BLACK,
	RED
};

enum unbalance_type {
	TYPE_LL,
	TYPE_LR,
	TYPE_RL,
	TYPE_RR
};

class Node
{
public:
	int key = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
	enum color color;

	Node(int key_t = 0)
	{
		key = key_t;
		color = RED;
		left = right = parent = nullptr;
	}
};

class BlackRedTree
{
public:
	BlackRedTree();
	~BlackRedTree();

	void insert(int key);
	void printTree_2();

private:
	Node* pRoot;
	Node* insertReal(int key, Node* p);	
	Node* adjustColor(Node* pRoot);

	Node* ll_rotate(Node* p);
	Node* lr_rotate(Node* p);
	Node* rr_rotate(Node* p);
	Node* rl_rotate(Node* p);

	void printInOrder(Node* p, int height, string to, int len);
	string getSpace(int num);
};

void BlackRedTree::insert(int key)
{
	pRoot = insertReal(key, pRoot);
}
Node* BlackRedTree::insertReal(int key, Node* pRoot)
{
	//insert pRoot node
	if (pRoot == nullptr)
	{
		pRoot = new Node(key);
		pRoot->color = BLACK;
		return pRoot;
	}

	Node* pre = nullptr;
	Node* tmp = pRoot;
	while (tmp != nullptr) 
	{
		pre = tmp;
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	tmp = new Node(key);
	if (key < pre->key)
		pre->left = tmp;
	else if (key > pre->key)
		pre->right = tmp;	
	tmp->parent = pre;

	return pRoot;
	//return adjustColor(tmp);
}

Node* BlackRedTree::ll_rotate(Node* p)
{
	Node* k = p->left;
	p->left = k->right;
	if (nullptr != k->right)
		k->right->parent = p;
	k->right = p;

	return k;
}
Node* BlackRedTree::rr_rotate(Node* p)
{
	Node* k = p->right;
	p->right = k->left;
	if (nullptr != k->left)
		k->left->parent = p;
	k->left = p;	

	return k;
}

Node* BlackRedTree::lr_rotate(Node* p)
{
	Node* k = p->left;
	p->left = rr_rotate(k);
	return ll_rotate(p);
}

Node* BlackRedTree::rl_rotate(Node* p)
{
	Node* k = p->right;
	p->right = ll_rotate(k);
	return rr_rotate(p);
}

Node* BlackRedTree::adjustColor(Node* p)
{
	Node* parent =  nullptr;

	while ((parent = p->parent) != nullptr && parent->color == RED)
	{
		Node* parentBrother = nullptr;

		if (parent->parent->left == parent)
			parentBrother = parent->parent->right;
		else
			parentBrother = parent->parent->left;

		if (parentBrother && parentBrother->color == RED)
		{
			parent->color = BLACK;
			parentBrother->color = BLACK;
			parent->parent->color = RED;
			p = parent->parent;			
			continue;
		}

		if (parentBrother && parentBrother->color == BLACK)
		{
			//same side
			if(p == parent->left && parent->parent->left == parent)
			{
				parent->color = BLACK;
				parent->parent->color = RED;
				ll_rotate(parent->parent);
			}
			else if (p == parent->right && parent->parent->right == parent)
			{
				parent->color = BLACK;
				parent->parent->color = RED;
				rr_rotate(parent->parent);
			}

			//different side
			if (p == parent->left && parent->parent->right == parent)
			{
				parent->color = BLACK;
				parent->parent->color = RED;
				rl_rotate(parent->parent);
			}
			else if (p == parent->right && parent->parent->left == parent)
			{
				parent->color = BLACK;
				parent->parent->color = RED;
				lr_rotate(parent->parent);
			}

			break;
		}
	}

	pRoot->color = BLACK;
	return pRoot;
}

void BlackRedTree::printInOrder(Node* p, int height, string to, int len)
{
	if (p == nullptr)
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
	cout << getSpace(height * len) + val << endl;
	printInOrder(p->left, height + 1, "^", len);
}

void BlackRedTree::printTree_2()
{
	Node* p = pRoot;
	cout << "Binary tree" << endl;
	printInOrder(p, 0, "H", 17);
	cout << endl;
}

string BlackRedTree::getSpace(int num)
{
	string buf;
	for (int i = 0; i < num; i++)
	{
		buf.append(" ");
	}
	return buf;
}

#endif // !BLACK_RED_TREE_H

