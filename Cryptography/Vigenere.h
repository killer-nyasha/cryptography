#pragma once
#include "Cryptography.h"

template <typename ALPHABET>
class VigenereEncryptor : public Encryptor<ALPHABET>
{
public:
	VigenereEncryptor(ALPHABET& alph) : Encryptor<ALPHABET>(alph)
	{

	}

	Buffer encrypt(Buffer& input, Buffer& _key)
	{
		//заполняем ключ до длины входного текста
		Buffer key = input.empty_copy();
		for (size_t i = 0; i < key.size; i++)
			key.data[i] = _key.data[i % _key.size];

		Buffer output = input.empty_copy();

		for (size_t i = 0; i < input.size; i++)
			if (this->alph.contains(input.data[i]))
				output.data[i] = this->alph.getChar(
					(this->alph.getIndex(input.data[i]) + this->alph.getIndex(key.data[i])) % this->alph.length()
				);
			else output.data[i] = input.data[i];

		return output;
	}

	Buffer decrypt(Buffer& input, Buffer& _key)
	{
		Buffer key = input.empty_copy();
		for (size_t i = 0; i < key.size; i++)
			key.data[i] = _key.data[i % _key.size];

		Buffer output = input.empty_copy();

		for (size_t i = 0; i < input.size; i++)
			if (this->alph.contains(input.data[i]))
				output.data[i] = this->alph.getChar(
				(this->alph.getIndex(input.data[i]) + this->alph.length() - this->alph.getIndex(key.data[i])) % this->alph.length()
				);
			else output.data[i] = input.data[i];

		return output;
	}
};