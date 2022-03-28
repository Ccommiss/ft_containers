#include "includes.hpp"

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>

#include <typeinfo> // ASUPPRIEMR

void findtype(std::string info)
{
	(void)info;
	// std::cout << "Current type is : ";
	// if (info == typeid(int*).name()) { debug("pointer on int"); }
	// else if (info == typeid(int).name()) { debug("int"); }
	// else if (info == typeid(std::string*).name()) { debug("pointer on string"); }
	// else if (info == typeid(unsigned int*).name()) { debug("pointer on unsigned int"); }
	// else if (info == typeid(std::vector<int> *).name()) { debug("pointer on vector<int>"); }
	// else if (info == typeid(std::vector<std::string> *).name()) { debug("pointer on vector<std::string>"); }
	// else { debug(info) };
}

namespace ft
{

	/*
	**	vector
	**	@brief
	**	@tparam T The type of the elements.
	**	@tparam Alloc An allocator that is used to acquire/release memory
	**			and to construct/destroy the elements in that memory.
	*/
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
		/*
		**	TYPEDEFS
		*/

		typedef T value_type;											  // alais
		typedef Alloc allocator_type;									  // alias
		typedef typename allocator_type::reference reference;			  // &T
		typedef typename allocator_type::const_reference const_reference; // const &T
		typedef typename allocator_type::pointer pointer;				  // T*
		typedef typename allocator_type::const_pointer const_pointer;
		/* Les iterateurs */
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_random_access_iterator<value_type> reverse_iterator;
		typedef ft::reverse_random_access_iterator<const value_type> const_reverse_iterator;

		/* Diff type & size_type */
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type; // std::allocator, vaut size_t

		/* ****************************************************
		**	🛠 Coplian form
		** ****************************************************
		** 	├── 👩🏻‍🔧 Contructors
		** 	│   ├── default
		** 	|	├── fill
		** 	|	├── range
		** 	│   └── copy
		** 	├── 🔨 Destructor
		** 	└── ⚖️ Overload operator=
		*/

		/*
		**	Default constructor
		*/
		explicit vector(const Alloc & = Alloc()) : _curr(0), _size(0), _capacity(0) {}

		/*
		**	Fill constructor
		*/
		explicit vector(size_type n, const T &value = T(), const Alloc & = Alloc()) : _size(0), _capacity(0) //, typename ft::enable_if< ft::is_integral<T>::value >::type* = 0) : _size(0), _capacity(0)
		{
			debug("[Fill constructor]");
			findtype(typeid(this->_curr).name());
			//_curr = alloc_obj.allocate(n); // comme un "new", on a malloc ;
			_curr = 0; // comme un "new", on a malloc ;
			assign(n, value); 
		}

		/*
		**	Range constructor
		*/
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const Alloc & = Alloc(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) : _size(0), _capacity(0)
		{
			debug("[Range constructor]");
			findtype(typeid(this->_curr).name());
			//_curr = alloc_obj.allocate(last - first + 1); // on malloc de la difference d'addresses entre la fin et le debut
			//_curr = alloc_obj.allocate(0);
			_curr = 0;
			assign(first, last);
		}

		/*
		** 		Copy constructors
		*/
		vector(const vector<T, Alloc> &x) : _size(0), _capacity(0)
		{
			*this = x;
		}

		/*
		**	Destructor
		*/
		~vector()
		{
			//std::cout << "HEHO" << std::endl;
			//if (_capacity > 0)
			clear();
			alloc_obj.deallocate(_curr, _capacity);
		};

		/*
		**	Operator = overload
		*/
		vector<T, Alloc> &operator=(const vector<T, Alloc> &x) // TEST POUR LE RESERVE
		{
			// if (*this != x) // a recoder car pas de comparaisons entre const et non const
			//{
			this->assign(x.begin(), x.end());
			//}
			return (*this);
		}

		allocator_type get_allocator() const
		{
		}

		/* ****************************************************
		**	🚀 ITERATORS
		** ****************************************************
		**
		** 	├── iterator
		** 	│ ├── begin
		** 	│ ├── cbegin
		** 	│ ├── end
		**	│ └── cend
		** 	├── reverse_iterators
		** 	| ├── rbegin
		** 	| ├── crbegin
		** 	│ ├── rend
		**	│ └── crend
		**	└──
		*/

		/*
		**	Begin
		**	@brief returns iterator to the first elem
		**	@return iterator or const_iterator to the first elem
		*/
		iterator begin()
		{
			return iterator(_curr);
		}
		const_iterator begin() const
		{
			return const_iterator(_curr);
		}

		/*
		**	End
		**	@brief returns iterator on last elem
		*/
		iterator end()
		{
			return iterator(_curr + _size);
		}
		const_iterator end() const
		{
			return const_iterator(_curr + _size);
		}

		/*
		**	Rbegin
		**	@brief
		**	@return Reverse iterator to the first element.
		*/
		reverse_iterator rbegin()
		{
			return reverse_iterator(_curr + _size);
		}
		const_reverse_iterator rbegin() const;

		/*
		**	Rend
		**	@brief
		**	@return Reverse iterator to the last element.
		*/
		reverse_iterator rend()
		{
			return reverse_iterator(_curr); // ca devrait etre + 1 pour aller plus a la fin ?? mais utilise pas mon implemde reverse ?????
		}
		const_reverse_iterator rend() const;

		/* ****************************************************
		**	📏 SIZE AND CAPACITY
		** ****************************************************
		**
		** 	├── 📏 Size
		** 	│ ├── size
		** 	│ ├── max_size
		** 	│ ├── resize
		**	│ └── empty
		** 	├── 📦 Capacity
		** 	| ├── capacity
		**	│ └── reserve
		**	└──
		*/

		/*
		**	Size
		**
		** 	@brief Returns the number of elements in the container,
		**	i.e. std::distance(begin(), end()).
		**	@return The number of elements in the container.
		*/
		size_type size() const { return (_size); }

		/*
		**	Max_size
		**
		** 	@brief Returns the maximum number of elements the container
		**	is able to hold due to system or library implementation limitations,
		**	i.e. std::distance(begin(), end()) for the largest container.
		**	@return The number of elements in the container.
		*/
		size_type max_size() const { return (alloc_obj.max_size()); };

		/*
		**	Resize
		**
		**	@brief Resizes the container so that it contains sz elements.
		**	@details n < the current container size: the content is
		**		reduced to its first n elements, removing those beyond.
		**	Otherwise, the content is expanded by inserting at the end
		**		until reaching a size of n
		**	@param sz New container size, expressed in number of elements.
		**	@param c Object whose content is copied to the added elements in case that n is greater
		**		than the current container size.
		**	@iterator_validity :
		**		- if container shrinks, all iterators, pointers and references
		**			to elements that have not been removed remain valid after the
		**			resize
		**		- if the container expands, the end iterator is invalidated and,
		**			if it has to reallocate storage, all iterators, pointers and references
		**			related to this container are also invalidated.
		*/
		void resize(size_type sz, T c = T())
		{
			if (sz > size())
				insert(end(), sz - size(), c);
			else if (sz < size())
				erase(begin() + sz, end());
			else
				;
		}

		/*
		**	Empty
		**	@brief Test whether vector is empty
		**	@return true or false
		*/
		bool empty() const
		{
			if (_size == 0)
				return true;
			return false;
		}

		/*
		**	Capacity
		**	@brief  Return size of allocated storage capacity
		**	@return size of allocated storage capacity
		*/
		size_type capacity() const { return (_capacity); }

		/*
		** memcpy
		**	@param &tmp the pointer we want to fill with _curr values
		**	@return none
		*/
		void memcpy(pointer &tmp) const
		{
			iterator it;
			size_t i = 0;
			for (it = begin(); it != end(); it++, i++) // on fait une copie mais c degueu
			{
				tmp[i] = _curr[i];
			}
		}
		void memcpy(pointer &tmp)
		{
			iterator it;
			size_t i = 0;
			for (it = begin(); it != end(); it++) // on fait une copie mais c degueu
			{
				tmp[i] = _curr[i];
				i++;
			}
		}

		/*
		**	Reserve
		**
		** 	@brief  Attempt to preallocate enough memory for specified number of
		** 	        elements.
		** 	@param  n  Number of elements required.
		**	@details if n > capacity, reallocation happens. Otherwise,
		**		no reallocation happens and capacity is not affected.
		** 	@throw  std::length_error if n exceeds max_size().
		**	@iterator_validity if reallocation happens, all iterators,
		**	pointers and references related to the container are invalidated.
		**	Otherwise, no change.
		*/
		void reserve(size_type n)
		{
			iterator it;

			int old_capacity = _capacity;
			if (n > max_size())
				throw(std::out_of_range("vector::reserve"));
			if (n > _capacity)
			{
				pointer tmp = alloc_obj.allocate(compute_capacity(n)); // on alloue
				memcpy(tmp);										   // va copier l'instance cournte dans tmp
				if (old_capacity > 0)
					alloc_obj.deallocate(_curr, old_capacity); // on peut desallouer l'instance courante
				_curr = tmp;
			}
		}

		/* ****************************************************
		**	🚪 ELEMENT ACCESS
		** ****************************************************
		**
		** 	├── operator[]
		** 	├── at
		** 	├── front
		**	└── back
		*/

		/*
		**	operator[]
		**
		** 	@brief access nth index of vector container
		**	@param n position of an element in the container
		**	@return a reference to the element at position n in the vector container.
		**	@throw nothing if the container size is greater than n, the function never throws exceptions (no-throw guarantee).
		**	Otherwise, the behavior is undefined.
		*/
		reference operator[](size_type n)
		{
			return (_curr[n]);
		}
		const_reference operator[](size_type n) const;

		/*
		**	at()
		**
		**	@brief
		**	@param n position of an element in the container
		**	@return a reference to the element at position n in the vector.
		** 	@throw out_of_range if n >= a.size()
		*/
		const_reference at(size_type n) const;
		reference at(size_type n)
		{
			if (n <= _size)
				return (_curr[n]);
			else
				throw std::out_of_range("out of range exception because n > size");
		}

		/*
		**	front
		**
		**	@brief Returns a reference to the first element in the vector.
		**	@return a reference to the first element in the vector container.
		*/
		reference front() { return (_curr[0]); }
		const_reference front() const;

		/*
		**	back
		**
		**	@brief Returns a reference to the last element in the vector.
		**	@return a reference to the last element in the vector container.
		*/
		reference back() { return (_curr[_size - 1]); }
		const_reference back() const;

		/* ****************************************************
		**	💄 MODIFIERS
		** ****************************************************
		**
		**	├── assign
		** 	│ ├── fill : assign(size_type n, const T &t)
		**	│ └── range :assign(InputIterator first, InputIterator last)
		** 	├── push_back
		** 	├── pop_back
		** 	├── insert
		** 	│ ├── single : insert (iterator position, const value_type& val)
		** 	│ ├── fill : insert (iterator position, size_type n, const value_type& val)
		**	│ └── range : insert (iterator position, InputIterator first, InputIterator last);
		** 	├── erase
		** 	│ ├── single : erase (iterator position)
		**	│ └── range : erase (iterator first, iterator last);
		** 	├── swap
		**	└── clear [TO DO]
		*/

		/*
		**  (1) assign( size_type n, const T& value );
		**
		**	@brief replaces the contents with n copies of value value
		**	@param n the new size of the container
		**	@param t the value to initialize elements of the container with
		*/
		void assign(size_type n, const T &t)
		{
			erase(begin(), end());
			insert(begin(), n, t);
		}

		/*
		**  (2) assign( InputIt first, InputIt last );
		**
		**	@brief Replaces the contents with copies of those in the range [first, last).
		**	The behavior is undefined if either argument is an iterator into *this.
		**	@param n the new size of the container
		**	@param t the value to initialize elements of the container with
		*/
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			erase(begin(), end());
			insert(begin(), first, last);
		}

		/*
		** 	Push back
		**
		** 	@brief Add element at the end
		** 	@iterator_validity invalidated if reallocation, no change otherwise
		*/
		void push_back(const T &x)
		{
			insert(end(), x);
		}

		/*
		** 	Pop back
		**
		** 	@brief Remove element at the end
		**	@iterator_validity only end iterator is invalidated
		*/
		void pop_back()
		{
			erase(end() - 1);
		}

		// custom
		int compute_capacity(unsigned long n)
		{
			if (_capacity < _size + n)
			{
				if (n > _size * 2)
					_capacity = _size + n;
				else
					_capacity = _size * 2;
			}
			return _capacity;
		}

		/*
		**	Insert
		**
		**	@brief
		**	@param position Position in the vector where the new elements are inserted
		**	@param x Value to be copied (or moved) to the inserted elements.

		**	@param first,last Iterators specifying a range of elements. Copies of the elements
		**	in the range [first,last) are inserted at position (in the same order).
		**	Notice that the range includes all the elements between first and last, including
		**	the element pointed by first but not the one pointed by last.
		**
		**	@details Causes reallocation if the new size is greater than the old capacity.
		** 	@iterator_validity invalidated if reallocation, no change otherwise
		**	@return iterator pointing to the first element inserted
		*/

		/*
		**	(1) insert single elem
		**	@brief insert one element at specified position
		**	@param position Position in the vector where the new elements are inserted
		**	@param x Value to be copied (or moved) to the inserted elements.
		** 	@iterator_validity invalidated if reallocation, no change otherwise
		**	@return  An iterator that points to the first of the newly inserted elements.
		*/
		iterator insert(iterator position, const T &x)
		{
			
			unsigned long start = ft::distance(begin(), position);
			int i = size();
			reserve(_size + 1);
			while (--i >= (int)start) // on decale le cas echeant
				alloc_obj.construct(_curr + i + 1, *(_curr + i));
			alloc_obj.destroy(_curr + start);
			alloc_obj.construct(_curr + start, x);
			_size += 1;
			return (iterator(_curr + start));
		}

		/*
		**	(2) fill insert
		**	@brief insert n element at specified position
		**	@param position Position in the vector where the new elements are inserted
		**	@param x Value to be copied (or moved) to the inserted elements.
		**	@param n Number of elements to insert. Each element is initialized to a copy of val.		**	@return  An iterator that points to the first of the newly inserted elements.
		** 	@iterator_validity invalidated if reallocation, no change otherwise
		*/
		void insert(iterator position, size_type n, const T &x)
		{
			
			unsigned long start = ft::distance(begin(), position);
			int i = size();
			reserve(_size + n);
			while (--i >= (int)start)
				alloc_obj.construct(_curr + i + n, *(_curr + i));
			for (unsigned long j = 0; j < n; j++, start++) // on a diff elems a copier
			{
				alloc_obj.destroy(_curr + start);
				alloc_obj.construct(_curr + start, x);
			}
			_size += n;
		}

		/*
		**	(3) inserts elements from range [first, last) before pos.
		**	@brief insert n element at specified position
		**	@param position Position in the vector where the new elements are inserted
		**	@param x Value to be copied (or moved) to the inserted elements.
		**	@param n Number of elements to insert. Each element is initialized to a copy of val.		**	@return  An iterator that points to the first of the newly inserted elements.
		** 	@iterator_validity invalidated if reallocation, no change otherwise
		*/
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			unsigned long diff = ft::distance(first, last);
			unsigned long start = ft::distance(begin(), position);
			int i = size();
			reserve(diff + _size);

			while (--i >= 0) // pq 0 et pas start et ca marche ???????????
				alloc_obj.construct(_curr + i + diff, *(_curr + i));
			for (unsigned long j = 0; j < diff; j++, start++) // on a diff elems a copier
			{
				alloc_obj.destroy(_curr + start);
				alloc_obj.construct(_curr + start, *(first + j));
			}
			_size += diff;
		}

		/*
		**	(1) Erase - single elem
		**
		**  @brief Invalidates all the iterators and references after the point of the erase.
		**	@param pos iterator to the element to remove
		**	@return iterator following the last removed element.
		**	If pos refers to the last element, then the end() iterator is returned.
		*/
		iterator erase(iterator position)
		{
			int i = ft::distance(begin(), position);
			iterator it = position + 1;
			while (it != end())
			{
				alloc_obj.destroy(_curr + i);
				alloc_obj.construct(_curr + i, *it);
				it++;
				i++;
			}
			_size -= 1;
			return (position);
		}

		/*
		**	(2) Erase - range
		**
		**  @brief Removes the elements in the range [first, last).
		**	@param first,last range of elements to remove
		**	@throw none unless an exception is thrown by the assignment operator of T.
		**	@return iterator following the last removed element.
		**	If pos refers to the last element, then the end() iterator is returned.
		*/
		iterator erase(iterator first, iterator last)
		{
			int i = ft::distance(begin(), first);
			int step = ft::distance(first, last) - 1;
			if (step <= 0)
				return (first);
			iterator it = first + 1;
			while (it != end())
			{
				alloc_obj.destroy(_curr + i);
				if (last != end() && i + step < (int)_size)
					alloc_obj.construct(_curr + i, *(it + step));
				it++;
				i++;
			}
			_size -= step + 1;
			return (first); // ??
		}

		void dealloc()
		{
			if (_capacity > 0)
				alloc_obj.deallocate(_curr, _capacity);
			_capacity = 0;
			_size = 0;
		}

		/*
		** 	Swap
		**
		**	@briefExchanges the contents of the container with those of other. Does not
		**	invoke any move, copy, or swap operations on individual elements.
		**	@param other another container of vector type to exchange the contents with
		** 	@iterator_validity iterators, pointers and references referring to elements
		**	in both containers remain valid, and are now referring to the same elements
		**	they referred to before the call, but in the other container,
		**	where they now iterate.
		**	Note that the end iterators do not refer to elements and may be invalidated.
		*/
		void swap(vector &other)
		{
			std::swap(_curr, other._curr);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
		}

		/*
		**	Clear
		**	@brief Erases all elements from the container. After this call,
		**	size() returns zero.
		**
		**	Invalidates any references, pointers, or iterators referring to contained elements.
		**	Any past-the-end iterators are also invalidated.
		*/
		void clear()
		{
			erase(begin(), end());
		}

		class sz_max : public std::exception
		{
			virtual const char *what() const throw()
			{
				std::cout << "Cannot allocate mor than max size" << std::endl;
			}
		};

		/* ****************************************************
		**	PRIVATE ELEMS
		**
		**
		**/
	private:
		pointer _curr;			  // pointeur sur le tableau, premiere addresse
		size_t _size;			  // le nb d'elemts contenus
		size_t _capacity;		  // la taille allouee
		allocator_type alloc_obj; // pour utiliser le meme objet a chaque fois sans le refaire
	};

	/* ****************************************************
	**	NON MEMBERS FUNCTIONS
	** ****************************************************
	**
	** 	├── 🔄 Swap
	** 	├── Relational Operators - using equal, lexicographical
	** 	  ├── ==
	** 	  ├── !=
	** 	  ├── <, <=
	** 	  └── >, >=
	**
	** operation	equivalent operation
	**	a!=b	|	!(a==b)
	**	a>b		|	b<a
	**	a<=b	|	!(b<a)
	**	a>=b	|	!(a<b)
	**/
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}



/*
** a == b 
*/
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		
		return (ft::equal(lhs.begin(), rhs.begin(), lhs.end()));
	}

/*
** 	a != b  
*/
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}


/*
**	 a < b
*/
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin()));
	}

/*
**  a <= b ===> !(b < a)
*/
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

/*
**  a > b ===> b < a
*/
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

/*
**  a>=b	|	!(a<b)
*/
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}


}

#endif
