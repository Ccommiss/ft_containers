# ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP



// RESSOURCE : https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
// T = le type d'iterateur


// Genereic
namespace ft {
  template <class T>
  struct iterator_traits {
    typedef typename T::value_type            value_type;
    typedef typename T::difference_type       difference_type;
    typedef typename T::iterator_category     iterator_category;
    typedef typename T::pointer               pointer;
    typedef typename T::reference             reference;
  };


  // Pointer specialisqtion
  template <class T>
  struct iterator_traits<T*> {
    typedef T                          value_type; // int  ? char ? etc
    typedef ptrdiff_t                  difference_type;
    typedef ft::random_access_iterator_tag iterator_category; // bidirectionnal ? random ?
    typedef T* pointer;
    typedef T& reference;
  };

  //Thus, for any type "pointer to" "T", it is defined that it has the random access iterator category.
  // A corresponding partial specialization exists for constant pointers (const T*).

// const pointer specialisation
  template <class T>
  struct iterator_traits<const T*> {
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef ft::random_access_iterator_tag  iterator_category;
    typedef const T* pointer;
    typedef const T& reference;
  };





	// SI C DES RANDSOM ACCESS IT ON PEUT FAIRE CA
  template< class InputIt >
  typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
  {
	typename ft::iterator_traits<InputIt>::difference_type  n = 0;
	while (first != last) // pb ici c'est pas l'overload qui s'applique pour le ++ ???? PK
	{
	  	first++;
	  	n++;
	}
    debug("ICI" << last - first);
	return n;
   // return (last - first);
  }

   template < class  T>
  typename ft::iterator_traits<>::difference_type distance(ft::random_access_iterator<> first, ft::random_access_iterator<> last)
  {
	debug ("lol");
  	return (last - first);
//	debug("N IS "<< n)
  //  return n;
  }



}
#endif
