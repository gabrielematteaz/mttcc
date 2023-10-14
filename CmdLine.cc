#include "CmdLine.h"

Mtt::Opt_t::Opt_t()
	: alias('\0'), fs(ARG_TYPE_NONE), arg(NULL)
{

}

Mtt::Opt_t::Opt_t(char alias, int fs, const char *arg)
	: alias(alias), fs(fs), arg(arg)
{

}

char Mtt::Opt_t::Alias() const
{
	return alias;
}

void Mtt::Opt_t::Alias(char alias)
{
	this->alias = alias;
}

int Mtt::Opt_t::Fs() const
{
	return fs;
}

void Mtt::Opt_t::Fs(int fs)
{
	this->fs = fs;
}

const char *Mtt::Opt_t::Arg() const
{
	return arg;
}

void Mtt::Opt_t::Arg(const char *arg)
{
	this->arg = arg;
}

int Mtt::Extr_Optv(int argc, char *argv[], std::size_t optc, Opt_t *optv)
{
	int i;

	if (argv == NULL || optv == NULL)
	{
		i = 0;
	}
	else
	{
		i = 1;

		bool invarg = false;

		while (invarg == false && i < argc)
		{
			if (argv[i] == NULL)
			{
				invarg = true;
			}
			else
			{
				std::size_t j = 0;

				if (argv[i][j] == '-')
				{
					j++;

					if (argv[i][j] == '\0')
					{
						invarg = true;
					}
					else if (argv[i][j] == '-')
					{
						i++;
						invarg = true;
					}
					else
					{
						bool newarg = false;

						do
						{
							bool optfound = false;
							std::size_t k = 0;

							while (optfound == false && k < optc)
							{
								if (argv[i][j] == optv[k].Alias())
								{
									int argtype = optv[k].Fs() & Opt_t::ARG_TYPE_MASK;

									if (argtype == Opt_t::ARG_TYPE_NONE)
									{
										optv[k].Arg(argv[i]);
									}
									else
									{
										j++;

										if (argv[i][j] == '\0')
										{
											i++;

											if (i == argc)
											{
												invarg = true;
											}
											else
											{
												optv[k].Arg(argv[i]);
											}
										}
										else
										{
											optv[k].Arg(argv[i] + j);
										}

										newarg = true;
									}

									optfound = true;
								}

								k++;
							}

							j++;
						} while (newarg == false && argv[i][j]);

						if (invarg == false)
						{
							i++;
						}
					}
				}
				else
				{
					invarg = true;
				}
			}
		}
	}

	return i;
}