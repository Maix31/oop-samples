#include <iostream>
#include <time.h>

///
/// ����, ����� ���� ����� ������ ������ �� ���� ���������
/// � ������� �� ������������ �� ���������� � ����� ������
/// ����������� ��� ������� ������.
///
class Counter
{
private:
	
	/// ���� �� �������������� ��� ������� ������ ������
	static int ExistingObjectsCount;
	
	/// ���� �� ����������� � ������� �� ������������ �� ���������� ������
	static int ObjectsCreatedCount;

public:
	Counter();
	~Counter();

	static int GetExistingObjectsCount();
	static int GetObjectsCreatedCount();
};

int Counter::ObjectsCreatedCount = 0;
int Counter::ExistingObjectsCount = 0;


///
/// ����������� �� ������������
///
Counter::Counter()
{
	ExistingObjectsCount++;
	ObjectsCreatedCount++;
}


///
/// ����������
///
Counter::~Counter()
{
	ExistingObjectsCount--;
}


///
/// ����� ���� �� �������������� ��� ������� �� �����������
/// �� ��������� ������ �� ��� Counter
///
int Counter::GetExistingObjectsCount()
{
	return ExistingObjectsCount;
}


///
/// ����� ���� �� ����������� �� ������� �� �����������
/// �� ��������� ������ �� ��� Counter
///
int Counter::GetObjectsCreatedCount()
{
	return ObjectsCreatedCount;
}


int main()
{
	srand((unsigned)time(NULL));

	// �������� �������������� ����� ����� 1 � 10
	int callCount = rand() % 10 + 1;

	while(callCount-- > 0)
	{
		Counter temp;
		std::cout << "Counter objects: "
				  << Counter::GetExistingObjectsCount()
				  << " currently existing and a total of "
				  << Counter::GetObjectsCreatedCount()
				  << " created\n";
	}	

	return 0;
}