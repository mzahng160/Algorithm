#include <iostream>
using namespace std;

struct ListNode
{
	int value;
	ListNode* next;

	ListNode (int value_, ListNode* next_ = nullptr)
	{
		value = value_;
		next = next_;
	}
};

void CreateList(ListNode** head, int* line, int len)
{

	for(int i = 0; i < len; i++)
	{
		*head= new ListNode(line[i], *head);
	}
}

void findCommon(ListNode* ptr1, ListNode* ptr2)
{
	cout << "common part" << endl;

	while(ptr1 != nullptr && ptr2 != nullptr)
	{
		if(ptr1->value > ptr2->value)
		{	
			ptr2 = ptr2->next;
		}
		else if(ptr1->value < ptr2->value)
		{	
			ptr1 = ptr1->next;
		}
		else
		{			
			cout << "^ "<< ptr1->value << endl;
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}
}

void DelNode(ListNode** head, int delValue)
{
	ListNode* ptr = *head;
	ListNode* prevPtr = nullptr;
	while(nullptr != ptr)
	{
		if(ptr->value == delValue)
		{
			prevPtr->next = ptr->next;

			delete ptr;
			ptr = nullptr;

			break;
		}
		prevPtr = ptr;
		ptr = ptr->next;
	}
}

void reverse(ListNode** head)
{
	
}

int main()
{
	int FirstLine[10]= {10,9,8,7,6,5,4,3,2,1};
	int SecondLine[10]= {12,11,10,9,8,7,6,5,4,3};

	ListNode* List_1 = nullptr;
	ListNode* List_2 = nullptr;

	CreateList(&List_1, FirstLine, 10);
	CreateList(&List_2, SecondLine, 10);

	findCommon(List_1, List_2);

	DelNode(&List_2, 10);
#if 0 //PRINT_LIST	
	ListNode* ptr = List_2;
	while(ptr != nullptr)
	{
		cout << ptr->value << endl;
		ptr = ptr->next;
	}
#endif
	return 0;
}
