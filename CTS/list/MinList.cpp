#include <iostream>
#include <algorithm>

struct MinNode {
	int data; // int 값만 되게 만들어보자
	MinNode* next; // 다음 노드를 가리키는 포인터 역할
};

class MinList 
{
public:
	using node = MinNode; // MinNode 를 node라는 이름으로 쓰겠다.
	using node_ptr = node*; // node*를  node_ptr라는 이름으로 쓰겠다.
private:
	node_ptr head;// 첫 노드

public:

	//리스트 맨앞에 값을 넣는다.
	void push_front(int val) 
	{
		auto new_node = new node{ val, nullptr }; // 새로운 노드를 하나만든다. 여기서 노드는 MinNode
		
		if (head != nullptr)
			new_node->next = head; 
		// head 즉 첫 주소가 널이아니면 즉 뭔가 값이있으면 지금 만든 노드에 넥스트를 head로한다.
		// 리스트에 값이 있으면 맨앞에 뭔가를 추가하려면 새로운 노드가 맨앞 노드를 가리키게한다.

		head = new_node;
		//리스트에 값이 없을땐 바로 새로 만든 노드가 맨앞자리를 차지하게한다.
		
		//리스트에 값이 있을땐 이미 앞에서 새로운 노드의 next 값을 head로 바꿨기때문에 
		//head 만 바꿔주면 [new_node - 원래있던 노드 - 원래 있던노드] 이런식으로 이어지게된다.
	}

	//리스트 맨앞 원소 삭제
	void pop_front() 
	{
		auto first = head;
		if (head) // 헤드가 없으면 원소가 없는거다. 그래서 뭘 할필요가 없다
		{
			head = head->next; // head 즉 첫 원소를 다음 원소로 바꿔준다.
			delete first; // 그러고 원래 첫원소였던 친구는 삭제
		}
	}


	//반복자구현
	struct MinList_iterator 
	{
	private:
		node_ptr ptr;
	public:
		MinList_iterator(node_ptr p) : ptr(p) {}; //초기화리스트 를 사용해서 ptr(p) 로 초기화해준다.

		int& operator*() { return ptr->data; }; // 역참조 하는 기능! 

		node_ptr get() { return ptr; }; // 본인의 주소를 가져오는기능!

		//선행증가
		MinList_iterator& operator++() 
		{
			ptr = ptr->next; // 다음 노드를 가리킨다.
			return *this; // 본인을 리턴 (노드를 가리키는 ptr이기때문에 그것에 값은 노드 주소 자체가된다.)
		}

		//후행증가
		MinList_iterator operator++(int) 
		{
			MinList_iterator result = *this;
			++(*this);
			return result; // 여기서 반환하는것은 이전 에 값을 반환해서 후위연산을 구현하는것이다.
		}


		friend bool operator==(const MinList_iterator& left, const MinList_iterator& right) 
		{
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const MinList_iterator& left, const MinList_iterator& right)
		{
			return left.ptr != right.ptr;
		}
	};

	
	MinList_iterator begin() { return MinList_iterator(head); };
	MinList_iterator end() { return MinList_iterator(nullptr); };

	//const 버전
	MinList_iterator begin() const { return MinList_iterator(head); };
	MinList_iterator end() const { return MinList_iterator(nullptr); };


	//생성자를 무조건 쓰게한다.
	MinList() = default;

	//복사생성자
	MinList(const MinList& other) : head(nullptr) 
	{
		if (other.head) 
		{
			head = new node{ 0,nullptr };
			auto cur = head;
			auto it = other.begin();
			while (true) 
			{
				cur->data = *it;

				auto tmp = it;
				++tmp;
				
				if (tmp == other.end()) { break; };

				cur->next = new node{ 0,nullptr };
				cur = cur->next;
				it = tmp;
			}
		}
	}

	//초기화 리스트를 사용하는 생성자 
	MinList(const std::initializer_list<int>& ilist) : head(nullptr) 
	{
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++) 
		{
			push_front(*it);
		}
	}

	//print 함수

	void print() 
	{
		auto tmpHead = head;

		while (head != nullptr) 
		{
			std::cout << head->data << ",";
			head = head->next;
		}

		head = tmpHead;

		std::cout << std::endl;
	}
};

int main() 
{
	MinList ml = { 1,2,3 };
	ml.push_front(0);
	ml.print();

	auto ml2 = ml;
	ml2.push_front(-1);
	std::cout << "첫번째 리스트 복사후 맨앞에 -1 추가"<< std::endl;
	ml2.print();

	std::cout << "깊은 복사후 첫번째 리스트 다시 프린트" << std::endl;
	ml.print();
}