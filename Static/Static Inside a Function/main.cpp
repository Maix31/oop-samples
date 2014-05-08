#include <iostream>
#include <time.h>

///
/// �������, ����� ���� ����� ���� � ���� ��������
///
void CountCalls()
{
	static int callCount = 0;

	callCount++;

	std::cout << "CountCalls() was called " << callCount << " times\n";
}


int main()
{
	srand((unsigned)time(NULL));

	// �������� �������������� ����� ����� 1 � 10
	int callCount = rand() % 10 + 1;

	while(callCount-- > 0)
	{
		CountCalls();
	}
}