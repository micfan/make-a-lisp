#include <iostream>
#include <string>
#include "linenoise.h"
#include "reader.h"

using namespace std;


static MalPtr eval(MalPtr ast) {
  auto ret = ast;
  return ret;
}

String print(MalPtr ast) {
  auto s = ast->str();
  cout << "Out ==> " << s << endl;
  return ast->str();
}

void repl() {
  string line = "[]";
  while (!(line = linenoise("In: ")).empty()) {
    auto str = print(eval(read(line)));
  }
}

void rep() {
//    string line = R"**("( + 2 (* 3 4) )")**";

    string a_nil = R"**("nil")**";
    print(eval(read(a_nil)));

    string a_str = R"**("1")**";
    print(eval(read(a_str)));

    string a_num = R"**(1)**";
    print(eval(read(a_num)));

    string list = R"**((123 456 789))**";
    print(eval(read(list)));

    string nil = R"**(nil)**";
    print(eval(read(nil)));
}


spdog lg = spdlog::stdout_color_mt("console");

int main() {
//    lg = spdlog::stdout_color_mt("console");

    lg->set_level(spdlog::level::trace);
  
//  repl();
    rep();
  return 0;
}