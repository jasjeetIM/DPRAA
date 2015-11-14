// proj/main2.cpp

#include <iostream>
// #include <sstream>
// #include <string>

#include "DoublyCircularLL.hpp"

// main
int main(void) {
   DoublyCircularLL dcll;
   int *pa, *pb, *pc, a, b, c, *p;
   a = 1;
   b = 2;
   c = 3;
   pa = &a;
   pb = &b;
   pc = &c;

   std::cout << "empty: " << dcll.empty() << std::endl;
   dcll.insert(pa);
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.insert(pb);
   dcll.insert(pc);
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   std::cout << "empty: " << dcll.empty() << std::endl;

   dcll.remove();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;
   dcll.stepNext();
   p = (int*) dcll.getCurrent();
   std::cout << "size: " << dcll.size() << "; " << "curr: " << *p << std::endl;

   dcll.remove();
   dcll.remove();
   std::cout << "empty: " << dcll.empty() << std::endl;

   return 0;
}
