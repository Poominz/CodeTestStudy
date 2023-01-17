#include <iostream>
// 목표 리스트 삽입함수 만들어보기  단 배열이나 stl 컨테이너 사용불가
// 힌트 1. struct , 2. push_front


struct Node
{
	int Data;		// 값
	Node* Next;		// 주소
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