#pragma once
#include <map>

//дл€ перекомпил€ции алгоритмов под разные типы символов
using cchar = wchar_t;

//содержит информацию об алфавите 
// - например полном наборе символов кодировки или определЄнном, заданном таблично.
class Alphabet
{
public:
	//получить конкретный символ
	cchar getChar(size_t index) { }
	
	//получить индекс конкретного символа
	size_t getIndex(cchar c) { }

	//длина алфавита
	size_t length() { }
};

class TableAlphabet : public Alphabet
{
public:
	size_t tableSize;
	cchar* table;
	std::map<cchar, size_t> reverseTable;

	TableAlphabet(size_t maxSize) : tableSize(maxSize)
	{
		table = new cchar[tableSize];
	}

	TableAlphabet(const TableAlphabet&) = delete;

	~TableAlphabet()
	{
		delete[] table;
	}

	void makeReverseTable()
	{
		reverseTable.clear();
		for (size_t i = 0; i < tableSize; i++)
			reverseTable.insert(std::make_pair(table[i], i));
	}

	//получить конкретный символ
	cchar getChar(size_t index)
	{
		return table[index];
	}

	size_t getIndex(cchar c)
	{
		return reverseTable[c];
	}

	bool contains(cchar c)
	{
		return reverseTable.find(c) != reverseTable.end();
	}

	//длина алфавита
	size_t length()
	{
		return tableSize;
	}
};

class Buffer
{
public:
	size_t size;
	cchar* data;

	Buffer empty_copy() const
	{
		Buffer output;
		output.size = size;
		output.data = new cchar[output.size];
		return output;
	}
};

template <typename ALPHABET> //A - alphabet
class Encryptor
{
protected:

	ALPHABET& alph;

public:

	Encryptor(ALPHABET& alph) : alph(alph)
	{

	}
};