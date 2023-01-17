#include <iostream>
#include <string>
#include <forward_list>

struct citizen 
{
	std::string name;
	int age;
};


std::ostream& operator<<(std::ostream& os, const citizen& c)
{
	return (os << "[" << c.name << ", " << c.age << "]");
}

int main() 
{
	std::forward_list<citizen> citizens = { {"kang",30}, {"Parck",29},{"Min",12},{"Lee",16} };

	auto citizens_copy = citizens;

	std::cout << "��ü �ùε�: ";
	for (const auto &c : citizens)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	citizens.remove_if([](const citizen& c) { return (c.age < 19); });

	std::cout << "��ǥ���� �ִ� �ùε�: ";
	for (const auto& c : citizens)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

}