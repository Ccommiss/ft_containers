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

}

#endif