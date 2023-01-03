#include <iostream>
#include <sstream>
#include <algorithm>

template <typename T>
class dynamic_array 
{
	//�������
	T* data;
	size_t n;

public:

	//������
	dynamic_array(int n)
	{
		this->n = n;
		data = new T[n];
	}

	//���������
	dynamic_array(const dynamic_array<T>& other)
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
		{
			data[i] = other[i];
		}
	}

	//�迭�� [] ������ ó�� ���ҿ� �����ϴ� �����ڸ� �����.
	T& operator[](int index) 
	{
		return data[index];
	}

	const T& operator[](int index) const
	{
		return data[index];
	}

	T& at(int index) 
	{
		if (index < this->n)
		{
			return data[index];
		}
		throw "Index out of range"; 
		// �ε��� ���� �Ѿ�� ���� try catch �ϰ� ���� �� / ����ó�� �� �� �ְ�
	}

	// ũ�� ��ȯ �Լ��� ,�Ҹ���
	size_t size() const 
	{
		return n;
	}

	~dynamic_array() 
	{
		delete[] data; // �޸� ���� ����
	}

	//�ݺ��� ���� �Լ� ����

	T* begin() { return data; } // ù �ּ� ��ȯ
	const T* begin() const { return data; }

	T* end() { return data + n; } // ù�ּ� + ����ũ�� �ϸ� �������ּ� �� �����ּҰ�����
	const T* end() const { return data + n; }

	// �ι迭�� ��ġ�� �Լ� �� + �����ڸ� ���ؼ� �Ѵ�.
	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1,
											dynamic_array<T>& arr2)
	{
		dynamic_array<T> result(arr1.size() + arr2.size()); // ������� �����ϱ�����

		std::copy(arr1.begin(), arr1.end(), result.begin()); // ù��° �迭�� result�� ī��
		std::copy(arr2.begin(), arr2.end(), result.begin() + arr1. size()); 
		// �ι�° �迭�� result �� ù��° �迭 ���� �ε������� ī��

		return result;
	}

	// ����� �����͸� ��� ���ڿ��� ��ȯ�ϴ� �Լ�
	std::string to_string(const std::string& sep = ", ")
	{
		if (n == 0) return "";

		std::ostringstream os; // ���ڿ� ����Ҷ� ���Ϸ��� ���
		
		os << data[0]; 

		for (int i = 1; i < n; i++) // ù ��° �迭 ���� ���� , �� ���̱����� ���
		{
			os << sep << data[i];
		}

		return os.str();
	}


};


//�л� ����ü
struct student
{
	std::string name;
	int standard; // �б����� , ��� ���
};

// << �����ڸ� ���� �л� ������ ����ϴ� �Լ�
std::ostream& operator<<(std::ostream& os, const student& s)
{
	return (os << "[" << s.name << ", " << s.standard << "]");
}

// ���� �׽�Ʈ
int main() 
{
	int nStudent;
	std::cout << "1�� �л��� �Է��ϼ��� : ";
	std::cin >> nStudent;

	dynamic_array<student> class1(nStudent); // nStudent ũ�� ��ŭ student Ÿ�������ϴ� �����迭 ����

	for (int i = 0; i < nStudent; i++)
	{
		std::string name;
		int standard;
		std::cout << i + 1 << "��° �л� �̸��� ���̸� �Է��ϼ���(����) :";
		std::cin >> name >> standard;

		class1[i] = student{ name,standard }; // �̸��� ���� �� ���� �� �־��ش�
	}

	//��������
	auto class2 = class1; 
	// dynamic_array<student> class2(class1); �̶� ���� �� ��������ڰ� �����

	std::cout << "1�� �� �����Ͽ� 2�� ����: " << class2.to_string() << std::endl;

	// ���б��� ���ļ� �� ū �� �����
	auto class3 = class1 + class2;
	// class1 �� class2 �� ��ġ�� ��������� ����
	std::cout << "1�ݰ� 2���� ���� 3�� ���� : " << class3.to_string() << std::endl;

	return 0;
}