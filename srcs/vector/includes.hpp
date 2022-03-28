# ifndef INCLUDES_HPP
# define INCLUDES_HPP


#include <cstddef>
#include <iostream>

/* FOREGROUND */
#define BBOLD "\x1B[1m"
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST
#define DIM(x)	"\033[2m" x RST

// "\033[{FORMAT_ATTRIBUTE};{BACKGROUND};{FOREGROUND}m{TEXT}\033[{RESET_FORMATE_ATTRIBUTE}m"
#define FG1(x)		"\033[4;30;33m" x RST
#define FG2(x)		"\033[4;32;40m" x RST
#define HEADER(x)	"\033[1;107;35m" x RST

//#define debug(x)	std::cout << x << std::endl;
#define debug(x)

#define color(x)	"\033[1;96m" x RST
//#define ENDL			endl;

//#define test(x)		std::cout << color("============================\n") << color(x) << color("\n============================")  << std::endl;

//cout << HEADER("\n**** TESTS INSERT ****") << endl;

//void	print(std::string func);
#	include <vector>
#	include <memory>
#   include "enable_if.hpp"
#	include "iterator.hpp"
#	include "reverse_iterators.hpp"
# 	include	"randomaccessiterator.hpp"
# 	include "iterator_traits.hpp"
#	include "relationnal_operators_tools.hpp"

#	include "Vector.hpp"



# endif
