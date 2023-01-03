#include <iostream>
#include <sstream>
#include <algorithm>

template <typename T>
class dynamic_array 
{
	//멤버변수
	T* data;
	size_t n;

public:

	//생성자
	dynamic_array(int n)
	{
		this->n = n;
		data = new T[n];
	}

	//복사생성자
	dynamic_array(const dynamic_array<T>& other)
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
		{
			data[i] = other[i];
		}
	}

	//배열의 [] 연산자 처럼 원소에 접근하는 연산자를 만든다.
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
		// 인덱스 값을 넘어서는 것을 try catch 하게 만든 것 / 예외처리 할 수 있게
	}

	// 크기 반환 함수와 ,소멸자
	size_t size() const 
	{
		return n;
	}

	~dynamic_array() 
	{
		delete[] data; // 메모리 누수 방지
	}

	//반복자 관련 함수 정의

	T* begin() { return data; } // 첫 주소 반환
	const T* begin() const { return data; }

	T* end() { return data + n; } // 첫주소 + 본인크기 하면 마지막주소 의 다음주소가나옴
	const T* end() const { return data + n; }

	// 두배열을 합치는 함수 를 + 연산자를 통해서 한다.
	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1,
											dynamic_array<T>& arr2)
	{
		dynamic_array<T> result(arr1.size() + arr2.size()); // 결과값을 저장하기위함

		std::copy(arr1.begin(), arr1.end(), result.begin()); // 첫번째 배열을 result에 카피
		std::copy(arr2.begin(), arr2.end(), result.begin() + arr1. size()); 
		// 두번째 배열을 result 에 첫번째 배열 이후 인덱스부터 카피

		return result;
	}

	// 저장된 데이터를 모두 문자열로 반환하는 함수
	std::string to_string(const std::string& sep = ", ")
	{
		if (n == 0) return "";

		std::ostringstream os; // 문자열 사용할때 편하려고 사용
		
		os << data[0]; 

		for (int i = 1; i < n; i++) // 첫 번째 배열 이후 부터 , 를 붙이기위해 사용
		{
			os << sep << data[i];
		}

		return os.str();
	}


};


//학생 구조체
struct student
{
	std::string name;
	int standard; // 학급정보 , 몇반 몇반
};

// << 연산자를 통해 학생 정보를 출력하는 함수
std::ostream& operator<<(std::ostream& os, const student& s)
{
	return (os << "[" << s.name << ", " << s.standard << "]");
}

// 구동 테스트
int main() 
{
	int nStudent;
	std::cout << "1반 학생수 입력하세유 : ";
	std::cin >> nStudent;

	dynamic_array<student> class1(nStudent); // nStudent 크기 만큼 student 타입으로하는 동적배열 생성

	for (int i = 0; i < nStudent; i++)
	{
		std::string name;
		int standard;
		std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요(영어) :";
		std::cin >> name >> standard;

		class1[i] = student{ name,standard }; // 이름과 반을 각 원소 에 넣어준다
	}

	//깊은복사
	auto class2 = class1; 
	// dynamic_array<student> class2(class1); 이랑 같음 즉 복사생성자가 실행됨

	std::cout << "1반 을 복사하여 2반 생성: " << class2.to_string() << std::endl;

	// 두학급을 합쳐서 더 큰 거 만들기
	auto class3 = class1 + class2;
	// class1 과 class2 를 합치고 복사생성자 실행
	std::cout << "1반과 2반을 합쳐 3반 생성 : " << class3.to_string() << std::endl;

	return 0;
}