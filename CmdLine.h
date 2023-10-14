#ifndef MTT_CMDLINE_H
#define MTT_CMDLINE_H

#include <cstddef>

namespace Mtt
{
	class Opt_t
	{
		char alias;
		int fs;
		const char *arg;

	public:
		static const int ARG_TYPE_NONE = 0x0;
		static const int ARG_TYPE_OPTIONAL = 0x1;
		static const int ARG_TYPE_REQUIRED = 0x3;
		static const int ARG_TYPE_MASK = 0x3;

		Opt_t();
		Opt_t(char alias, int fs = ARG_TYPE_NONE, const char *arg = NULL);

		char Alias() const;
		void Alias(char alias);

		int Fs() const;
		void Fs(int fs);

		const char *Arg() const;
		void Arg(const char *arg);
	};

	int Extr_Optv(int argc, char *argv[], std::size_t optc, Opt_t *optv);
}

#endif