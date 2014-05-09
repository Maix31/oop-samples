#include <iostream>

#include "DynamicArray.h"

///
/// ������� ��� ��������� �����
///
/// ���� ��������������� ������� � ������
/// (�� ���� �� � �������� ��������� �����)
///
DynamicArray::DynamicArray()
{
	std::cout
		<< " -> [" << this << "] "
		<< "Entering DynamicArray()\n";

	pData = NULL;
	AllocatedSize = 0;
	Length = 0;
}


///
/// ����������� �� �������� (copy constructor)
///
DynamicArray::DynamicArray(DynamicArray const & other)
{
	std::cout
		<< " -> [" << this << "] "
		<< "Entering DynamicArray(DynamicArray const &)\n";

	CopyFrom(other);
}



///
/// �������� �� ����������� (assignment operator)
///
DynamicArray& DynamicArray::operator=(DynamicArray const & other)
{
	if(this != &other)
	{
		Free();
		CopyFrom(other);
	}

	return *this;
}


///
/// ����������
///
DynamicArray::~DynamicArray()
{
	std::cout
		<< " -> [" << this << "] "
		<< "Entering ~DynamicArray()\n";

	Free();
}


///
/// ������ ������� �� ������ other � ������� �����
///
/// ��������� ����������, �� ������� � ������.
/// �� �� �������� �������� �� ������������� �� ������� �����.
/// ��� � �����, ����� ������� ��������� ������ �� �� �������
/// ��������� ��� Free().
///
void DynamicArray::CopyFrom(DynamicArray const & other)
{
	pData = new int[other.AllocatedSize];

	for(size_t i = 0; i < other.Length; i++)
		pData[i] = other.pData[i];

	AllocatedSize = other.AllocatedSize;
	Length = other.Length;
}


///
/// ����������� ������� ����� �� ���������� �����
///
void DynamicArray::Free()
{
	delete [] pData;
	pData = NULL;
	AllocatedSize = 0;
	Length = 0;
}


///
/// ������������� ���������� �����, ���� �� ��� �� �������
/// NewSize ��������.
///
/// ��� NewSize � ��-����� �� ������� ������ �� ������,
/// ���������� � ������� >= NewSize �� �����.
///
void DynamicArray::Reallocate(size_t NewSize)
{
	std::cout
		<< " -> [" << this << "] "
		<< "Reallocating " << AllocatedSize << " -> " << NewSize << "\n";

	int* pTemp = new int[NewSize];

	// ����� �������� �� ����� ��������
	size_t limit = std::min(AllocatedSize, NewSize);

	for(size_t i = 0; i < limit; i++)
		pTemp[i] = pData[i];

	delete [] pData;

	pData = pTemp;
	AllocatedSize = NewSize;
}


///
/// ������ ��� ������� � ���������� �����
///
/// ������ ������� �� ������ � ���� �� ������.
///
void DynamicArray::Add(int Element)
{
	if(Length >= AllocatedSize)
	{
		size_t NewSize = (AllocatedSize == 0 ? 2 : AllocatedSize*2);
		
		Reallocate(NewSize);
	}

	pData[Length++] = Element;
}


///
/// ����� ������� �� ������� �� ������ �����
///
size_t DynamicArray::GetAllocatedSize() const
{
	return AllocatedSize;
}


///
/// ����� ���� �� ���������� � ������
///
size_t DynamicArray::GetLength() const
{
	return Length;
}


///
/// ����� �������� ������� �� �� ������� index � ������
///
int DynamicArray::GetAt(size_t index) const
{
	return pData[index];
}


///
/// ������� ���������� �� ������ � STDOUT
///
void DynamicArray::Print() const
{
	std::cout
		<< "Dynamic Array at 0x" << this
		<< ", buffer at 0x"      << pData
		<< ", size ("            << Length
		<< " / "                 << AllocatedSize
		<< ")\n";
}


///
/// �������� ��� ����� - ������������ �� ������� ����� � rhs
///
DynamicArray DynamicArray::operator+ (DynamicArray const& rhs) const
{
	DynamicArray temp(*this);

	for(size_t i = 0; i < rhs.GetLength(); i++)
	{
		temp.Add(rhs.GetAt(i));
	}

	return temp;
}