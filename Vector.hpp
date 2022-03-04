#include <allocator>


struct bidirectional_iterator_tag {}


template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>



template < class T, class Alloc = std::allocator<T> >
class vector {

	vector();
	~vector();

	typedef value_type		T;
	typedef allocator_type	Alloc;
	typedef reference 		allocator_type::reference;
	typedef const_reference allocator_type::const_reference;
	typedef pointer			allocator_type::pointer;
	typedef const_pointer 	allocator_type::const_pointer;
	//typedef iterator		//mon random access


}
