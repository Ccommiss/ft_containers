

# Ft_containers
---

- [# Ft_containers](#-ft_containers)
	- [Prérequis](#prérequis)
	- [Test](#test)
	- [Iterator "superstructure"](#iterator-superstructure)
		- [Why are tags useful?](#why-are-tags-useful)

##Partie obligatoire


Implémentez les containers suivants et rendez les fichiers <container>.hpp corres-
pondants :
• vector : vous n’avez pas à faire la spécialisation ```vector<bool>```
• map
• stack

Elle utilisera votre classe vector comme container sous-jacent par défaut. Cependant, elle restera compatible avec les autres containers, ceux de la STL inclus.

Vous pouvez valider ce projet sans la stack (80/100).
Cependant, si vous voulez faire la partie bonus, il faudra avoir réalisé les 3 containers obligatoires.
Vous devez aussi implémenter :

- *iterators_traits*
- *reverse_iterator*
- *enable_if*

Oui, il s’agit de C++11 mais vous saurez le refaire en C++98.
Le but est de vous faire découvrir SFINAE.
- *is_integral*
- *equal et/ou lexicographical_compare*
- *std::pair*
- *std::make_pair*

### Prérequis

- Le namespace doit être __ft__.
- La structure de données interne utilisée pour chacun de vos containers doit être cohérente et justifiable (utiliser juste un tableau pour map n’est donc pas accepté).
- Vous ne pouvez pas implémenter plus de fonctions publiques que ne possèdent les containers standards. Toute autre fonction supplémentaire doit être privée ou protégée. Chaque fonction et chaque variable publique doit être justifiée.
- Toutes les fonctions membres, les fonctions non-membres et les surcharges d’un container sont attendues.
- Vous devez vous conformer au nommage original. Faites attention aux détails.
- Si le container possède un système d’itérateur, vous devez l’implémenter.
- Vous devez utiliser std::allocator.
- Pour les surcharges non-membres, __le mot-clé friend est autorisé__. Chaque utilisation de friend doit être justifiée et sera vérifiée en évaluation.
- Bien entendu, pour implémenter map::value_compare, le mot-clé friend est au-
torisé.

>Vous pouvez utiliser https://www.cplusplus.com/
>et https://cppreference.com/ comme références.

### Test
• Vous devez aussi fournir vos propres tests, au minimum un main.cpp, pour votre
évaluation. Vous devez pousser plus loin que le main donné en exemple !
• Vous devez créer deux binaires faisant tourner les mêmes tests : l’un avec vos
containers et l’autre avec les containers standards.
• Comparez les sorties et les performances / temps (vos containers peuvent être
jusqu’à 20 fois plus lents que les originaux).
• Pour tester vos containers : ft::<container>.
Un fichier main.cpp est disponible sur la page intranet d


https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6

Allocator
https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed

ibterpolation search
https://medium.com/@vgasparyan1995/interpolation-search-a-generic-implementation-in-c-part-2-164d2c9f55fa


---


| Classe  |  | Iterateurs | Description |
|---|---|---|---|---|
|Vector   | Tableau | Random access |  |
|List|  Liste| Bidirectionnal |  Collection of nodes, with two pointers, previous and next |
|Map| Key-value pair| Bidirectionnal| Structure as binary search tree|---|


http://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__iterator_8h-source.html 

- __Hierarchie des operateurs__
\
\
  ![enter image description here](https://media.geeksforgeeks.org/wp-content/uploads/iterators.png)

_One important thing to be kept in mind is that random-access iterators are also valid bidirectional iterators, as shown in the iterator hierarchy above._
[__<span style="color: purple;">Definitions__](https://www.math.hkbu.edu.hk/parallel/pgi/doc/pgC++_lib/stdlibug/var_0565.htm) : </span>


- __Random Access Operator__ : _can access the container also non-sequentially (i.e. by jumping around)._
Some algorithms require more functionality than the ability to access values in either a forward or backward direction. Random access iterators permit values to be accessed by subscript, subtracted one from another (to yield the number of elements between their respective values) or modified by arithmetic operations, all in a manner similar to conventional pointers.
When using conventional pointers, arithmetic operations can be related to the underlying memory; that is, x+10 is the memory ten elements after the beginning of x. With iterators the logical meaning is preserved (x+10 is the tenth element after x), however the physical addresses being described may be different.

- __Bidirectionnal__: _Can scan the container back and forth_
 A bidirectional iterator is similar to a forward iterator, except that bidirectional iterators support the decrement operator (operator --), permitting movement in either a forward or a backward direction through the elements of a container. For example, we can use bidirectional iterators in a function that reverses the values of a container, placing the results into a new container.



### Iterator "superstructure"

Super lien :
https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp


C++ expects some properties from an iterator: (example : we have an Interger class, that will be our container, containing a private int array);

- __iterator_category__ — one of the six iterator categories we have seen above. The full list is available here. 
- __difference_type__ — a signed integer type that can be used to identify distance between iterator steps. Our iterator is basically a wrapper around a pointer and leverages pointer arithmetic, so the default std::ptrdiff_t is a good choice;
- __value_type__ — the type the iterator iterates over. int in our case;
- __pointer__ — defines a pointer to the type iterated over. int* in our case;
- __reference__  — defines a reference to the type iterated over. int& in our case;



#### Why are tags useful?

Some of the tags above might seem useless at first. In fact, you will notice how they will never get mentioned during the definition of our iterator. Tags are used to select the most efficient algorithm if your container is passed to one of the Standard Library functions from the <algorithm> library. Wrong tags mean sub-optimal performance! The iterator category is also used to set algorithm requirements, for example: std::fill wants a Forward Iterator, while std::reverse wants a Bidirectional Iterator. Passing the wrong iterator will result in a compilation error.