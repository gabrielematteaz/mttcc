#ifndef MTT_STR_H
#define MTT_STR_H

#include <stdexcept>

namespace mtt
{
	enum class fill_mode_t
	{
		LEFT,
		INTERNAL,
		RIGHT
	};

	class fstr_ival_fmt_t
	{
	public:
		char plus, minus;

		char fill;
		fill_mode_t fill_mode;
	
	private:
		int base;
	
	public:
		enum class ltr_case_t
		{
			MIXED,
			UPPER = 1,
			LOWER = 3
		} ltr_case;

		inline fstr_ival_fmt_t() noexcept
			: plus('+'), minus('-'), fill(' '), fill_mode(fill_mode_t::LEFT), base(10), ltr_case(ltr_case_t::MIXED)
		{

		}

		inline fstr_ival_fmt_t(char plus, char minus, char fill, fill_mode_t fill_mode, int base, ltr_case_t ltr_case)
			: plus(plus), minus(minus), fill(fill), fill_mode(fill_mode), base(base < 2 || base > 36 ? throw std::invalid_argument("base") : base), ltr_case(ltr_case)
		{

		}

		inline int get_base() const noexcept
		{
			return base;
		}

		inline bool set_base(int base) noexcept
		{
			if (base < 2 || base > 36) return false;

			this->base = base;

			return true;
		}

		std::size_t conv(const char *fstr, const char **end = nullptr) const noexcept;
	};

	class ival_fstr_fmt_t
	{
	public:
		char plus, minus;

		char fill;
		fill_mode_t fill_mode;
		std::size_t width;
	
	private:
		int base;
	
	public:
		bool lcase;
		bool null_term;

		inline ival_fstr_fmt_t() noexcept
			: plus(0), minus('-'), fill(' '), fill_mode(fill_mode_t::LEFT), width(0), base(10), lcase(false), null_term(true)
		{

		}

		inline ival_fstr_fmt_t(char plus, char minus, char fill, fill_mode_t fill_mode, std::size_t width, int base, bool lcase, bool null_term)
			: plus(plus), minus(minus), fill(fill), fill_mode(fill_mode), width(0), base(base < 2 || base > 36 ? throw std::invalid_argument("base") : base), lcase(lcase), null_term(null_term)
		{

		}

		inline int get_base() const noexcept
		{
			return base;
		}

		inline bool set_base(int base) noexcept
		{
			if (base < 2 || base > 36) return false;

			this->base = base;

			return true;
		}

		std::size_t conv(char *fstr, std::size_t ival) const noexcept;
	};

	void *mem_rev(void *mem, std::size_t n) noexcept;
}

#endif