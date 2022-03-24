#include "includes.hpp"

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <typeinfo> // ASUPPRIEMR  

void 		findtype(std::string info)
{
	std::cout << "Current type is : ";
	if (info == typeid(int*).name()) { debug("pointer on int"); }
	else if (info == typeid(int).name()) { debug("int"); }
	else if (info == typeid(std::string*).name()) { debug("pointer on string"); }
	else if (info == typeid(unsigned int*).name()) { debug("pointer on unsigned int"); }
	else if (info == typeid(std::vector<int> *).name()) { debug("pointer on vector<int>"); }
	else if (info == typeid(std::vector<std::string> *).name()) { debug("pointer on vector<std::string>"); }
	else { debug(info) };
}


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
		typedef ft::reverse_random_access_iterator<value_type> 			reverse_iterator;
		typedef ft::reverse_random_access_iterator<const value_type>	const_reverse_iterator;

		/* Diff type & size_type */
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 	difference_type;
		typedef typename allocator_type::size_type 											size_type; // std::allocator, vaut size_t


		/* ****************************************************
		**	COPLIAN STUFF
		**
		**
		**
		**/

		/*
		**	Default constructor
		*/
		explicit vector(const Alloc & = Alloc()) : _size(0), _capacity(0) {}; //*_curr = T(); }

		/*
		**	Fill constructor
		*/
		explicit vector(size_type n, const T& value = T(), const Alloc & = Alloc()) : _size(0), _capacity(0) //, typename ft::enable_if< ft::is_integral<T>::value >::type* = 0) : _size(0), _capacity(0)
		{
			debug("[Fill constructor]");
			findtype(typeid(this->_curr).name());
			_curr = alloc_obj.allocate(n); // comme un "new", on a malloc ;
			assign(n, value);
		}

		void assign(size_type n, const T& t)
		{
			erase(begin(), end());
			insert(begin(), n, t);
		}


		/*
		**	Range constructor
		*/
		template <class InputIterator >
		vector(InputIterator first, InputIterator last, const Alloc & = Alloc(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0) : _size(0), _capacity(0)
		{
			debug("[Range constructor]");
			findtype(typeid(this->_curr).name());
			_curr = alloc_obj.allocate(last - first + 1); // on malloc de la difference d'addresses entre la fin et le debut
			assign(first, last);
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{

			erase(begin(), end());
			insert(begin(), first, last);
		}

		/*
		** 		Copy constructors
		*/
		vector(const vector<T, Alloc>& x) : _size(0), _capacity(0)
		{
			*this = x;
		}

		/*
		**	Destructor
		*/

		~vector() {
			debug("[~Destructor]");
			if (_capacity > 0)
				alloc_obj.deallocate(_curr, _capacity);
		};

		/*
		**	Operator = overload
		*/

		vector<T, Alloc>& operator=(const vector<T, Alloc>& x) // TEST POUR LE RESERVE 
		{
			//if (*this != x) // a recoder car pas de comparaisons entre const et non const
			//{

				this->assign(x.begin(), x.end());
			//}
			return (*this);
		}

		allocator_type get_allocator() const
		{

		}


		/* ****************************************************
		**	ITERATORS
		**
		**
		**
		**/

		/*
		**	Begin
		**	@brief returns iterator on first elem
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
		**	rbegin
		**	@brief
		*/
		reverse_iterator rbegin()
		{
			return reverse_iterator(_curr + _size);
		}
		//const_reverse_iterator rbegin() const;
		reverse_iterator rend()
		{
			return reverse_iterator(_curr); // ca devrait etre + 1 pour aller plus a la fin ?? mais utilise pas mon implemde reverse ????? 
		}
		//const_reverse_iterator rend() const;



		/* ****************************************************
		**	SIZE AND CAPACITY
		**
		**
		**
		**/

		size_type size() const { return (_size); }
		size_type max_size() const { return (alloc_obj.max_size()); };
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
		bool empty() const { if (_size == 0) return true; return false; }


		/**
		 *  @brief  Attempt to preallocate enough memory for specified number of
		 *          elements.
		 *  @param  __n  Number of elements required.
		 *  @throw  std::length_error  If @a n exceeds @c max_size().
		 *
		 *  This function attempts to reserve enough memory for the
		 *  %vector to hold the specified number of elements.  If the
		 *  number requested is more than max_size(), length_error is
		 *  thrown.
		 *
		 *  The advantage of this function is that if optimal code is a
		 *  necessity and the user can determine the number of elements
		 *  that will be required, the user can reserve the memory in
		 *  %advance, and thus prevent a possible reallocation of memory
		 *  and copying of %vector data.
		 */


		 /*
		 ** memcpy
		 **	@param &tmp the pointer we want to fill with _curr values
		 **	@return none
		 */
		void 	memcpy(pointer& tmp) const
		{
			iterator it;
			size_t i = 0;
			for (it = begin(); it != end(); it++) // on fait une copie mais c degueu
			{
				tmp[i] = _curr[i];
				i++;
			}
		}

		void 	memcpy(pointer& tmp)
		{
			iterator it;
			size_t i = 0;
			for (it = begin(); it != end(); it++) // on fait une copie mais c degueu
			{
				tmp[i] = _curr[i];
				i++;
			}
		}

		void reserve(size_type n)
		{
			iterator it;

			if (n > max_size())
				throw (std::out_of_range("Reserve error : cannot allocate more than max_size"));
			if (n > _capacity)
			{
				pointer tmp = alloc_obj.allocate(n); // on alloue
				memcpy(tmp); //va copier l'instance cournte dans tmp 
				alloc_obj.deallocate(_curr, _capacity); // on peut desallouer l'instance courante
				_curr = tmp;
				_capacity = n;
			}
		}
		/* ****************************************************
		**	ELEMENT ACCESS
		**
		**
		**
		**/


		/*
		** 	@brief access
		**	@param n the index we want to access
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
		reference front()
		{
			return (_curr[0]);
		}
		const_reference front() const;
		reference back()
		{
			return (_curr[_size - 1]);
		}
		const_reference back() const;

		/* ****************************************************
		**	MODIFIERS
		**	- push_back
		**	- pop_back
		**	- insert
		**	- erase
		**
		**/

		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void pop_back()
		{
			erase(end() - 1);
		}

		/*
		**	INSERT :
		**	Causes reallocation if the new size is greater than the old capacity.
		**	If no reallocation happens, all
		**	the iterators and references before the insertion point remain valid.
		**	If an exception is thrown other than
		**	by the copy constructor or assignment operator of T there are no effects.
		*/

		int	compute_capacity(int n)
		{
			int i = 2;
			while (_capacity < _size + n)
			{
				if (_capacity >= 1)
					_capacity = _size * i; 
				else if (_capacity == 0 || _size == 0)
				{
					_capacity += _size + n;
				}
				i++;
			}
			return _capacity; // test 
		}

		iterator insert(iterator position, const T& x)
		{
			int new_size = compute_capacity(1);
			pointer _new_curr = alloc_obj.allocate(new_size); //on rajout une size en plus;
			size_t j = 0;
			iterator it = iterator(_curr); // iterateur sur begin

			for (size_type i = 0; i < _size + 1; i++) // on copie sauf si on arrive a l'iterateur
			{
				if (it != position)
					_new_curr[i] = _curr[j++];
				else
					_new_curr[i] = x;
				it++;
			}
			alloc_obj.deallocate(_curr, _capacity);
			_curr = _new_curr;
			_size += 1;
			return (it); // pas le bon retourn !! chercher !!! 
		}

		void insert(iterator position, size_type n, const T& x)
		{
			pointer 			_new_curr;
			size_type 			new_elems = n;
			size_type 			i = 0;

			int new_size = compute_capacity(n);
			debug ("NEW SIZE RESIZE = " << new_size)
			_new_curr = alloc_obj.allocate(new_size); //on rajout n size en plus car n x t vont etre add 
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
			alloc_obj.deallocate(_curr, _capacity);
			_curr = _new_curr; // deallocate avant !!
			_size += new_elems;
		}

		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
		{
			iterator it = iterator(_curr);
			InputIterator start = InputIterator(first);
			size_t i = 0;
			size_t diff = ft::distance(first, last);
			int old_capacity = _capacity; // capacite au debut 
			int new_size = compute_capacity(diff);
			pointer _new_curr = alloc_obj.allocate(new_size);

			for (size_type j = 0; j < _size + diff; j++) // last - first = diff type qui sera la taille;
			{
				if (it != position) // test...
					_new_curr[j] = _curr[i];
				else
				{
					i -= 1;
					for (size_t n = diff; n > 0; n--)
					{
						alloc_obj.construct(_new_curr + j, *start++);
						j++;
					}
					j -= 1;
				}
				it++;
				i++;
			}
			if (old_capacity != 0) // A REMETTRE PARTOUT
				alloc_obj.deallocate(_curr, _capacity);
			_size += diff;
			_curr = _new_curr;
		}

		/*
		**	ERASE :
		**  @brief Invalidates all the iterators and references after the point of the erase.
		*/
		iterator erase(iterator position)
		{
			int i		= ft::distance(begin(), position);
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


		iterator erase(iterator first, iterator last)
		{
			if (_capacity == 0) // rien a effacer
				return (iterator(_curr));
			size_t diff = ft::distance(first, last);
			pointer _new_curr = alloc_obj.allocate(_capacity); // on enleve un range 
			iterator it = iterator(_curr);
			// On copie tant que < a la size actuelle car on aura un elem en moins 
			size_t j = 0;
			for (size_type i = 0; i < _size;)
			{
				if (it != first)
				{
					_new_curr[j++] = _curr[i];
					it++;
					i++;
				}
				else // on est tombe sur le premier
				{
					while (it != last)
					{
						it++;
						i++; // on skip 
					}
				}
			}
			if (_capacity != 0)
				alloc_obj.deallocate(_curr, _capacity);
			_curr = _new_curr;
			_size -= diff;
			return (it);
		}

		void	dealloc()
		{
			if (_capacity > 0)
				alloc_obj.deallocate(_curr, _capacity);
			_capacity = 0;
			_size = 0;
		}

		void swap(ft::vector<T, Alloc>& other) // copier this dans  le deuxiemn 
		{
			ft::vector<T> tmp(*this);
			this->dealloc();
			this->assign(other.begin(), other.end());
			other.dealloc();
			other.assign(tmp.begin(), tmp.end());
		}
		void clear();


		class sz_max : public std::exception
		{
			virtual const char* what() const throw()
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
		pointer 		_curr; // pointeur sur le tableau, premiere addresse
		size_t  		_size; // le nb d'elemts contenus
		size_t			_capacity; // la taille allouee 
		allocator_type	alloc_obj; // pour utiliser le meme objet a chaque fois sans le refaire 
	};
}


# endif
