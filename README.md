
<span style="font-weight: bold; font-size:46px; "> 📦 Ft_containers

---

- [Sujet](#sujet)
	- [Partie obligatoire](#partie-obligatoire)
	- [Prérequis](#prérequis)
	- [Test](#test)
- [Documentation](#documentation)
	- [Iterators](#iterators)
		- [Types of iterator and hierarchy](#types-of-iterator-and-hierarchy)
		- [Iterator "superstructure"](#iterator-superstructure)
		- [Why are tags useful?](#why-are-tags-useful)
		- [Iterator traits](#iterator-traits)
		- [Implementing RAI (random access iterators)](#implementing-rai-random-access-iterators)
		- [Lexicographical compare/equal function](#lexicographical-compareequal-function)
	- [What is SFINAE ?](#what-is-sfinae-)
	- [Keywords : explicit, inline ...](#keywords--explicit-inline-)
- [Vectors](#vectors)
		- [Constructors : default, fill or range ?](#constructors--default-fill-or-range-)
- [Map](#map)
		- [Definition](#definition)
	- [Tree](#tree)
		- [From Binary Search Tree (BST)](#from-binary-search-tree-bst)
		- [To Self-Balancing Search Trees](#to-self-balancing-search-trees)


## Sujet

<details open>
<summary> <span style="font-weight: bold; font-size:25px; "> Sujet (dropdown) </span> </summary>

___________

### Partie obligatoire


Implémentez __les containers__ suivants et rendez les fichiers <container>.hpp corres-
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

>Vous pouvez utiliser <https://www.cplusplus.com/>
>et <https://cppreference.com/> comme références.

### Test

• Vous devez aussi fournir vos propres tests, au minimum un main.cpp, pour votre
évaluation. Vous devez pousser plus loin que le main donné en exemple !
• Vous devez créer deux binaires faisant tourner les mêmes tests : l’un avec vos
containers et l’autre avec les containers standards.
• Comparez les sorties et les performances / temps (vos containers peuvent être
jusqu’à 20 fois plus lents que les originaux).
• Pour tester vos containers : ft::<container>.
Un fichier main.cpp est disponible sur la page intranet d
___________
</details>

## Documentation
<https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6>

Allocator
<https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed>

ibterpolation search
<https://medium.com/@vgasparyan1995/interpolation-search-a-generic-implementation-in-c-part-2-164d2c9f55fa>


### Iterators


| Classe |                | Iterateurs     | Description                                               |
| ------ | -------------- | -------------- | --------------------------------------------------------- | --- |
| Vector | Tableau        | Random access  |                                                           |
| List   | Liste          | Bidirectionnal | Collection of nodes, with two pointers, previous and next |
| Map    | Key-value pair | Bidirectionnal | Structure as binary search tree                           | --- |

<http://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__iterator_8h-source.html>

#### Types of iterator and hierarchy
\
\
  ![enter image description here](https://media.geeksforgeeks.org/wp-content/uploads/iterators.png)

*One important thing to be kept in mind is that random-access iterators are also valid bidirectional iterators, as shown in the iterator hierarchy above.*
[__<span style="color: purple;"> Definitions__](https://www.math.hkbu.edu.hk/parallel/pgi/doc/pgC++_lib/stdlibug/var_0565.htm) : </span>


- __Random Access Operator__ : *can access the container also non-sequentially (i.e. by jumping around).*
Some algorithms require more functionality than the ability to access values in either a forward or backward direction. Random access iterators permit values to be accessed by subscript, subtracted one from another (to yield the number of elements between their respective values) or modified by arithmetic operations, all in a manner similar to conventional pointers.
When using conventional pointers, arithmetic operations can be related to the underlying memory; that is, x+10 is the memory ten elements after the beginning of x. With iterators the logical meaning is preserved (x+10 is the tenth element after x), however the physical addresses being described may be different.

- __Bidirectionnal__: *Can scan the container back and forth*
 A bidirectional iterator is similar to a forward iterator, except that bidirectional iterators support the decrement operator (operator --), permitting movement in either a forward or a backward direction through the elements of a container. For example, we can use bidirectional iterators in a function that reverses the values of a container, placing the results into a new container.

#### Iterator "superstructure"

Super lien :
<https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp>

C++ expects some properties from an iterator: (example : we have an Interger class, that will be our container, containing a private int array);

- __iterator_category__ — one of the six iterator categories we have seen above. The full list is available here.
- __difference_type__ — a signed integer type that can be used to identify distance between iterator steps. Our iterator is basically a wrapper around a pointer and leverages pointer arithmetic, so the default std::ptrdiff_t is a good choice;
- __value_type__ — the type the iterator iterates over. int in our case;
- __pointer__ — defines a pointer to the type iterated over. int* in our case;
- __reference__  — defines a reference to the type iterated over. int& in our case;

#### Why are tags useful?

Some of the tags above might seem useless at first. In fact, you will notice how they will never get mentioned during the definition of our iterator. Tags are used to select the most efficient algorithm if your container is passed to one of the Standard Library functions from the *algorithm* library. Wrong tags mean sub-optimal performance! The iterator category is also used to set algorithm requirements, for example: std::fill wants a Forward Iterator, while std::reverse wants a Bidirectional Iterator. Passing the wrong iterator will result in a compilation error.

<https://web.stanford.edu/class/cs107l/handouts/04-Custom-Iterators.pdf>
<http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.38.6443&rep=rep1&type=pdf>

___________

#### Iterator traits

https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits

#### Implementing RAI (random access iterators)

[ a faire ]

#### Lexicographical compare/equal function

No more than a less-than, and an equal comparison. Comparing each iterator.

[More](https://riptutorial.com/cplusplus/example/3820/lexicographical-comparison)


### What is SFINAE ?

___Substitution failure is not an ERROR___

### Keywords : explicit, inline ...

__<span style="color: purple;"> Definitions__ </span>:

- __$Explicit$__ :
> ___In C++, a constructor with only one required parameter is considered an implicit conversion function. It converts the parameter type to the class type.___
>Suppose, you have a class String:
>
> ```class String {
>public:
>    String(int n); // allocate n bytes to the String object
>    String(const char *p); // initializes object with char *p
>};
>```
>
> Now, if you try:
>
>```String mystring = 'x';```
>
>The character 'x' will be implicitly converted to int and then the  String(int) constructor will be called. But, this is not what the user might have intended. So, to prevent such conditions, we shall define the constructor as __explicit__:
>
>```class String {
>public:
>    explicit String (int n); //allocate n bytes
>    String(const char *p); // initialize sobject with string p
>};
> ```

[Source](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)


- __$Inline$__ :

Inline function is mainly used for optimization purpose when calling small functions.
>C++ provides an inline functions to reduce the function call overhead. Inline function is a function that is expanded in line when it is called. When the inline function is called whole code of the inline function gets inserted or substituted at the point of inline function call. This substitution is performed by the C++ compiler at compile time. Inline function may increase efficiency if it is small.

[Source](https://www.geeksforgeeks.org/inline-functions-cpp/)

- __$Using$__ :

- __$Friend$__ :


_____

## Vectors

#### Constructors : default, fill or range ?

- ISO : p482 (490 on PDF), chap. 23.2.4

| Contructeurs                                                                                                          | Declaration                                                             | Parametres      | Description |
| --------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------- | --------------- | ----------- |
| ``` explicit vector (const Allocator& = Allocator());```                                                              | ```std::vector<int> my_vec```                                                  |           Aucun     |             |
| ```explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator())```;                                   | ```std::vector<int> my_vec(x)``` OR ```std::vector<int> my_vec(x, y)``` | un ou deux types integraux | Cree un tableau de x elements valant tous T(), ou bien de la valeur y si specifiee.
| ```template <class InputIterator> vector(InputIterator first, InputIterator last, const Allocator& = Allocator());``` | ```std::vector<int> (other.begin(), other.end())```                    | Deux iterateurs   |


:rotating_light: $~~~$ __Probleme__ : si je cree un vecteur vector(5,8), comment faire pour que le constructeur appele soit bien celui prenant size_type et value, et non inputiterator ? En effet, inputiterator est ici un simple typename.

:bulb: $~~$ __Solution__ : utiliser enable_if.
$~~~~~~~~~~~~~$ :question: $~$  **C'est quoi ?** &nbsp;  Doc : https://en.cppreference.com/w/cpp/types/enable_if
$~~~~~~~~~~~~~$ :sunglasses: $~~$**Explications :** &nbsp;https://www.codeproject.com/Articles/878913/enable-if
$~~~~~~~~~~~~~$ _On aura donc besoin d'un enable_if pour les iterateurs... ou enable_if pour ce qui n'est pas un int !
$~~~~~~~~~~~~~$ En utilisant par ex qqchose comme : std::is_integral a reimplementer.
$~~~~~~~~~~~~~$=> [Doc](https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/types/is_integral.html), [Source code in Boost Library](https://code.woboq.org/appleseed/include/boost/type_traits/is_integral.hpp.html)_

https://eli.thegreenplace.net/2014/sfinae-and-enable_if/ parfaite explication mais c++11

$~~~~~~~~~~~~~$ :warning: &nbsp; Attention, en cpp98, on ne peut pas mettre ca dans le template. Genre ca ```typename = typename std::enable_if<!std::is_integral<InputIterator>::value> ``` qui est ecrit [par ici](https://stackoverflow.com/questions/14035520/choose-which-constructor-in-c)
-> On le resout comme ca  https://stackoverflow.com/questions/17842478/select-class-constructor-using-enable-if



__________

[From SO](https://stackoverflow.com/questions/6296945/size-vs-capacity-of-a-vector)
- __Size__ is not allowed to differ between multiple compilers. The size of a vector is the number of elements that it contains, which is directly controlled by how many elements you put into the vector.

- __Capacity__ is the amount of total space that the vector has. Under the hood, a vector just uses an array. The capacity of the vector is the size of that array. This is always equal to or larger than the size. The difference between them is the number of elements that you can add to the vector before the array under the hood needs to be reallocated.



## Map

#### Definition

- map is a kind of associative container that supports unique keys (contains at most one of each key value) and  provides  for  fast  retrieval  of  values  of  another  type T based  on  the  keys.
- Map supports bidirectional iterators

### Tree

#### From Binary Search Tree (BST)

![Tux, the Linux mascot](/doc_src/180px-Binary_search_tree.svg.png)

- Main principle : **the key in each node is greater than any key stored in the left sub-tree, and less than or equal to any key stored in the right sub-tree** (Wikipedia)
-  the BST property is as follow: For every vertex X, all vertices on the left subtree of X are strictly smaller than X and all vertices on the right subtree of X are strictly greater than X. (https://visualgo.net/en/bst?slide=4-2)
- Conseuqences 
  - Each node has only up to two children


Abstract Data Type (ADT).

#### To Self-Balancing Search Trees

From Wikipedia definition, 

>Self-balancing binary search trees modify the basic insertion and deletion operations of binary search trees, often using additional information on each node, in order to maintain logarithmic depth. These include two early structures of this type, AVL trees, which maintain an invariant that subtree heights differ by at most one, and red–black trees, which instead color nodes red or black and maintain an invariant on the number of colored nodes on each root-to-leaf path.


- Vertex has at least 4 attributes: parent, left, right, key/value/data



