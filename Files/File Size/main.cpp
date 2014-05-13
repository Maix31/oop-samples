// 
// ���������� ������� �� ������ ������� �� ����� ����
//

#include <iostream>

#include <fstream>

int main(int argc, char* argv[])
{
	std::ifstream in;

	// ����������� ���� ����� �� ����� � ������� �� ��������� ���
	if(argc != 2)
	{
		// ��� ����� �� � ������� �� ��������� ���,
		// ������ ���������� �� ����������� �� �� ������

		// ��������� �����, � ����� �� �������� ����� �� �����
		// _MAX_PATH � �������� ���������
		char buffer[_MAX_PATH];

		std::cout << "Path: ";
		std::cin.getline(buffer, _MAX_PATH);

		in.open(buffer);
	}
	else
	{
		// ����� ��� ����� � ������� �� ��������� ���
		in.open(argv[1]);
	}

	// ����������� ���� ������ � ��� ������� �������
	if( ! in)
	{
		// ��� ���� �� � ����, ��������� ��������� �� ������
		std::cerr << "Cannot open the file for reading!\n";
		return 1;
	}

	// ������� ������� �� ����� ���� ������ � ������� ����
	// � �������� �������� �������
	in.seekg(0, std::ios::end);

	size_t size = in.tellg();

	// ��������� �����, ������ ������ ���� �� �� ����������
	in.close();

	// ��������� ������� �� �����
	std::cout << "Size: " << size << " bytes\n";

	return 0;
}
