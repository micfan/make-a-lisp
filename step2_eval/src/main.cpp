#include <iostream>
#include <string>
#include "linenoise.h"
#include "reader.h"

using namespace std;

static MalPtr eval(MalPtr ast) {
    return ast->eval();
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

void rep(const string &line ) {
    if (!line.empty()) {
        auto str = print(eval(read(line)));
    }
}

void rep() {

    string a_nil = R"**("nil")**";
    rep(a_nil);

    string a_num = R"**(123)**";
    rep(a_num);

    string a_str = R"**("123")**";
    rep(a_str);

    string a_symbol = R"**(abc)**";
    rep(a_symbol);

    string a_list = R"**((123 456))**";
    rep(a_list);

    string a_list2 = R"**((123 456 789))**";
    rep(a_list);

    string a_stmt = R"**(( + 2 (* 3 4) ))**";

    rep(a_stmt);

    string nil = R"**(nil)**";
    rep(nil);
}


spdog lg = spdlog::stdout_color_mt("console");

int main() {

    lg->set_level(spdlog::level::trace);

    repl();
//    rep();
    return 0;
}