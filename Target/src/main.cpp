#include <iostream>
#include <string>
#include <Windows.h>

using std::dec;
using std::hex;
using std::uppercase;

int main()
{
	int varInt = 123456;
	std::string varString = "Default String";
	double varDouble = 3.14;
	char varChar[128] = "Long char array right there ->";
	int* ptr2int = &varInt;
	int** ptr2ptr = &ptr2int;
	int*** ptr2ptr2 = &ptr2ptr;

	std::cout << "Process ID: " << GetCurrentProcessId() << '\n';
	std::cout << "varInt    (0x" << hex << uppercase << (uintptr_t)&varInt << ") = " << dec << varInt << '\n';
	std::cout << "varString (0x" << hex << uppercase << (uintptr_t)&varString << ") = " << varString << '\n';
	std::cout << "varFloat  (0x" << hex << uppercase << (uintptr_t)&varDouble << ") = " << varDouble << '\n';
	std::cout << "varChar   (0x" << hex << uppercase << (uintptr_t)&varChar << ") = " << varChar << '\n';
	std::cout << "ptr2int   (0x" << hex << uppercase << (uintptr_t)&ptr2int << ") = " << "0x" << (uintptr_t)ptr2int << '\n';
	std::cout << "ptr2ptr   (0x" << hex << uppercase << (uintptr_t)&ptr2ptr << ") = " << "0x" << (uintptr_t)ptr2ptr << '\n';
	std::cout << "ptr2ptr2  (0x" << hex << uppercase << (uintptr_t)&ptr2ptr << ") = " << "0x" << (uintptr_t)ptr2ptr2 << '\n';

	system("pause");
}