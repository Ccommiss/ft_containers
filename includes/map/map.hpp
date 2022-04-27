
#ifndef MAP_HPP
#define MAP_HPP

#include "ft_tree.hpp"
#include "ft_pair.hpp"
#include "rb_tree_iterators.hpp"
//#include "../utils/reverse_iterators.hpp"
#include "reverse_iterators.hpp"
// stdless : Function object for performing comparisons. Unless specialized, invokes operator< on type T.
namespace ft
{
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		// types:
		typedef Key 													key_type;
		typedef T 														mapped_type;
		typedef ft::pair<const Key, T> 									value_type;

		typedef Compare key_compare;
		typedef Allocator allocator_type;
	
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef ft::_Rb_tree_iterator<value_type> 									iterator;
		typedef ft::_Rb_tree_const_iterator<value_type> 							const_iterator;


		// pbmatique : iterator ne peut pas etre un ptr sur paire, mais un ptr sur noeud pour
		// pvoir iterer
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::size_type size_type;

		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		class value_compare;

		typedef typename Allocator::template rebind< ft::Tree<value_type, value_compare, Allocator> >::other _alloctree;



		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		// 23.3.1.1 construct/copy/destroy:
		explicit map(const Compare& c = Compare(), const Allocator& a = Allocator()) : alloc(a), comp(c), _def_value(T()), _curr(rb_tree(comp))
		{
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& c = Compare(), const Allocator &a = Allocator())  :  alloc(a), comp(c), _curr(rb_tree(comp))
		{
			insert(first, last);
		}
		map(const map<Key, T, Compare, Allocator>& x) : alloc(x.alloc), comp(x.comp), _def_value(T()), _curr(rb_tree(comp))
		{
			*this = x;
		}

		~map()
		{
			//delete _curr;
		}

		map<Key, T, Compare, Allocator>& operator=(const map<Key, T, Compare, Allocator>& x)
		{
			erase(begin(), end());
			insert(x.begin(), x.end());
			return (*this);
		}

		/*
		** 		ITERATORS
		*/
		iterator begin()
		{
			return iterator(_curr.getMinSuccessor(_curr.root));
		}
		const_iterator begin() const
		{
			return const_iterator(_curr.getMinSuccessor(_curr.root));
		}
		iterator end()
		{
			return iterator(_curr.nil_node);
		}
		const_iterator end() const
		{
			return const_iterator(_curr.nil_node);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end()); // test
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end()); // test
		}


		reverse_iterator rend()
		{
			return reverse_iterator(begin()); // test pas sure
		}
		const_reverse_iterator rend() const;

		// capacity:
		bool empty() const
		{
			if (_curr._size == 0)
				return true;
			return (false);
		}
		size_type size() const
		{
			return (_curr._size);
		}

		size_type max_size() const
		{
			return (alloc.max_size()); 
		}

		// 23.3.1.2 element access:
		mapped_type& operator[](const key_type& x)
		{
			if (_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value)) != _curr.nil_node)
				return (_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value))->_data.second);
			return (_curr.insert(ft::make_pair<key_type, mapped_type>(x, _def_value))->_data.second);
		}
		/*
		**
		**	@return
		*/
		ft::pair<iterator, bool>  insert(const value_type& x)
		{
			size_type old_size = _curr._size; 
			_curr.insert(x);
			bool success = old_size != _curr._size ? true : false;
			return ft::make_pair(iterator(_curr.find(x)), success);
		}

		void debugging()
		{
			//_curr.display(_curr.getRootPtr());
			//_curr.see_tree();
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
				_curr.insert(ft::make_pair<key_type, mapped_type>(a->first, a->second));
		}
		void erase(iterator position)
		{
			_curr.erase(ft::make_pair<key_type, mapped_type>(position->first, _def_value));
		}

		// retourne le nb d'elem supp 
		size_type erase(const key_type& x)
		{
			if (_curr.erase(ft::make_pair<key_type, mapped_type>(x, _def_value)) == true)
				return 1; // trouver quoi retourner
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			iterator tmp;
			for (iterator a = first; a != last;)
			{
				tmp = a;
				a++;
				_curr.erase(ft::make_pair<key_type, mapped_type>(tmp->first, _def_value));
			}
		}

/*
**
**	@brief Exchanges the content of the container by the content of x, which is another map of the same type. Sizes may differ.
**	@param Another map container of the same type as this 
**	(i.e., with the same template parameters, Key, T, Compare and Alloc) whose content is swapped with that of this container.
*/
		void swap(map<Key, T, Compare, Allocator>& other)
		{
			_curr.swap(other._curr);
		}
		void clear()
		{
			erase(begin(), end());
		}
		// observers:
		key_compare key_comp() const 
		{
			return key_compare();
		}
		value_compare value_comp() const
		{
			return value_compare(comp);
		}
		// 23.3.1.3 map operations:
		iterator find(const key_type& x)
		{
			return iterator(_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value)));
		}
		const_iterator find(const key_type& x) const
		{
			return const_iterator(_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value)));
		}

		/*
		**		Count
		**		@brief  Searches the container for elements with a key equivalent to k and returns the number of matches.
		**		@param x key to search for
		**		@return  1 if the container contains an element whose key is equivalent to k, or zero otherwise.
		*/
		size_type count(const key_type& x) const
		{
			if (_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value)) != _curr.nil_node)
				return 1;
			return 0;
		}
		/*
		** 	1,2) Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
		*/
		iterator lower_bound(const key_type& x)
		{
			iterator it = _curr.find(ft::make_pair(x, _def_value));
			if (it == _curr.nil_node)
			{
				for (iterator new_it = begin(); new_it != end(); new_it++)
				{
					if (new_it->first > x)
					{
						it = new_it;
						break;
					}
				}
			}
			return (it);// == _curr.nil_node ? _curr.nil_node : it);
		}

		const_iterator lower_bound(const key_type& x) const
		{
			const_iterator it(_curr.find(ft::make_pair(x, _def_value)));
			if (it == const_iterator(_curr.nil_node))
			{
				for (const_iterator new_it = begin(); new_it != end(); new_it++)
				{
					if (new_it->first > x)
					{
						it = new_it;
						break;
					}
				}
			}
			return (it);
		}

		/*
		**	1,2) Returns an iterator pointing to the first element that is greater than key.
		*/
		iterator upper_bound(const key_type& x)
		{
			iterator it;
			for (it = begin(); it != end(); it++)
			{
				if (it->first > x)
					break;
			}
			return (it); // == _curr.nil_node ? _curr.nil_node : it);
		}

		const_iterator upper_bound(const key_type& x) const
		{
			const_iterator it;
			for (it = begin(); it != end(); it++)
			{
				if (it->first > x)
					break;
			}
			return (it); // == _curr.nil_node ? _curr.nil_node : it);
		}
		

/*
**	equal_range
** 	@brief  Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
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

	private:
		Allocator alloc;
		_alloctree _tree_alloc; 
		/*
		**	@brief comparison function object to use for all comparisons of keys
		*/
		Compare comp;
		size_type _capacity;
		size_type _size;
		T _def_value; // default value whenever we need a pair but we have only a key

		typedef ft::Tree<value_type, value_compare, Allocator> rb_tree;
		rb_tree _curr;
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator>& lhs, const map<Key, T, Compare, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator>& lhs,
		const map<Key, T, Compare, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
		const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator>& lhs, const map<Key, T, Compare, Allocator>& rhs)
		{
		return (rhs < lhs);
	}
	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>& lhs, const map<Key, T, Compare, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>& lhs,const map<Key, T, Compare, Allocator>& rhs)
	{
		return (!(rhs < lhs));
	}
	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key, T, Compare, Allocator>& lhs, map<Key, T, Compare, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}

};

// https://web.archive.org/web/20160731194845/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/MAP.H
#endif
