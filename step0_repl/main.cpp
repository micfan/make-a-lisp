#include <iostream>
#include <string>
#include "linenoise.h"

using namespace std;

string read(string s) {
  return s;
}

string eval(string s) {
  return s;
}

string print(string s) {
  cout << s << endl;
  return s;
}

void repl() {
  string line;
  while (!(line = linenoise("user> ")).empty()) {
    print(eval(read(line)));
  }
}

int main() {
  
  repl();

  return 0;
}