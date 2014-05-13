/*
	���������� �� ����� � ���� ������ �� ����� � nothrow,
	��������:
	
	int** ppBuffer = new (std::nothrow) int* [Rows];

	� ���� ������, ��� ���������� � ���������, new �� ������
	����������, � ������ ���� ����� NULL
*/

#include <iostream>
#include <assert.h>

///
///	����������� ������� ����� �� �������� �����,
/// ����� � ��� ������� � Allocate().
///
void Free(int** ppArray, size_t Rows)
{
	assert(ppArray != NULL);

	for(size_t i = 0; i < Rows; i++)
	{
		delete [] ppArray[i];
	}

	delete [] ppArray;
}


///
///	������ �������� �����
///
/// \return
///		�������� ��� ������������� ����� ���
///		NULL, ��� ��������� �� ����� �� ������ ������
///
int** Allocate(size_t Rows, size_t Cols)
{
	int** ppBuffer = new (std::nothrow) int* [Rows];

	if( ! ppBuffer)
		return NULL;

	for(size_t i = 0; i < Rows; i++)
	{
		ppBuffer[i] = new (std::nothrow) int [Cols];

		if( ! ppBuffer[i])
		{
			Free(ppBuffer, i);
			return NULL;
		}
	}

	return ppBuffer;

}


int main()
{
	size_t Rows, Cols;

	std::cout << "Enter Rows: ";
	std::cin >> Rows;

	std::cout << "Enter Cols: ";
	std::cin >> Cols;

	int **ppArray = Allocate(Rows, Cols);

	if( ! ppArray)
	{
		std::cerr << "Allocation failed!";
		return 1;
	}

	// ��� ����� �� ���������� ������ �� ���� �������

	Free(ppArray, Rows);

	return 0;
}