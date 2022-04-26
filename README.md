# ft_containers

[![cboutier's 42 ft_containers Score](https://badge42.vercel.app/api/v2/cl1f9y1k8000609jsc4a29jay/project/2497995)](https://github.com/JaeSeoKim/badge42)

Validated on March 28th, 2022

100/100

Implementing 3 of the STL containers: **Stack**, **Vector** and **Map**, with all its member functions, non-member functions and overloads.  
An AVL Tree was used for the Map container. 
www.cplusplus.com and https://en.cppreference.com/ were used as a reference.  
Complying with the C++98 standard, C++11 features were not implemented.  

**What was implemented:**
- iterators_traits  
- reverse_iterator  
- enable_if  
- is_integral  
- equal + lexicographical_compare  
- std::pair  
- std::make_pair  

Usage:  
`make` will create 2 executables, `ft_containers` (the version we implemented), and `std_containers` (the STL version).  
It will then execute both executables and run a diff on both outputs.  
`./ft_containers` will run the *version we implemented* and show its output.  
`./std_containers` will run the *STL version* and show its output.
