#include <iostream>
#include <string>
#include <stack>
int main()
{
   std::stack<char> stack;
   std::string postfix = "";
   //only works for the specific symbols (^, *, /, +, -)
   //only works for the english alphabets
   //To implement, parenthesis checking
   //To implement, chain popping IE (U - V * W + X) when + enters the stack and pops * and -

   std::string expression = "U - V * X";
   char validSymbols[] = {'^','*', '/', '+', '-', '(', ')'};

   bool isHigherPriority(std::stack<char> stack, char toAdd);
   bool isInside(char symbol, char arr[], int size);

   for(char symbol : expression) {
      symbol = std::tolower(symbol);
      if(symbol == ' ' || (!isInside(symbol, validSymbols, sizeof(validSymbols)/sizeof(char)) && !(symbol >= 'a' && symbol <= 'z'))) {
         std::cout << '\'' <<  symbol << '\'' << " is not a valid symbol" << std::endl;
         continue;
      }

      if(symbol >= 'a' && symbol <= 'z') {
         postfix += symbol;
      }else{
         if(isHigherPriority(stack, symbol)) {
            stack.push(symbol);
         }else {
            postfix += symbol;
            stack.pop();
            stack.push(symbol);
         }
      }
   }

   while(!stack.empty()) {
      postfix += stack.top();
      stack.pop();
   }
   std::cout << postfix << std::endl;
}

bool isInside(char symbol, char arr[], int arrSize) {
   for(int i = 0; i < arrSize; i++) {
      if(symbol == arr[i]) {
         return true;
      }
   }
   return false;
}

bool isHigherPriority(std::stack<char> stack, char toAdd) {
   if(stack.size() <= 0) {
      return true;
   }

   char high[] = {'^'};
   char mid[] = {'*', '/'};
   char low[] = {'+', '-'};

   char compared = stack.top();

   if(isInside(compared, low, 2)) {
      if(isInside(toAdd, mid, 2) || isInside(toAdd, high, 1)) {
         return true;
      }
      else {
         return false;
      }
   }
   else if(isInside(compared, mid, 2)) {
      if(isInside(toAdd, high, 1)) {
         return true;
      }
      else {
         return false;
      }
   }
   else if(isInside(compared, high, 1)) {
      return false;
   }
   std::cout << "I shoudlnt have had reached here, something failed";
   return false;
}

