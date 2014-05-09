#pragma once

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

	void Print() const;

public:
	DynamicArray operator+(DynamicArray const &) const;

private:
	void Reallocate(size_t NewSize);
	void CopyFrom(DynamicArray const &);
};