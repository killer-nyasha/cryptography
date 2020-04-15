#pragma once
//аффинный шифр

#include "Cryptography.h"

template <typename T>
inline T gcd(T a, T b) 
{
	while (a != b) 
	{
		if (a > b) 
			std::swap(a, b);
		b = b - a;
	}
	return a;
}

template <typename T>
inline T find_a_minus_one(T a, T m)
{
	T a_minus_one = 1;
	while (1 != a * a_minus_one % m)
		a_minus_one++;
	return a_minus_one;
}

template <typename ALPHABET>
class AffineEncryptor : public Encryptor<ALPHABET>
{
public:
	AffineEncryptor(ALPHABET& alph) : Encryptor<ALPHABET>(alph)
	{

	}

	Buffer encrypt(Buffer& input, size_t a, size_t b)
	{
		if (gcd(a, this->alph.length()) > 1)
			std::wcout << L"Неверно выбрано \"a\" в аффинном шифре. Оно должно быть взаимно простым с длиной алфавита.";

		Buffer output = input.empty_copy();

		for (size_t i = 0; i < input.size; i++)
			if (this->alph.contains(input.data[i]))
				output.data[i] = this->alph.getChar
				(
					((a * this->alph.getIndex(input.data[i])) + b) % this->alph.length()
				);
			else output.data[i] = input.data[i];


		return output;
	}

	Buffer decrypt(Buffer& input, size_t a, size_t b)
	{
		if (gcd(a, this->alph.length()) > 1)
			std::wcout << L"Неверно выбрано \"a\" в аффинном шифре. Оно должно быть взаимно простым с длиной алфавита.";

		size_t a_minus_one = find_a_minus_one(a, this->alph.length());

		Buffer output = input.empty_copy();

		for (size_t i = 0; i < input.size; i++)
			if (this->alph.contains(input.data[i]))
			{
				output.data[i] = this->alph.getChar
				(
					(a_minus_one * (this->alph.length() + this->alph.getIndex(input.data[i]) - b)) % this->alph.length()
				);
			}
			else output.data[i] = input.data[i];

		return output;
	}
};