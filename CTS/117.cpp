#include <iostream>
// ��ǥ ����Ʈ �����Լ� ������  �� �迭�̳� stl �����̳� ���Ұ�
// ��Ʈ 1. struct , 2. push_front


struct Node
{
	int Data;		// ��
	Node* Next;		// �ּ�
};

Node* head;

void Push_Front(int data)
{
	Node* tmp = new Node;
	tmp->Data = data;
	tmp->Next = head;
	head = tmp;
}


int main() 
{
	Push_Front(1);
	Push_Front(2);
	Push_Front(3);

	std::cout << head->Data << std::endl;
	std::cout << head->Next->Data << std::endl;
	std::cout << head->Next->Next->Data << std::endl;
}