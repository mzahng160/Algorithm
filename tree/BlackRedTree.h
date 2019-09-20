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
	void deleteNode(int key);

private:
	Node* pRoot;
	Node* insertReal(int key, Node* p);	
	Node* adjustColor(Node* pRoot);

	Node* ll_rotate(Node* p);
	Node* lr_rotate(Node* p);
	Node* rr_rotate(Node* p);
	Node* rl_rotate(Node* p);

	Node* find(int key);
	Node* findNode(int key, Node* p);

	void printInOrder(Node* p, int height, string to, int len);
	string getSpace(int num);

	Node* case1_adjust(Node* p);
	void case2_adjust(Node* p, unbalance_type t);

	void deleteNode(Node* p);
	void deleteRedLeaf(Node* p);
	void deleteBlackLeaf(Node* p);
	void rbDeleteRoatae(Node* p, unbalance_type type);
	void deleteBlackOneSonNode(Node* p);
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

	//return pRoot;
	return adjustColor(tmp);
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

Node* BlackRedTree::find(int key)
{
	return findNode(key, pRoot);
}

Node* BlackRedTree::findNode(int key, Node* p)
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

Node* BlackRedTree::case1_adjust(Node* p)
{
	Node* parent = p->parent;
	Node* grand = parent->parent;
	Node* uncle = grand->left == parent ? grand->right:grand->left;

	grand->color = RED;
	uncle->color = BLACK;
	parent->color = BLACK;

	return grand;
}
void BlackRedTree::case2_adjust(Node* p, unbalance_type t)
{
	Node* big;
	Node* middle;
	Node* small;

	switch (t)
	{
		case TYPE_LL:
		{
			big = p;
			middle = big->left;
			small = middle->left;

			big->left = middle->right;
			if (nullptr != middle->right)
				middle->right->parent = big;
			middle->right = big;

			break;
		}

		case TYPE_LR:
		{
			big = p;
			small = big->left;
			middle = small->right;

			small->right = middle->left;
			big->left = middle->right;
			if (nullptr != middle->left)
				middle->left->parent = small;
			if (nullptr != middle->left)
				middle->right->parent = big;
			
			middle->left = small;
			middle->right = big;
			break;
		}
		case TYPE_RL:
		{
			small = p;
			big = small->right;
			middle = big->left;

			big->left = middle->right;
			small->right = middle->left;

			if (nullptr != middle->left)
				middle->left->parent = small;
			if (nullptr != middle->left)
				middle->right->parent = big;

			middle->left = small;
			middle->right = big;
			break;
		}
		case TYPE_RR:
		{
			big = p;
			middle = big->right;
			small = middle->right;

			big->right = middle->left;
			if (nullptr != middle->left)
				middle->left->parent = big;
			middle->left = big;
			break;
		}
		default:
			break;
	}	

	if (p->parent == nullptr)
		pRoot = middle;
	else if (p->parent->left == p)
		p->parent->left = middle;
	else if (p->parent->right == p)
		p->parent->right = middle;

	if (p->parent != nullptr)
		middle->parent = p->parent;

	big->parent = middle;
	small->parent = middle;

	middle->color = BLACK;
	big->color = RED;
	small->color = RED;
}

Node* BlackRedTree::adjustColor(Node* p)
{
	while (p != pRoot)
	{
		if (p->parent->color == BLACK)
			break;	

		Node* parent = p->parent;
		Node* grand = parent->parent;
		Node* uncle = grand->left == parent ? grand->right : grand->left;

		if (uncle && uncle->color == RED)
		{
			parent->color = BLACK;
			uncle->color = BLACK;
			grand->color = RED;
			p = grand;
			continue;
		}

		if (uncle == nullptr || uncle->color == BLACK)
		{
			if (p == parent->left)
			{
				if (parent == grand->left)
				{
					case2_adjust(grand, TYPE_LL);
				}
				else if (parent == grand->right)
				{					
					case2_adjust(grand, TYPE_RL);
				}
			}
			else if (p == parent->right)
			{
				if (parent == grand->right)
				{
					case2_adjust(grand, TYPE_RR);
				}
				else if (parent == grand->left)
				{
					case2_adjust(grand, TYPE_LR);
				}
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

	string keyValue;
	if (RED == p->color) 
	{
		keyValue.append("\033[41;34m");
		keyValue.append(std::to_string(p->key).c_str());
		keyValue.append("\033[0m");
	}
	else
	{
		keyValue.append("\033[46;30m");
		keyValue.append(std::to_string(p->key).c_str());
		keyValue.append("\033[0m");
	}

	string val;
	val.append(to);
	val.append(keyValue);
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

void BlackRedTree::deleteNode(Node* p)
{
	Node* parent = p->parent;
	if (p == nullptr)	//pRoot
	{
		delete pRoot;
		return;
	}

	if (p == parent->left)
		parent->left = nullptr;
	if (p == parent->right)
		parent->right = nullptr;
	delete p;	
}

void BlackRedTree::deleteRedLeaf(Node* p)
{
	deleteNode(p);
}

void BlackRedTree::rbDeleteRoatae(Node* p, unbalance_type type)
{
	Node* parent = p;
	Node* middle;

	switch (type)
	{
	case TYPE_LL:
		{
			middle = p->left;

			p->left = middle->right;
			if (middle->right != nullptr)
				middle->right->parent = p;

			middle->right = p;
		}
		break;
	case TYPE_LR:
		break;
	case TYPE_RL:
		break;
	case TYPE_RR:
		{
			middle = p->right;

			p->right = middle->left;
			if (middle->left != nullptr)
				middle->left->parent = p;

			middle->left = p;	
		}
		break;
	default:
		break;
	}
	if (parent->parent == nullptr)
		pRoot = middle;
	else if(parent = parent->parent->left)
		parent->parent->left = middle;
	else if (parent = parent->parent->right)
		parent->parent->right = middle;

	middle->parent = parent->parent;
	p->parent = middle;
}

void BlackRedTree::deleteBlackLeaf(Node* p)
{
	Node* begin = p;
	while (begin != pRoot)
	{
		Node* parent = p->parent;
		Node* brohter = parent->right;

		if (brohter && RED == brohter->color)
		{
			p->color = RED;
			brohter->color = BLACK;

			if (p == parent->left)
			{
				rbDeleteRoatae(parent, TYPE_RR);
				continue;
			}
			else
			{
				rbDeleteRoatae(parent, TYPE_LL);
				continue;
			}
		}
		else
		{
			Node* bl = brohter->left->color;
			Node* br = brohter->right->color;
			if (bl->color == BLACK && br->color == BLACK)
			{
				deleteNode(p);
				brohter->color = BLACK;
				begin = parent;
				continue;
			}

			else if (brother == parent->left && bl->color == RED)
			{
				brohter->parent->color;
				parent->color = BLACK;
				bl->color = BLACK;

				rbDeleteRoatae(parent, TYPE_LL);

				deleteNode(p);
			}
			else if	(brother == parent->right && br->color == RED)
			{
				brohter->parent->color;
				parent->color = BLACK;
				br->color = BLACK;

				rbDeleteRoatae(parent, TYPE_RR);

				deleteNode(p);
			}
			else if (brother == parent->right && bl->color == RED)
			{
				rbDeleteRoatae(brother, TYPE_LL);
				brohter->color = RED;
				bl->color = BLACK;
				begin = p;
				continue;
			}
			else if(brother == parent->left && br->color == RED)
			{
				rbDeleteRoatae(brother, TYPE_RR);
				brohter->color = RED;
				bl->color = BLACK;
				begin = p;
				continue;
			}
		}		
	}
}

void BlackRedTree::deleteBlackOneSonNode(Node* p)
{
	Node* pl = p->left;
	Node* pr = p->right;

	if (pl && RED == pl->color)
	{
		p->key = pl->key;
		p->left = nullptr;
		deleteNode(pl);
	}
	if (pr && RED == pr->color)
	{
		p->key = pr->key;
		p->right = nullptr;
		deleteNode(pr);
	}
}

void BlackRedTree::deleteNode(int key)
{
	Node* node = find(key);
	if (node == nullptr)
		return;

	int tag = 0;
	while (tag != 2)
	{
		if (nullptr == node->left)
		{
			if (nullptr == node->right)
			{
				if (RED == node->color)
					deleteRedLeaf(node);
				else
					deleteBlackLeaf(node);
				break;
			}
			else
			{
				deleteBlackOneSonNode();
				break;
			}
		}
		else if(nullptr == node->right)
		{
			deleteBlackOneSonNode();
			break;
		}
		else
		{
			Node* successor = node->right;
			while (successor->right!=nullptr)
			{
				successor = successor->right;
			}
			int tmp = node->key;
			node->key = successor->key;
			successor->key = tmp;

			node = successor;
			tag++;
		}
	}
}

#endif // !BLACK_RED_TREE_H

