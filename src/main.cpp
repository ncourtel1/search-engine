#include <iostream>

const char* Recommand(char letter);

int main() {
   std::cout << Recommand('a');
}

const char* Recommand(char letter){
   if (letter == 'a' || letter == 'A')
      return "apple";
   return "pizza";
}