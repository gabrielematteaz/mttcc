#include "Fmt.h"

Mtt::Atoi_Fmt_t::Atoi_Fmt_t()
	: plus('+'), minus('-'), fill(' '), base(10), fs(FILLING_LEFT)
{

}

Mtt::Atoi_Fmt_t::Atoi_Fmt_t(char plus, char minus, char fill, int base, int fs)
	: plus(plus), minus(minus), fill(fill), base(base < 2 || base > 36 ? 10 : base), fs(fs)
{

}

char Mtt::Atoi_Fmt_t::Plus() const
{
	return plus;
}

void Mtt::Atoi_Fmt_t::Plus(char plus)
{
	this->plus = plus;
}

char Mtt::Atoi_Fmt_t::Minus() const
{
	return minus;
}

void Mtt::Atoi_Fmt_t::Minus(char minus)
{
	this->minus = minus;
}

char Mtt::Atoi_Fmt_t::Fill() const
{
	return fill;
}

void Mtt::Atoi_Fmt_t::Fill(char fill)
{
	this->fill = fill;
}

int Mtt::Atoi_Fmt_t::Base() const
{
	return base;
}

bool Mtt::Atoi_Fmt_t::Base(int base)
{
	bool valid;

	if (base < 2 || base > 36)
	{
		valid = false;
	}
	else
	{
		this->base = base;
		valid = true;
	}

	return valid;
}

int Mtt::Atoi_Fmt_t::Fs() const
{
	return fs;
}

void Mtt::Atoi_Fmt_t::Fs(int fs)
{
	this->fs = fs;
}

std::size_t Mtt::Atoi_Fmt_t::Conv(const char *str, const char **end) const
{
	std::size_t sign, val = 0;

	if (str == NULL)
	{
		sign = 0;
	}
	else
	{
		int filling = fs & FILLING_MASK;
		std::size_t i = 0;
		char fill = this->fill == '\0' ? '0' : this->fill;

		if (filling == FILLING_INTERNAL)
		{
			if (minus && str[i] == minus)
			{
				sign = -1;
				i++;
			}
			else
			{
				sign = 1;

				if (plus && str[i] == plus)
				{
					i++;
				}
			}

			while (str[i] == fill)
			{
				i++;
			}
		}
		else
		{
			if (filling == FILLING_LEFT)
			{
				while (str[i] == fill)
				{
					i++;
				}
			}

			if (minus && str[i] == minus)
			{
				sign = -1;
				i++;
			}
			else
			{
				sign = 1;

				if (plus && str[i] == plus)
				{
					i++;
				}
			}
		}

		if (base > 10)
		{
			int ltrcase = fs & LTR_CASE_MASK;
			bool invchar = false;

			if (ltrcase == LTR_CASE_UNK)
			{
				char umax = 55 + base, lmax = umax + 32;

				while (invchar == false)
				{
					if ('0' <= str[i] && str[i] <= '9')
					{
						val = val * base + str[i] - '0';
						i++;
					}
					else if ('A' <= str[i] && str[i] < umax)
					{
						val = val * base + str[i] - 55;
						i++;
					}
					else if ('a' <= str[i] && str[i] < lmax)
					{
						val = val * base + str[i] - 87;
						i++;
					}
					else
					{
						invchar = true;
					}
				}
			}
			else
			{
				char min = ltrcase == LTR_CASE_LOWER ? 'a' : 'A', m = min - 10, max = m + base;

				while (invchar == false)
				{
					if ('0' <= str[i] && str[i] <= '9')
					{
						val = val * base + str[i] - '0';
						i++;
					}
					else if (min <= str[i] && str[i] < max)
					{
						val = val * base + str[i] - m;
						i++;
					}
					else
					{
						invchar = true;
					}
				}
			}
		}
		else
		{
			char max = '0' + base;

			while ('0' <= str[i] && str[i] < max)
			{
				val = val * base + str[i] - '0';
				i++;
			}
		}

		str = str + i;
	}

	if (end)
	{
		*end = str;
	}

	return sign * val;
}

void Mtt::Itoa_Fmt_t::Mem_Rev(void *mem, std::size_t n)
{
	if (mem)
	{
		char *m = static_cast < char * > (mem);
		std::size_t i = 0;

		while (i < n)
		{
			char mc = m[i];

			n--;
			m[i] = m[n];
			i++;
			m[n] = mc;
		}
	}
}

Mtt::Itoa_Fmt_t::Itoa_Fmt_t()
	: Atoi_Fmt_t('\0', '-', ' ', 10, FILLING_LEFT | NULL_TERM), width(0)
{

}

Mtt::Itoa_Fmt_t::Itoa_Fmt_t(char plus, char minus, char fill, int base, int fs, std::size_t width)
	: Atoi_Fmt_t(plus, minus, fill, base, fs), width(width)
{

}

std::size_t Mtt::Itoa_Fmt_t::Width() const
{
	return width;
}

void Mtt::Itoa_Fmt_t::Width(std::size_t width)
{
	this->width = width;
}

std::size_t Mtt::Itoa_Fmt_t::Conv(char *str, std::size_t val) const
{
	std::size_t len;

	if (str == NULL)
	{
		if (Minus() && static_cast < std::ptrdiff_t > (val) < 0)
		{
			val = -val;
			len = 1;
		}
		else
		{
			len = Plus() == '\0' ? 0 : 1;
		}

		do
		{
			val /= Base();
			len++;
		} while (val);

		if (len < width)
		{
			len = width;
		}
	}
	else
	{
		bool neg;

		if (Minus() && static_cast < std::ptrdiff_t > (val) < 0)
		{
			val = -val;
			neg = true;
		}
		else
		{
			neg = false;
		}

		len = 0;

		if (Base() > 10)
		{
			char a = (Fs() & LTR_CASE_MASK) == LTR_CASE_LOWER ? 87 : 55;

			do
			{
				std::size_t rem = val % Base();

				val /= Base();
				str[len] = (rem < 10 ? '0' : a) + rem;
				len++;
			} while (val);
		}
		else
		{
			do
			{
				str[len] = '0' + val % Base();
				val /= Base();
				len++;
			} while (val);
		}

		int filling = Fs() & FILLING_MASK;
		std::size_t width = Fill() == '\0' ? 0 : Width();

		if (filling == FILLING_INTERNAL)
		{
			width--;

			while (len < width)
			{
				str[len] = Fill();
				len++;
			}

			if (neg)
			{
				str[len] = Minus();
				len++;
			}
			else if (Plus())
			{
				str[len] = Plus();
				len++;
			}
			else if (len == width)
			{
				str[len] = Width();
				len++;
			}

			Mem_Rev(str, len);
		}
		else if (filling == FILLING_RIGHT)
		{
			if (neg)
			{
				str[len] = Minus();
				len++;
			}
			else if (Plus())
			{
				str[len] = Plus();
				len++;
			}

			Mem_Rev(str, len);

			while (len < width)
			{
				str[len] = Fill();
				len++;
			}
		}
		else
		{
			if (neg)
			{
				str[len] = Minus();
				len++;
			}
			else if (Plus())
			{
				str[len] = Plus();
				len++;
			}

			while (len < width)
			{
				str[len] = Fill();
				len++;
			}

			Mem_Rev(str, len);
		}

		if ((Fs() & NULL_TERM_MASK) == NULL_TERM)
		{
			str[len] = '\0';
		}
	}

	return len;
}