#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <string>

class  Node
{
public:
	int key = 0;
	int height = 0;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int key_t = 0)
	{
		key = key_t;
		height = 1;
		left = right = nullptr;
	}
};

class AVLTree {

public:
	AVLTree();
	//~AVLTree();

	void insert(int key);
	Node* insert_real(int key, Node* p);

	void print();
	void printTree_2();

	Node* find(int key);
	Node* find_real(int key, Node*& p);

	Node* remove(int key);

private:
	void destory(Node* p);

	int get_height(Node* p);
	int get_balance(Node* p);

	Node* ll_ratate(Node* p);
	Node* rr_ratate(Node* p);
	Node* lr_ratate(Node* p);
	Node* rl_ratate(Node* p);

	void preorder(Node* p);
	void midorder(Node* p);
	void postorder(Node* p);

	Node* GetMinNode(Node* p);
	Node* GetMaxNode(Node* p);

	std::string getSpace(int num);
	void printInOrder(Node* p, int height, std::string to, int len);

	Node* remove(Node* root, int key);

	Node* pRoot;
};

#endif