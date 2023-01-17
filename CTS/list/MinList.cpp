#include <iostream>
#include <algorithm>

struct MinNode {
	int data; // int ���� �ǰ� ������
	MinNode* next; // ���� ��带 ����Ű�� ������ ����
};

class MinList 
{
public:
	using node = MinNode; // MinNode �� node��� �̸����� ���ڴ�.
	using node_ptr = node*; // node*��  node_ptr��� �̸����� ���ڴ�.
private:
	node_ptr head;// ù ���

public:

	//����Ʈ �Ǿտ� ���� �ִ´�.
	void push_front(int val) 
	{
		auto new_node = new node{ val, nullptr }; // ���ο� ��带 �ϳ������. ���⼭ ���� MinNode
		
		if (head != nullptr)
			new_node->next = head; 
		// head �� ù �ּҰ� ���̾ƴϸ� �� ���� ���������� ���� ���� ��忡 �ؽ�Ʈ�� head���Ѵ�.
		// ����Ʈ�� ���� ������ �Ǿտ� ������ �߰��Ϸ��� ���ο� ��尡 �Ǿ� ��带 ����Ű���Ѵ�.

		head = new_node;
		//����Ʈ�� ���� ������ �ٷ� ���� ���� ��尡 �Ǿ��ڸ��� �����ϰ��Ѵ�.
		
		//����Ʈ�� ���� ������ �̹� �տ��� ���ο� ����� next ���� head�� �ٲ�⶧���� 
		//head �� �ٲ��ָ� [new_node - �����ִ� ��� - ���� �ִ����] �̷������� �̾����Եȴ�.
	}

	//����Ʈ �Ǿ� ���� ����
	void pop_front() 
	{
		auto first = head;
		if (head) // ��尡 ������ ���Ұ� ���°Ŵ�. �׷��� �� ���ʿ䰡 ����
		{
			head = head->next; // head �� ù ���Ҹ� ���� ���ҷ� �ٲ��ش�.
			delete first; // �׷��� ���� ù���ҿ��� ģ���� ����
		}
	}


	//�ݺ��ڱ���
	struct MinList_iterator 
	{
	private:
		node_ptr ptr;
	public:
		MinList_iterator(node_ptr p) : ptr(p) {}; //�ʱ�ȭ����Ʈ �� ����ؼ� ptr(p) �� �ʱ�ȭ���ش�.

		int& operator*() { return ptr->data; }; // ������ �ϴ� ���! 

		node_ptr get() { return ptr; }; // ������ �ּҸ� �������±��!

		//��������
		MinList_iterator& operator++() 
		{
			ptr = ptr->next; // ���� ��带 ����Ų��.
			return *this; // ������ ���� (��带 ����Ű�� ptr�̱⶧���� �װͿ� ���� ��� �ּ� ��ü���ȴ�.)
		}

		//��������
		MinList_iterator operator++(int) 
		{
			MinList_iterator result = *this;
			++(*this);
			return result; // ���⼭ ��ȯ�ϴ°��� ���� �� ���� ��ȯ�ؼ� ���������� �����ϴ°��̴�.
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

	//const ����
	MinList_iterator begin() const { return MinList_iterator(head); };
	MinList_iterator end() const { return MinList_iterator(nullptr); };


	//�����ڸ� ������ �����Ѵ�.
	MinList() = default;

	//���������
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

	//�ʱ�ȭ ����Ʈ�� ����ϴ� ������ 
	MinList(const std::initializer_list<int>& ilist) : head(nullptr) 
	{
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++) 
		{
			push_front(*it);
		}
	}

	//print �Լ�

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
	std::cout << "ù��° ����Ʈ ������ �Ǿտ� -1 �߰�"<< std::endl;
	ml2.print();

	std::cout << "���� ������ ù��° ����Ʈ �ٽ� ����Ʈ" << std::endl;
	ml.print();
}