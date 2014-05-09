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
	pData = NULL;
	AllocatedSize = 0;
	Length = 0;
}


///
/// ����������� �� �������� (copy constructor)
///
DynamicArray::DynamicArray(DynamicArray const & other)
{
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
/// ��� index �� � ������� ������ � ������, ���������
/// ������ ���������� �� ��� out_of_range
///
int DynamicArray::GetAt(size_t index) const
{
	if(index >= Length)
		throw std::out_of_range("index out of range!");

	return pData[index];
}


///
/// ������� ���������� �� ������� � ������.
///
/// ��� index �� � ������� ������ � ������, ���������
/// ������ ���������� �� ��� out_of_range
///
void DynamicArray::SetAt(size_t index, int value)
{
	if(index >= Length)
		throw std::out_of_range("index out of range!");

	pData[index] = value;
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

	if(Length > 0)
	{
		std::cout << "Contents: " << pData[0];

		for(size_t i = 1; i < Length; i++)
			std::cout << ", " << pData[i];

		std::cout << "\n";
	}
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


///
/// ����� proxy �����, ����� ��������� �������� �� ������ � ������ index.
///
/// ���� ������ �� ��������� �� �������� �� ������������ ������ � �����
/// proxy �����, ����� ���� �� �� �������� �� ������� �� �������� �� ������.
///
/// �����:
/// 1. ���������� �� ����� �������� �� ���� ���� index
/// � ������� ������ � ������. ������ �������� �� �����
/// ����� ���, ������ proxy ������� �� ��������.
/// 2. proxy ������� � ������� � ��������� ������, � �� � ��������� �������
/// �� ������. ���� ��������, �� ���������� �� ���� ����� ������� �� ������
/// � ���������� �����, proxy ������� ������ �� �������� ���� � ��� ������.
///
DynamicArrayElementProxy DynamicArray::operator[](size_t index)
{
	return DynamicArrayElementProxy(this, index);
}


///
/// ����� proxy �����, ����� ��������� �������� �� ������ � ������ index.
///
/// ���� ������ �� ��������� �� �������� �� ���������� ������ � �����
/// ���������� proxy �����, ����� *�� ����* �� �� �������� �� �������
/// �� �������� �� ������.
///
/// �� ������������ ����������, ����� ��������� ��� �������������� ������
/// �� subscript ���������.
///
const DynamicArrayElementProxy DynamicArray::operator[](size_t index) const
{
	// ��-���� � ����� const_cast, ������ ������������� �� proxy-��
	// ������ �������� ��� ������������ �����
	return DynamicArrayElementProxy(const_cast<DynamicArray*>(this), index);
}



/// ============================================================================



///
/// ���������� ��� proxy �����, ����� ���������
/// �������� �� ������� ElementIndex � ���������� �����
/// ����� �� pParent
///
DynamicArrayElementProxy::DynamicArrayElementProxy(DynamicArray * pDynamicArray, size_t ElementIndex) :
	pParent(pDynamicArray),
	ParentElementIndex(ElementIndex)
{
}


///
/// ����� ���������� �� ��������, ������ ��� ��
/// �������� ���� rvalue
///
DynamicArrayElementProxy::operator int() const
{
	return pParent->GetAt(ParentElementIndex);
}


///
/// ��������� ���� �������� �� ��������, ������
/// ��� �� �������� ���� lvalue
///
DynamicArrayElementProxy& DynamicArrayElementProxy::operator=(int value)
{
	pParent->SetAt(ParentElementIndex, value);

	return *this;
}