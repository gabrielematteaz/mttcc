#ifndef MTT_FMT_H
#define MTT_FMT_H

#include <cstddef>

namespace Mtt
{
	class Atoi_Fmt_t
	{
		char plus;
		char minus;
		char fill;
		int base;
		int fs;

	public:
		static const int FILLING_LEFT = 0x0;
		static const int FILLING_INTERNAL = 0x1;
		static const int FILLING_RIGHT = 0x3;
		static const int FILLING_MASK = 0x3;

		static const int LTR_CASE_UNK = 0x0;
		static const int LTR_CASE_UPPER = 0x04;
		static const int LTR_CASE_LOWER = 0xC;
		static const int LTR_CASE_MASK = 0xC;

		Atoi_Fmt_t();
		Atoi_Fmt_t(char plus, char minus, char fill, int base, int fs);

		char Plus() const;
		void Plus(char plus);

		char Minus() const;
		void Minus(char minus);

		char Fill() const;
		void Fill(char fill);

		int Base() const;
		bool Base(int base);

		int Fs() const;
		void Fs(int fs);

		std::size_t Conv(const char *str, const char **end = NULL) const;
	};

	class Itoa_Fmt_t : public Atoi_Fmt_t
	{
		std::size_t width;

		static void Mem_Rev(void *mem, std::size_t n);

	public:
		static const int NULL_TERM = 0x00;
		static const int NULL_TERM_NONE = 0x10;
		static const int NULL_TERM_MASK = 0x10;

		Itoa_Fmt_t();
		Itoa_Fmt_t(char plus, char minus, char fill, int base, int fs, std::size_t width);

		std::size_t Width() const;
		void Width(std::size_t width);

		std::size_t Conv(char *str, std::size_t val) const;
	};
}

#endif