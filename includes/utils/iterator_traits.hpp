# ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include "randomaccessiterator.hpp"

/*
**     ft_containers : iterator_traits
**     @file iterator_traits.p
**     @author ccommiss
*/

namespace ft {


  /*
  ** Generic
  ** @tparam T the type of iterator
  */
  template <class T>
  struct iterator_traits {
    typedef typename T::value_type            value_type;
    typedef typename T::difference_type       difference_type;
    typedef typename T::iterator_category     iterator_category;
    typedef typename T::pointer               pointer;
    typedef typename T::reference             reference;
  };


  /*
  **  Pointer specialisation
  **  @tparam T the type of iterator
  **  @brief  Thus, for any type "pointer to" "T", it is defined that it has the random access iterator category.
  **  A corresponding partial specialization exists for constant pointers (const T*).
  */
  template <class T>
  struct iterator_traits<T*> {
    typedef T                          value_type; // int  ? char ? etc
    typedef ptrdiff_t                  difference_type;
    typedef ft::random_access_iterator_tag iterator_category; // bidirectionnal ? random ?
    typedef T* pointer;
    typedef T& reference;
  };

  /*
  ** Const pointer specialisation
  */
  template <class T>
  struct iterator_traits<const T*> {
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef ft::random_access_iterator_tag  iterator_category;
    typedef const T* pointer;
    typedef const T& reference;
  };


  /*
  **    Distance
  **    @brief computes distance between two iterators
  **    @tparam InputIt type of iterator - not Random Access Iterator
  **    @param two iterators
  **    @return classical random access it : last -first
  **      || if non-RA it : first increments until reaching last
  */
  template< class InputIt >
  typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
  {
    typename ft::iterator_traits<InputIt>::difference_type  n = 0;
    while (first != last) // pb ici c'est pas l'overload qui s'applique pour le ++ ???? PK
    {
      first++;
      n++;
    }
    return (n);
  }

  /*
  **  Distance - specialized
  **  @tparam T type of random access iteratr (string, int...)
  **  @tparam total specialization
  */
  template<typename T >
  typename ft::iterator_traits< ft::random_access_iterator <T> >::difference_type distance(ft::random_access_iterator <T> first, ft::random_access_iterator <T> last)
  {
    return last - first;
  }

}
#endif
