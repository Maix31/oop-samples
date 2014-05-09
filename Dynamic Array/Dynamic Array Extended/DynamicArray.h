#pragma once

class DynamicArrayElementProxy;

///
/// ��������� ��������� �����
///
class DynamicArray
{
private:
	/// ������� �� ������
	int *pData;

	/// ������ �� ���������� ����� �� ������
	size_t AllocatedSize;
	
	/// ���� �� ������������ ������ �� ������
	size_t Length;

public:
	DynamicArray();
	DynamicArray(DynamicArray const &);
	DynamicArray& operator=(DynamicArray const &);
	~DynamicArray();

public:
	void Free();
	
	void Add(int Element);

	size_t GetAllocatedSize() const;
	size_t GetLength() const;
	
	int GetAt(size_t) const;
	void SetAt(size_t, int);

	void Print() const;

public:
	DynamicArray operator+(DynamicArray const &) const;
	DynamicArrayElementProxy operator[](size_t);
	const DynamicArrayElementProxy operator[](size_t) const;

private:
	void Reallocate(size_t NewSize);
	void CopyFrom(DynamicArray const &);
};


///
/// ��������� ������� � ��������� �����
///
class DynamicArrayElementProxy
{
private:
	/// �������� ��� ���������� �����, ����� � ������ proxy-��
	DynamicArray *pParent;

	/// ������ �� �������� �� ���������� �����, ����� proxy-�� ���������
	size_t ParentElementIndex;
	
public:
	DynamicArrayElementProxy(DynamicArray *, size_t);

public:
	operator int() const;
	
	DynamicArrayElementProxy& operator=(int);
};