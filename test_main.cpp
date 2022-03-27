// map::value_comp
#include <iostream>
#include <map>
#include "Vector.hpp"

int main ()
{
  	std::cout << std::endl << "RESIZE TESTS" << std::endl;
	ft::vector<int> test(12, 12);

	std::cout << "1s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(72);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;

  return 0;
}

// // map::key_comp
// #include <iostream>
// #include <map>

// int main ()
// {
//   std::map<char,int> mymap;

//   std::map<char,int>::key_compare mycomp = mymap.key_comp();

//   mymap['c']=100;
//   mymap['d']=200;
//   mymap['a']=300;
//   mymap['b']=400;

//   std::cout << "mymap contains:\n";

// //   char highest = mymap.rbegin()->first;     // key value of last element
//   char highest = 'c';     // key value of last element
//   std::cout << "highest : " << highest << std::endl;
//   std::map<char,int>::iterator it = mymap.begin();
//   do {
//     std::cout << it->first << " => " << it->second << '\n';
//   } while ( mycomp((*it++).first, highest) );

//   std::cout << '\n';

//   return 0;
// }

// #include <iostream>
// #include <string>
// // #include "Map.hpp"
// #include <map>

// int main()
// {
// 	std::map<std::string, int> mymap;
//     const std::pair<std::string, int> pair_one = std::make_pair("alpha", 0);
//     const std::pair<std::string, int> pair_two = std::make_pair("beta", 0);
//     const std::pair<std::string, int> pair_three = std::make_pair("gamma", 0);

//     mymap.insert(pair_one);
//     mymap.insert(pair_two);
//     mymap.insert(pair_three);
//     mymap.at("alpha") = 10;
//     mymap.at("beta") = 20;
//     mymap.at("gamma") = 30;

//     // for (auto& x: mymap) {
//     //   std::cout << x.first << ": " << x.second << '\n';
//     // }

// 	std::map<std::string, int>::iterator it_beg;
//     std::map<std::string, int>::iterator it_end;

//     it_beg = mymap.begin();

//     it_end = mymap.end();

//     for ( ; it_beg != it_end ; ++it_beg)
//         std::cout << it_beg->first << ' ' << it_beg->second << '\n';

//     return 0;
// }