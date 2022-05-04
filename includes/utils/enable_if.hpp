
#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

	template <typename T, bool val = false > // par defaut, pas integral
	struct is_integral  {
		const static bool value = val;
	};

	template<> struct is_integral<unsigned char> : public is_integral<unsigned char, true> {};
	template<> struct is_integral<unsigned short> : public is_integral<unsigned short, true> {};
	template<> struct is_integral<unsigned int> : public is_integral<unsigned int, true> {};
	template<> struct is_integral<unsigned long> : public is_integral<unsigned long, true> {};
	template<> struct is_integral<signed char> : public is_integral<signed char, true> {};
	template<> struct is_integral<short> : public is_integral<short, true> {};
	template<> struct is_integral<long> : public is_integral<long, true> {};
	template<> struct is_integral<char> : public is_integral<char, true> {};
	template<> struct is_integral<bool>: public is_integral<bool, true> {};
	template<> struct is_integral<int>: public is_integral<int, true> {};

	template <bool, typename T = void>
		struct enable_if {};

	template <typename T>
	struct enable_if<true, T> {
 		 typedef T type;
	};
}

#endif
