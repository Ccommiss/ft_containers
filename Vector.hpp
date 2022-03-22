

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include "includes.hpp"


//template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {

		public:


		/*
		**	TYPEDEFS
		*/

		typedef T 														value_type; // alais
		typedef Alloc													allocator_type; //alias
		typedef typename allocator_type::reference						reference; // &T
		typedef typename allocator_type::const_reference 				const_referenc; // const &T
		typedef typename allocator_type::pointer 						pointer; // T*
		typedef typename allocator_type::const_pointer 					const_pointer;
		/* Les iterateurs */
		typedef ft::random_access_iterator<value_type>					iterator;
		typedef ft::random_access_iterator<const value_type>			const_iterator;
		// 		typedef ft::random_access_iterator<value_type> reverse_iterator;
		//		typedef ft::random_access_iterator<const value_type> const_reverse_iterator;

		/* Diff type & size_type */
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 	difference_type;
		typedef typename allocator_type::size_type 						size_type; // std::allocator, vaut size_t

		/*
		**	CONTRUCTORS
		*/
		//empty
		explicit vector(const Alloc & = Alloc())
		{
			*_curr = T();
		}
		//fill constructor
		//template < >
		explicit vector(size_type n, const T& value = T(), const Alloc & = Alloc(), typename ft::enable_if< ft::is_integral<T>::value >::type* = 0)
		{
			// _ M_create_storage, l 300, renvoie sur M allocate
			std::cout << "Fill constructor called" << std::endl;
			allocator_type		alloc_obj;
			_curr = alloc_obj.allocate(n); // comme un "new", on a malloc ;
			std::cout << "allocated" << std::endl;
			_size = n;
			std::cout << "VALUE : " << value << std::endl;
			assign(n, value);
		}

	//Answer : https://stackoverflow.com/questions/17842478/select-class-constructor-using-enable-if
	//range
		template <class InputIterator >
		vector(InputIterator first, InputIterator last, const Alloc & = Alloc(), typename ft::enable_if< ft::is_integral<T>::value >::type* = 0)
		{
			std::cout << "Range constructor called" << std::endl;
			(void)first;
			(void)last;
			//assign(first, last);
		}

		vector(const vector<T, Alloc>& x);
		~vector() {
			std::cout << "Adieu" << std::endl;
		};

		vector<T, Alloc>& operator=(const vector<T, Alloc>& x);

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			erase(begin(), end());
			insert(begin(), first, last);
		}

		void assign(size_type n, const T& t)
		{
			//erase(begin(), end());
			//insert(begin(), n, t);
			for (unsigned long i = 0; i < n; i++)
			{
				_curr[i] = t;
				std::cout << _curr[i] << std::endl;
			}
		}

		//erase : appelle destroy ;
		// insert
		allocator_type get_allocator() const
		{

		}


		// iterators:
		iterator begin()
		{
			return iterator(_curr);
		};
		const_iterator begin() const;
		iterator end()
		{
			return iterator(_curr + (_size - 1));
		};
		const_iterator end() const;
		//reverse_iterator rbegin();
		//const_reverse_iterator rbegin() const;
		//reverse_iterator rend();
		//const_reverse_iterator rend() const;


		// 23.2.4.2 capacity:
		size_type size() const;
		size_type max_size() const;
		void resize(size_type sz, T c = T());
		size_type capacity() const;
		bool empty() const;
		void reserve(size_type n);

	private:
		pointer _curr; // pointeur sur le tableau, premiere addresse
		size_t  _size; // la taille n allouee
	};
}

# endif
