#include <iostream>

#include "Array.h"

int main()
{
	Array<char> arr;

	// ��������� ������ � ����� �����-������
	for (char c = 'z'; c >= 'a'; c--)
		arr[c - 'a'] = c;

	// ��������� ��������� � ������� �� ��������
	std::cout << "The alphabet: ";

	for (Array<char>::Iterator it = arr.GetIterator(); !it.IsOver(); it.Next())
	{
		std::cout << it.Value();
	}

	std::cout << "\n\n";

	return 0;
}