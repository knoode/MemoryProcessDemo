// Read Memory from Target

#include <iostream>
#include <cstddef>
#include <Windows.h>

using std::dec;
using std::hex;

int main()
{
	DWORD pid{};

	std::cout << "[?] Target PID: ";
	std::cin >> pid;
	std::cout << "[INFO] Opening Process with PID " << pid << " ..." << std::endl;

	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);

	if (!hProcess) {
		std::cerr << "[ERROR] OpenProcess() exited with error " << GetLastError() << '\n';
		system("pause");
		return EXIT_FAILURE;
	}

	BOOL bRead;
	std::string varType{};
	uintptr_t lpBase{};

	std::cout << "[?] Variable type: ";
	std::cin >> varType;

	std::cout << "[?] Base addr: ";
	std::cin >> hex >> lpBase;

	int varInt{};
	double varDouble{};
	std::string varString{};
	if (varType == "int") {
		if (ReadProcessMemory(
			hProcess, reinterpret_cast<LPCVOID>(lpBase), &varInt, sizeof(varInt), nullptr
		)) {
			std::cout << "[SUCCESS] Variable type INT, value: " << varInt << '\n';
		}
		else {
			std::cerr << "[ERROR] Cannot read from memory, Last Error: " << GetLastError() << '\n';
			return EXIT_FAILURE;
		}
	}
	else if (varType == "double" || varType == "float") {
		if (ReadProcessMemory(
			hProcess, reinterpret_cast<LPCVOID>(lpBase), &varDouble, sizeof(varDouble), nullptr
		)) {
			std::cout << "[SUCCESS] Variable type DOUBLE, value: " << varDouble << '\n';
		}
		else {
			std::cerr << "[ERROR] Cannot read from memory, Last Error: " << GetLastError() << '\n';
			return EXIT_FAILURE;
		}
	} else if (varType == "char[]" || varType == "char*") {
		size_t varCharArr_sz{};
		std::cout << "Char[] length: ";
		std::cin >> varCharArr_sz;
		char* varCharArr = new char[varCharArr_sz];
		
		if (ReadProcessMemory(
			hProcess, reinterpret_cast<LPCVOID>(lpBase), varCharArr, varCharArr_sz, nullptr
		)) {
			std::cout << "[SUCCESS] Variable type CHAR[] read, value: \"" << varCharArr << "\"\n";
			delete[] varCharArr;
		}
		else {
			std::cerr << "[ERROR] Cannot read from memory, Last Error: " << GetLastError() << '\n';
			delete[] varCharArr;
			return EXIT_FAILURE;
		}
	} else if (varType == "string" || varType == "std::string") {
		if (ReadProcessMemory(
			hProcess, reinterpret_cast<LPCVOID>(lpBase), &varString, sizeof(varString), nullptr
		)) {
			std::cout << "[SUCCESS] Variable type std::string read, value: \"" << varString << "\"\n";
		}
		else {
			std::cerr << "[ERROR] Cannot read from memory, Last Error: " << GetLastError() << '\n';
			return EXIT_FAILURE;
		}
	}
	else {
		std::cout << "[ERROR] Unknown variable type: \"" << varType << '\n';
		return EXIT_FAILURE;
	}

	CloseHandle(hProcess);
	system("pause");
}