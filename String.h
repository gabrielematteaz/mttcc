#ifndef MATTEAZ_STRING_H
#define MATTEAZ_STRING_H

#include <stdexcept>

#define IS_NEGATIVE_VALUE(value) (value & (std::size_t)1 << (sizeof(value) * CHAR_BIT - 1))

namespace Matteaz
{
	enum class FillMode
	{
		LEFT,
		INTERNAL,
		RIGHT
	};

	class StringToValueFormat
	{
	public:
		char plus, minus;

		char fill;
		FillMode fillMode;

	private:
		int base;

	public:
		enum class LetterCase
		{
			MIXED,
			UPPER,
			LOWER
		} letterCase;

		inline StringToValueFormat() noexcept
			: plus('+'), minus('-'), fill(' '), fillMode(FillMode::LEFT), base(10), letterCase(LetterCase::MIXED)
		{

		}

		inline StringToValueFormat(char plus, char minus, char fill, FillMode fillMode, int base, LetterCase letterCase)
			: plus(plus), minus(minus), fill(fill), fillMode(fillMode), base(base < 2 || base > 36 ? throw std::invalid_argument("base") : base), letterCase(letterCase)
		{

		}

		inline int GetBase() const noexcept
		{
			return base;
		}

		inline bool SetBase(int base) noexcept
		{
			if (base < 2 || base > 36) return false;

			this->base = base;

			return true;
		}

		std::size_t Convert(const char *string, const char **end = nullptr) const noexcept;
	};

	class ValueToStringFormat
	{
	public:
		char plus, minus;
	
		char fill;
		FillMode fillMode;
		std::size_t width;

	private:
		int base;
	
	public:
		bool lowercase;
		bool nullTerminate;

		inline ValueToStringFormat() noexcept
			: plus(0), minus('-'), fill(' '), fillMode(FillMode::LEFT), width(0), base(10), lowercase(false), nullTerminate(true)
		{

		}

		inline ValueToStringFormat(char plus, char minus, char fill, FillMode fillMode, std::size_t width, int base, bool lowercase, bool nullTerminate)
			: plus(plus), minus(minus), fill(fill), fillMode(fillMode), width(width), base(base < 2 || base > 36 ? throw std::invalid_argument("base") : base), lowercase(lowercase), nullTerminate(nullTerminate)
		{

		}

		inline int GetBase() const noexcept
		{
			return base;
		}

		inline bool SetBase(int base) noexcept
		{
			if (base < 2 || base > 36) return false;

			this->base = base;

			return true;
		}

		std::size_t Convert(char *string, std::size_t value) const noexcept;
	};

	void *ReverseMemory(void *memory, std::size_t size) noexcept;
}

#endif