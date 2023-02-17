# Containers

## Description of the task in the project

As part of the project our own library was written that implements the basic standard C++ container classes:
- `list`, `queue`, `stack`, `vector`, `array` (implemented by [ExpectoPatronus](https://github.com/ExpectoPatronus))
- `map`,  `set`, `multiset`

Implementations are provided a full set of standard methods and attributes for element handling, container capacity checking and iteration.

- The program was developed in C++ language of  C++17 standard using template
- Classes were implemented within the `study` namespace
- Container classes methods were full coverage with unit-tests using the GTest library
- The logic of the Standard Template Library (STL) was followed (in terms of checks, memory handling and behaviour in abnormal situations)


## Description of methods

Each type of containers are provided the user with the following methods:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialization list;
- methods for accessing container elements (e.g. accessing an element with the index i);
- methods for checking if a container is full (e.g. the number of elements in the container, check if the container is empty);
- methods for changing the container (removing and adding new elements, cleaning the container);
- methods for dealing with the container iterator.
