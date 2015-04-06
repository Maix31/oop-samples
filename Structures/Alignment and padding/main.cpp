#include <iostream>
#include <fstream>

struct Test
{
	// �� ����������: �������� �� ���������� �������� � ����������� �
	// ����� ��� ���� �� �� ������ ����� ������ ������
	char c1;
	short s;
	char c2;
	long l;
	unsigned char c3;
};


// ������ ������� ��������� �� �������� � �����������
void Init(Test* p)
{
	p->c1 = 0x01;
	p->s = 0x1234;
	p->c2 = 0x02;
	p->l = 0x12345678;
	p->c3 = 0x03;
}


// ������� ������������ �� ��������� � ������� ����
void SaveToTextFile(Test* p, std::ofstream& file)
{
	file
		<< p->c1 << " "
		<< p->s  << " "
		<< p->c2 << " "
		<< p->l  << " "
		<< p->c3 << "\n";
}


// ������� ���������� �� offset-� �� ���� �� �������� � �����������
#define FIELD_INFO(field) std::cout << "    " #field ": offset=" << offsetof(Test, field) << "\n";


int main()
{
	// ��������� ���������� �� �����������
	std::cout << "Size of Test: " << sizeof(Test) << std::endl;
	FIELD_INFO(c1);
	FIELD_INFO(s);
	FIELD_INFO(c2);
	FIELD_INFO(l);
	FIELD_INFO(c3);

	
	// ��������� � �������������� ���� ��������� �� �����������
	Test instance;
	Init(&instance);

	// �� ����������: ����������� ���������� ���� debugger, ��������
	// ����������� instance � ������� � ����������� ��� �� �����������
	// ������� �������.

	// ��������� � �������������� ����� �� ���������
	Test arr[5];

	for (int i = 0; i < 5; i++)
		Init(&arr[i]);

	// �� ����������: ����� � �� instance ��-����, �������� ������ � ������� �
	// ����� ��� �� ����������� �������� �������� � �������.


	// ��������� �� ������������ ���������� ������� ������
	Test* p = arr;
	std::cout << "First element at 0x" << p << ", second element at 0x" << (p + 1) << "\n";

	return 0;
}