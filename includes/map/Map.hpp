#include "../includes.hpp"

#ifndef MAP_HPP
#define MAP_HPP

#include "ft_tree.hpp"
#include "ft_pair.hpp"
#include "rb_tree_iterators.hpp"
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
		typedef ft::reverse_random_access_iterator<iterator> reverse_iterator;
		typedef ft::reverse_random_access_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::size_type size_type;

		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		struct value_compare;

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
			//_alloctree tree_alloc = _alloctree();
			//_curr = tree_alloc.allocate(1); // on malloc l'arbre 
			//rb_tree ptr = rb_tree(comp);
			//_curr(rb_tree(comp));
					//	out(":)")
			//_curr = 0;
			//tree_alloc.construct(_curr, rb_tree(comp));
			//out("Hola")
			//_curr = rb_tree(comp);
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator & = Allocator());
		map(const map<Key, T, Compare, Allocator>& x);

		~map()
		{
			//delete _curr;
		}
		map<Key, T, Compare, Allocator>& operator=(const map<Key, T, Compare, Allocator>& x)
		{
			if (*this != x || _size != x.size())
			{
				clear();
				_curr->insert(x.begin(), x.end());
			}
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
		const_reverse_iterator rbegin() const;
		reverse_iterator rend()
		{
			return reverse_iterator(begin()); // test pas sure
		}
		const_reverse_iterator rend() const;

		// capacity:
		bool empty() const
		{
			_curr._size == 0 ? true : false;
		}
		size_type size() const
		{
			return (_curr._size);
		}
		size_type max_size() const;

		// 23.3.1.2 element access:
		// T& operator[](const key_type& x)
		// {
		// 	// renvoie une reference sur la pair pointee
		// 	return (_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value))->_data.second);
		// }

		mapped_type& operator[](const key_type& __k)
		{
			// concept requirements
			iterator __i = lower_bound(__k);
			// __i->first is greater than or equivalent to __k.
			if (__i == end() || __i->first == __k ) //key_comp()(__k, (*__i).first))
			{
				__i = _curr.insert(__k);
			}
			return (*__i).second;
		}

		// modifiers:
		// vlue type sera une std pair
		// pair<iterator, bool> insert(const value_type& x)
		void insert(const value_type& x)
		{
			_curr.insert(x);
		}

		void debugging()
		{
			_curr.see_tree();
		}
		iterator insert(iterator position, const value_type& x)
		{
			(void)position;
			_curr.insert(x);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator a = first; a != last; a++)
				_curr.insert(ft::make_pair<key_type, mapped_type>(a->first, a->second));
		}
		void erase(iterator position)
		{
			_curr.del(ft::make_pair<key_type, mapped_type>(position->first, _def_value));
		}
		size_type erase(const key_type& x)
		{
			_curr.del(ft::make_pair<key_type, mapped_type>(x, _def_value));
			return 1; // trouver quoi retourner
		}
		void erase(iterator first, iterator last)
		{
			for (iterator a = first; a != last; a++)
				_curr.del(ft::make_pair<key_type, mapped_type>(a->first, _def_value));
		}
		void swap(map<Key, T, Compare, Allocator>&);
		void clear();
		// observers:
		key_compare key_comp() const;
		value_compare value_comp() const;
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
			std::cout << ft::make_pair<key_type, mapped_type>(x, _def_value) << std::endl;
			std::cout << *(_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value))) << std::cout;
			if (_curr.find(ft::make_pair<key_type, mapped_type>(x, _def_value)) != _curr.nil_node)
				return 1;
			return 0;
		}
		/*
		** 	1,2) Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
		*/
		iterator lower_bound(const key_type& x)
		{
			key_type i = x;
			while (_curr.find(ft::make_pair<key_type, mapped_type>(i, _def_value)) == _curr.nil_node
				&& i < _curr._size) // limite car jamais plus de size elem
				i++;
			iterator it = _curr.find(ft::make_pair<key_type, mapped_type>(i, _def_value));
			return (it == _curr.nil_node ? NULL : it);
		}
		const_iterator lower_bound(const key_type& x) const;

		/*
		**	1,2) Returns an iterator pointing to the first element that is greater than key.
		*/
		iterator upper_bound(const key_type& x)
		{
			key_type i = x + 1;
			while (_curr.find(ft::make_pair<key_type, mapped_type>(i, _def_value)) == _curr.nil_node
				&& i < _curr._size) // limite car jamais plus de size elem
				i++;
			iterator it = _curr.find(ft::make_pair<key_type, mapped_type>(i, _def_value));
			return (it == _curr.nil_node ? NULL : it);
		}

		const_iterator upper_bound(const key_type& x) const;
		pair<iterator, iterator>
			equal_range(const key_type& x);

		pair<const_iterator, const_iterator>
			equal_range(const key_type& x) const;

	private:
		Allocator alloc;
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
	bool operator==(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);
	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key, T, Compare, Allocator>& x,
		map<Key, T, Compare, Allocator>& y);

};

// https://web.archive.org/web/20160731194845/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/MAP.H
#endif
