#include "String.h"

std::size_t Matteaz::StringToValueFormat::Convert(const char *string, const char **end) const noexcept
{
	if (string == nullptr)
	{
		if (end) *end = nullptr;

		return 0;
	}

	char stringChar = *string;
	std::size_t sign;

	if (fill)
	{
		if (fillMode == FillMode::INTERNAL)
		{
			if (minus && stringChar == minus)
			{
				string++;
				stringChar = *string;
				sign = -1;
			}
			else
			{
				if (plus && stringChar == plus)
				{
					string++;
					stringChar = *string;
				}

				sign = 1;
			}

			while (stringChar == fill)
			{
				string++;
				stringChar = *string;
			}
		}
		else
		{
			if (fillMode == FillMode::LEFT)
			{
				while (stringChar == fill)
				{
					string++;
					stringChar = *string;
				}
			}

			if (minus && stringChar == minus)
			{
				string++;
				stringChar = *string;
				sign = -1;
			}
			else
			{
				if (plus && stringChar == plus)
				{
					string++;
					stringChar = *string;
				}

				sign = 1;
			}
		}
	}
	else
	{
		if (minus && stringChar == minus)
		{
			string++;
			stringChar = *string;
			sign = -1;
		}
		else
		{
			if (plus && stringChar == plus)
			{
				string++;
				stringChar = *string;
			}

			sign = 1;
		}
	}

	std::size_t value = 0;

	if (base > 10)
	{
		char difference;

		if (letterCase == LetterCase::MIXED)
		{
			char uppercaseMaximum = 55 + base, lowercaseMaximum = uppercaseMaximum + 32;

			while (true)
			{
				if (stringChar >= '0' && stringChar <= '9') difference = '0';
				else if (stringChar >= 'A' && stringChar < uppercaseMaximum) difference = 55;
				else if (stringChar >= 'a' && stringChar < lowercaseMaximum) difference = 87;
				else break;

				string++;
				value = value * base + stringChar - difference;
				stringChar = *string;
			}
		}
		else
		{
			char letterCaseMinimum = letterCase == LetterCase::LOWER ? 'a' : 'A', letterCaseDifference = letterCaseMinimum - 10, letterCaseMaximum = letterCaseDifference + base;

			while (true)
			{
				if (stringChar >= '0' && stringChar <= '9') difference = '0';
				else if (stringChar >= letterCaseMinimum && stringChar < letterCaseMaximum) difference = letterCaseDifference;
				else break;

				string++;
				value = value * base + stringChar - difference;
				stringChar = *string;
			}
		}
	}
	else
	{
		char maximum = '0' + base;

		while (stringChar >= '0' && stringChar < maximum)
		{
			string++;
			value = value * base + stringChar - '0';
			stringChar = *string;
		}
	}

	if (end) *end = string;

	return sign * value;
}

std::size_t Matteaz::ValueToStringFormat::Convert(char *string, std::size_t value) const noexcept
{
	std::size_t length;

	if (string)
	{
		bool negative;

		if (minus && IS_NEGATIVE_VALUE(value))
		{
			value = -value;
			negative = true;
		}
		else negative = false;

		char *stringCopy = string;

		if (base > 10)
		{
			char letterCaseA = lowercase ? 87 : 55;

			do
			{
				char reminder = value % base;

				value /= base;
				*stringCopy = (reminder < 10 ? '0' : letterCaseA) + reminder;
				stringCopy++;
			} while (value);
		}
		else
		{
			do
			{
				*stringCopy = '0' + value % base;
				value /= base;
				stringCopy++;
			} while (value);
		}

		if (fill)
		{
			char *stringAtWidth;

			if (fillMode == FillMode::INTERNAL)
			{
				stringAtWidth = string + width - 1;

				while (stringCopy < stringAtWidth)
				{
					*stringCopy = fill;
					stringCopy++;
				}

				if (negative)
				{
					*stringCopy = minus;
					stringCopy++;
				}
				else if (plus)
				{
					*stringCopy = plus;
					stringCopy++;
				}
				else if (stringCopy == stringAtWidth)
				{
					*stringCopy = fill;
					stringCopy++;
				}

				length = stringCopy - string;
				ReverseMemory(string, length);
			}
			else if (fillMode == FillMode::RIGHT)
			{
				if (negative)
				{
					*stringCopy = minus;
					stringCopy++;
				}
				else if (plus)
				{
					*stringCopy = plus;
					stringCopy++;
				}

				ReverseMemory(string, stringCopy - string);
				stringAtWidth = string + width;

				while (stringCopy < stringAtWidth)
				{
					*stringCopy = fill;
					stringCopy++;
				}

				length = stringCopy - string;
			}
			else
			{
				if (negative)
				{
					*stringCopy = minus;
					stringCopy++;
				}
				else if (plus)
				{
					*stringCopy = plus;
					stringCopy++;
				}

				stringAtWidth = string + width;

				while (stringCopy < stringAtWidth)
				{
					*stringCopy = fill;
					stringCopy++;
				}

				length = stringCopy - string;
				ReverseMemory(string, length);
			}
		}
		else
		{
			if (negative)
			{
				*stringCopy = minus;
				stringCopy++;
			}
			else if (plus)
			{
				*stringCopy = plus;
				stringCopy++;
			}

			length = stringCopy - string;
			ReverseMemory(string, length);
		}

		if (nullTerminate) *stringCopy = 0;
	}
	else
	{
		if (minus && IS_NEGATIVE_VALUE(value))
		{
			value = -value;
			length = 1;
		}
		else length = plus ? 1 : 0;

		do
		{
			value /= base;
			length++;
		} while (value);

		if (length < width) length = width;
	}

	return length;
}

void *Matteaz::ReverseMemory(void *memory, std::size_t size) noexcept
{
	if (memory)
	{
		char *charMemory = (char *)memory, *reverseCharMemory = charMemory + size;

		while (charMemory < reverseCharMemory)
		{
			reverseCharMemory--;

			char memoryChar = *charMemory;

			*charMemory = *reverseCharMemory;
			charMemory++;
			*reverseCharMemory = memoryChar;
		}
	}

	return memory;
}