
#ifndef set_HPP
#define set_HPP

#include "ft_tree.hpp"
#include "ft_pair.hpp"
#include "relationnal_operators_tools.hpp"
#include "rb_tree_iterators.hpp"
#include "reverse_iterators.hpp"

namespace ft
{
	template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> > 
	class set
	{
	public:
		typedef Key 																key_type;
		typedef Key																	value_type;
		typedef Compare 															key_compare;
		typedef Compare 															value_compare;
		typedef Allocator 															allocator_type;
		typedef typename Allocator::reference 										reference;
		typedef typename Allocator::const_reference 								const_reference;
		typedef ft::_Rb_tree_iterator<value_type> 									iterator;
		typedef ft::_Rb_tree_const_iterator<value_type> 							const_iterator;
		typedef ft::reverse_iterator<iterator> 										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
		typedef typename allocator_type::size_type									size_type;
		typedef typename Allocator::pointer 										pointer;
		typedef typename Allocator::const_pointer									const_pointer;


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
		explicit set(const Compare& c = Compare(), const Allocator& a = Allocator()) : alloc(a), comp(c), _def_value(Key()), _curr(rb_tree(comp)) {}

		/*
		**	Range constructor
		*/		
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const Compare& c = Compare(), const Allocator &a = Allocator())  :  alloc(a), comp(c), _curr(rb_tree(comp))
		{
			insert(first, last);
		}

		/*
		** 	Copy constructor
		*/
		set(const set<Key, Compare, Allocator>& x) : alloc(x.alloc), comp(x.comp), _def_value(Key()), _curr(rb_tree(comp))
		{
			*this = x;
		}

		/*
		**	Destructor
		*/
		~set() {}

		/*
		**	Operator = overload
		*/
		set<Key, Compare, Allocator>& operator=(const set<Key, Compare, Allocator>& x)
		{
			if (*this != x || _size != x.size())
			{
				erase(begin(), end());
				insert(x.begin(), x.end());
			}
			return (*this);
		}

		allocator_type get_allocator() const
		{
			return Allocator();
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
			return iterator(_curr.getMinSuccessor(_curr.root));
		}

		const_iterator begin() const
		{
			return const_iterator(_curr.getMinSuccessor(_curr.root));
		}

		/*
		**	End
		**	@brief returns iterator on last elem + 1
		*/
		iterator end()
		{
			return iterator(_curr.nil_node);
		}

		const_iterator end() const
		{
			return const_iterator(_curr.nil_node);
		}

		/*
		**	Rbegin
		**	@brief
		**	@return Reverse iterator to the first element from the end.
		*/
		reverse_iterator rbegin()
		{
			return reverse_iterator(end()); 
		}
	
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end()); 
		}

		/*
		**	Rend
		**	@brief
		**	@return Reverse iterator to the last element from the end.
		*/
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		/* ****************************************************
		**	📏 SIZE 
		** ****************************************************
		**
		** 	├── 📏 Size
		** 	│ ├── size
		** 	│ ├── max_size
		**	│ └── empty
		**	└──
		*/
		size_type size() const
		{
			return (_curr._size);
		}

		size_type max_size() const
		{
			return (alloc.max_size()); 
		}

		bool empty() const
		{
			if (_curr._size == 0)
				return true;
			return (false);
		}

		/* ****************************************************
		**	💄 MODIFIERS
		** ****************************************************
		**
		** 	├── insert
		** 	│ ├── single : insert (const value_type& val)
		** 	│ ├── single position : insert (iterator position, const value_type& x)
		**	│ └── range : insert (InputIterator first, InputIterator last);
		** 	├── erase
		** 	│ ├── single : erase(const key_type& x)
		** 	│ ├── single : erase (iterator position)
		**	│ └── range : erase (iterator first, iterator last);
		** 	├── swap
		**	└── clear
		*/

		/*
		**	insert
		**	@return pair <iterator, bool> where it = the iterator on the found object, and bool equivalent 
		**	to false or true if found.
		*/
		ft::pair<iterator, bool>  insert(const value_type& x)
		{
			size_type old_size = _curr._size; 
			_curr.insert(x);
			bool success = old_size != _curr._size ? true : false;
			return ft::make_pair(iterator(_curr.find(x)), success);
		}

		iterator insert(iterator position, const value_type& x)
		{
			(void)position;
			return iterator(_curr.insert(x));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator a = first; a != last; a++)
				_curr.insert(*a);
		}
	
		/*
		** 	Erase
		**	@brief erase 
		**	@param x key to be deleted 
		**	@param first,last range of its to be deleted
		**	@return 1 if key is deleted, 0 otherwise.
		*/
		size_type erase(const key_type& x)
		{
			if (_curr.erase(x) == true)
				return 1; 
			return 0;
		}
	
		void erase(iterator position)
		{
			_curr.erase(*position);
		}

		void erase(iterator first, iterator last)
		{
			iterator tmp;
			for (iterator a = first; a != last;)
			{
				tmp = a;
				a++;
				_curr.erase(*tmp);
			}
		}

		/*
		**	Swap
		**	@brief Exchanges the content of the container by the content of x, which is another set of the same type. Sizes may differ.
		**	@param Another set container of the same type as this 
		**	(i.e., with the same template parameters, Key,  Compare and Alloc) whose content is swapped with that of this container.
		*/
		void swap(set<Key, Compare, Allocator>& other)
		{
			_curr.swap(other._curr);
		}

		/*
		**	Clear 
		**	@brief Remove all elements from set
		*/
		void clear()
		{
			erase(begin(), end());
		}

		/* ****************************************************
		**	👀 OBSERVERS
		** ****************************************************
		**
		** 	├── key_comp
		**	└── value_comp
		*/

		/*
		** 	Keycomp and Value Comp : return object passed as param 
		** 
		*/
		key_compare key_comp() const 
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(comp);
		}

		/* ****************************************************
		**	👀 set OPERATIONS 
		** ****************************************************
		**
		** 	├── find
		** 	├── count
		** 	├── bounds
		** 	│ ├── lower_bound
		**	│ └── upper_bound
		**	└── equal_range
		*/

		/*
		**	Find
		**	@brief find an element by its key
		**	@param k the key to be searched for 
		*/
		iterator find(const key_type& x)
		{
			return iterator(_curr.find(x));
		}

		const_iterator find(const key_type& x) const
		{
			return const_iterator(_curr.find(x));
		}

		/*
		**		Count
		**		@brief  Searches the container for elements with a key equivalent to k and returns the number of matches.
		**		@param x key to search for
		**		@return  1 if the container contains an element whose key is equivalent to k, or zero otherwise.
		*/
		size_type count(const key_type& x) const
		{
			if (_curr.find(x) != _curr.nil_node)
				return 1;
			return 0;
		}

		/*
		**	Lower_bound
		** 	@brief Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
		**	@param k the key to search for
		*/
		iterator lower_bound(const key_type& x)
		{
			iterator it = _curr.find(x);
			if (it == _curr.nil_node)
			{
				for (iterator new_it = begin(); new_it != end(); new_it++)
				{
					if (*new_it > x)
					{
						it = new_it;
						break;
					}
				}
			}
			return (it);
		}
	
		const_iterator lower_bound(const key_type& x) const
		{
			const_iterator it = (_curr.find(x));
			if (it == const_iterator(_curr.nil_node))
			{
				for (const_iterator new_it = begin(); new_it != end(); new_it++)
				{
					if (*new_it > x)
					{
						it = new_it;
						break;
					}
				}
			}
			return (it);
		}

		/*
		**	Upper_bound
		**	@brief Returns an iterator pointing to the first element that is greater than key.
		** 	@param k the key to search for
		*/
		iterator upper_bound(const key_type& x)
		{
			iterator it;
			for (it = begin(); it != end(); it++)
			{
				if (*it > x)
					break;
			}
			return (it);
		}
		const_iterator upper_bound(const key_type& x) const
		{
			const_iterator it;
			for (it = begin(); it != end(); it++)
			{
				if (*it > x)
					break;
			}
			return (it);
		}

		/*
		**	equal_range
		** 	@brief  Returns the bounds of a range that includes all the elements in the container which 
		**		have a key equivalent to k.
		** 	@param k - key to search for
		*/
		pair<iterator, iterator>
		equal_range(const key_type& x)
		{
			return(ft::make_pair(lower_bound(x), upper_bound(x)));
		}

		pair<const_iterator, const_iterator>
		equal_range(const key_type& x) const
		{
			return(ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x)));
		}

	template <class K, class Comp, class Alloc>
	friend bool operator==(const set<K, Comp, Alloc>& lhs, const set<K,  Comp, Alloc>& rhs);
	template <class K,  class Comp, class Alloc>
	friend bool operator<(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs);

	private:
		Allocator 		alloc;
		Compare 		comp;
		size_type 		_capacity;
		size_type		_size;
		Key 			_def_value;
		typedef 		ft::Tree < value_type, value_compare, Allocator > rb_tree;
		rb_tree 		_curr;
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

	template <class Key, class Compare, class Allocator>
	void swap(set<Key,  Compare, Allocator>& lhs, set<Key,  Compare, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
	template <class Key,  class Compare, class Allocator>
	bool operator==(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class Key,  class Compare, class Allocator>
	bool operator!=(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Key,  class Compare, class Allocator>
	bool operator<(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class Key,  class Compare, class Allocator>
	bool operator>(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return (rhs < lhs);
	}
	template <class Key,  class Compare, class Allocator>
	bool operator>=(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key,  class Compare, class Allocator>
	bool operator<=(const set<Key,  Compare, Allocator>& lhs,const set<Key,  Compare, Allocator>& rhs)
	{
		return (!(rhs < lhs));
	}
};

#endif
