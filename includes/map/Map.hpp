#include "../includes.hpp"

#ifndef MAP_HPP
#define MAP_HPP

#include "ft_tree.hpp"
#include "ft_pair.hpp"
#include "rb_tree_iterators.hpp"
// stdless : Function object for performing comparisons. Unless specialized, invokes operator< on type T.
namespace ft
{
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator< ft::pair <const Key, T> > >
	class map
	{
	public:
		// types:
		typedef Key														key_type;
		typedef T														mapped_type;
		//typedef ft::pair<const Key, T> 									value_type; //
		// c la mon pb, pour le rendu, decommenter au dessus
		typedef ft::pair< Key, T> 									value_type; //

		typedef Compare													key_compare;
		typedef Allocator 												allocator_type;
		typedef typename Allocator::reference 							reference;
		typedef typename Allocator::const_reference 					const_reference;
		//typedef ft::random_access_iterator<value_type>					iterator;
		typedef ft::_Rb_tree_iterator<value_type> 						iterator;
	// pbmatique : iterator ne peut pas etre un ptr sur paire, mais un ptr sur noeud pour 
	// pvoir iterer 
		typedef ft::random_access_iterator<const value_type>			const_iterator;
		typedef ft::reverse_random_access_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_random_access_iterator<const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::size_type 						size_type;

		typedef typename Allocator::pointer 							pointer;
		typedef typename Allocator::const_pointer 						const_pointer;

	
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
		explicit map(const Compare& c = Compare(), const Allocator& a = Allocator()) : alloc(a), comp(c), _def_value(T())
		{
			_curr = new rb_tree(comp); // creons l'arbre 
		}


		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator & = Allocator());
		map(const map<Key, T, Compare, Allocator>& x);
		~map() {}
		map<Key, T, Compare, Allocator>& operator=(const map<Key, T, Compare, Allocator>& x);

		/*
		** 		ITERATORS
		*/
		iterator begin() {
			return _curr;
		}
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;



		// capacity:
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// 23.3.1.2 element access:
		T& operator[](const key_type& x);
		// {
		// 	return (T[x]);
		// }

		// modifiers:
		// vlue type sera une std pair 
		//pair<iterator, bool> insert(const value_type& x)
		void	insert(const value_type& x)
		{
			_curr->insert(x);
		}

		void debugging()
		{
			_curr->see_tree();
		}

		iterator insert(iterator position, const value_type& x);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		void erase(iterator position);
		size_type erase(const key_type& x);
		void erase(iterator first, iterator last);
		void swap(map<Key, T, Compare, Allocator>&);
		void clear();
		// observers:
		key_compare key_comp() const;
		value_compare value_comp() const;
		// 23.3.1.3 map operations:
		iterator find(const key_type& x)
		{
			return iterator(_curr->find(ft::make_pair<key_type, mapped_type>(x, _def_value))); 
		}
		const_iterator find(const key_type& x) const//
		{
			return const_iterator(_curr->find(ft::make_pair<key_type, mapped_type>(x, _def_value)));  
		}
		size_type count(const key_type& x) const;
		iterator lower_bound(const key_type& x);
		const_iterator lower_bound(const key_type& x) const;
		iterator upper_bound(const key_type& x);
		const_iterator upper_bound(const key_type& x) const;
		pair<iterator, iterator>
			equal_range(const key_type& x);

		pair<const_iterator, const_iterator>
			equal_range(const key_type& x) const;

	private:
		Allocator	alloc;
		/*
		**	@brief comparison function object to use for all comparisons of keys
		*/
		Compare 	comp;
		size_type	_capacity;
		size_type	_size;
		T 			_def_value; // default value whenever we need a pair but we have only a key

		typedef ft::Tree < value_type, value_compare > 	rb_tree; //allacor a rajouter 
		rb_tree* _curr;
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
