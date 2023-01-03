#include <iostream>
#include <array>

void c_arrprint(int* arr, int count) {
	for (int i = 0; i < count; i++)
	{
		std::cout << arr[i] << ", ";
		//printf("%d ", arr[i]);
	}
}

void arrprint(std::array<int, 5> arr)
{
	for (auto ele : arr) {
		std::cout << ele << ", ";
	}
}


template<size_t N>
void arrprint2(const std::array<int, N>& arr) {
	for (auto ele : arr) {
		std::cout << ele << ", ";
	}
}

int main(void)
{
	//예외처리 예시
	//std::array<int, 4> arr3 = { 1,2,3,4 };

	//try
	//{
	//	std::cout << arr3.at(3) << std::endl;
	//	std::cout << arr3.at(4) << std::endl; // 예외발생 
	//}
	//catch (const std::out_of_range& ex)
	//{
	//	std::cerr << ex.what() << std::endl;
	//}

	//arrprint
	std::array<int, 5> arr = { 1,2,3,4,5 };
	arrprint(arr);
		// c스타일 방식
	int c_arr[10] = { 1,2,3,4,5 };
	c_arrprint(c_arr, sizeof(c_arr) / sizeof(int));
}