

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
		typedef typename allocator_type::const_reference 				const_reference; // const &T
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
		**
		**
		*/

		/*
		**	default constructor
		*/
		explicit vector(const Alloc & = Alloc()) { *_curr = T(); }

		/*
		**	Fill constructor constructor
		*/
		explicit vector(size_type n, const T& value = T(), const Alloc & = Alloc(), typename ft::enable_if< ft::is_integral<T>::value >::type* = 0)
		{
			_curr = alloc_obj.allocate(n); // comme un "new", on a malloc ;
			assign(n, value);
		}

		/*
		**	Fill constructor constructor
		*/
		template <class InputIterator >
		vector(InputIterator first, InputIterator last, const Alloc & = Alloc(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
		{
			std::cout << "Range constructor called" << std::endl;
			_curr = alloc_obj.allocate(last - first + 1); // on malloc de la difference d'addresses entre la fin et le debut
		//	_size = last - first + 1;
		//	_capacity = _size;// a test 
			assign(first, last);
		}

		vector(const vector<T, Alloc>& x);
		~vector() {
			std::cout << "Adieu" << std::endl;
		};

		vector<T, Alloc>& operator=(const vector<T, Alloc>& x);

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			//erase(begin(), end());
			///insert(begin(), first, last); 
			(void)last;
			for (unsigned long i = 0; i < _size; i++)
			{
				_curr[i] = *first;
				std::cout << "[RANGE ASSIGN] value at case " << i << " = " << _curr[i] << std::endl;
				*first++;
			}
		}

		//Assign called for fill constructor 
		void assign(size_type n, const T& t)
		{
			//erase(begin(), end());
			insert(begin(), n, t);
		}

		//erase : appelle destroy ;
		// insert
		allocator_type get_allocator() const
		{

		}


		/*
		**	ITERATORS
		*/

		iterator begin()
		{
			return iterator(_curr);
		};
		const_iterator begin() const;
		iterator end()
		{
			return iterator(_curr + (_size + 1));
		};
		const_iterator end() const;
		//reverse_iterator rbegin();
		//const_reverse_iterator rbegin() const;
		//reverse_iterator rend();
		//const_reverse_iterator rend() const;


		/*
		**	SIZE & CAPACITY
		*/

		size_type size() const { return (_size); }
		size_type max_size() const;
		void resize(size_type sz, T c = T())
		{
			if (sz > size())
				insert(end(), sz - size(), c);
			else if (sz < size())
				erase(begin() + sz, end());
			else
				;
		}
		size_type capacity() const { return (_capacity); }
		bool empty() const {
			if (_size == 0) return true; return false;
		}
		void reserve(size_type n);

		/*
		**
		**	ELEMENT ACCESS
		**
		*/
		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		const_reference at(size_type n) const;
		reference at(size_type n);
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		/*
		** 23.2.4.3 MODIFIERS:
		*/

		void push_back(const T& x)
		{
			_curr.insert(_curr.end(), x);
		}
		void pop_back();

		/*
		**	INSERT :
		**	Causes reallocation if the new size is greater than the old capacity.
		**	If no reallocation happens, all
		**	the iterators and references before the insertion point remain valid.
		**	If an exception is thrown other than
		**	by the copy constructor or assignment operator of T there are no effects.
		*/
		iterator insert(iterator position, const T& x)
		{
			pointer 			_new_curr;

			_new_curr = alloc_obj.allocate(_size + 1); //on rajout une size en plus
			iterator it = iterator(_curr); // iterateur sur begin

			for (size_type i = 0; i < _size; i++) // on copie sauf si on arrive a l'iterateur
			{
				if (it != position)
					_new_curr[i] = _curr[i];
				else
					_new_curr[i] = x;
				it++;
			}
			_curr = _new_curr; // deallocate avant !! 
			return (it); // pas le bon retourn !! chercher !!! 
		}

		void insert(iterator position, size_type n, const T& x)
		{
			pointer 			_new_curr;
			size_type 			new_elems = n;
			size_type 			i = 0;

			_new_curr = alloc_obj.allocate(_size + n); //on rajout n size en plus car n x t vont etre add 
			iterator it = iterator(_curr);
			for (size_type j = 0; j < _size + new_elems; j++)
			{
				// on copie sauf si on arrive a l'iterateur
				if (it != position) // test...
					_new_curr[j] = _curr[i];
				else
				{
					i -= 1;
					for (;n > 0; n--)
						_new_curr[j++] = x;
					j -= 1;
				}
				it++;
				i++;
			}
			_curr = _new_curr; // deallocate avant !!
			_size += new_elems;
			//_capacity += new_elems; revoir les calculs de cpacite 
		}
		//template <class InputIterator>
		//void insert(iterator position, InputIterator first, InputIterator last);

		/*
		**	ERASE :
		**  Invalidates all the iterators and references after the point of the erase.
		*/
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector<T, Alloc>&);
		void clear();

		private:
		pointer 		_curr; // pointeur sur le tableau, premiere addresse
		size_t  		_size; // le nb d'elemts contenus
		size_t			_capacity; // la taille allouee 
		allocator_type	alloc_obj; // pour utiliser le meme objet a chaque fois sans le refaire 
	};
}

# endif
