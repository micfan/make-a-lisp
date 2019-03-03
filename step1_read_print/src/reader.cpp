//
// Created by mic on 6/22/18.
//

#include "types.h"
#include "reader.h"

#include <string>
#include <vector>
#include <array>
#include <map>
#include <iostream>
#include <regex>
#include <iterator>
#include <functional>
#include <typeinfo>


using namespace std;

Reader::Reader(const string& input) : m_iter(input.begin()), m_end(input.end()) {
    next();
}

bool Reader::eof() const {
    return m_iter == m_end;
}

String Reader::peek() const {
    if (eof()) {
        lg->error("Reader EOF in peek()");
    }
    return m_token;
};

string Reader::next() {
    if (eof()) {
        lg->warn("Reader EOF in next()");
    }
    string current = peek();
    next_token();
    return current;
};

bool Reader::regex_matched(const regex& re) {
    if (eof()) {
        return false;
    }

    smatch sm;
    auto flags = regex_constants::match_continuous;
    if (!std::regex_search(m_iter, m_end, sm, re, flags)) {
        return false;
    }

    // todo: assert

    m_token = sm.str(0);
    return true;
}

static const auto whitespace_regex = Regex("[\\s,]+|;.*");
static const auto token_regexes = {
    Regex("~@"),
    Regex(R"([\[\]{}()'`~^@])"),
    Regex(R"("(?:\\.|[^\\"])*")"),
    Regex(R"([^\s\[\]{}('"`,;)]+)"),
};

void Reader::next_token() {
    m_iter += m_token.size();

    while (regex_matched(whitespace_regex)) {
        lg->debug("skipped 1 space");
        m_iter += m_token.size();
    }

    if (eof()) {
        return;
    }

    for (auto &it :token_regexes) {
        if (regex_matched(it)) {
            return;
        }
    }

/*
    string mismatch(m_iter, m_end);
    if (mismatch[0] == '"') {
        cerr << "Expected \", got EOF" << endl;
    } else {
        cerr << "Unexpected: " << mismatch.c_str() << endl;
    }
    */
}

MalPtr read(const String &input) {
    Reader reader(input);
    if (reader.eof()) {
        throw MalEmptyInputException();
    }
    auto form = reader.read_form();
    return form;
}

MalPtr Reader::read_form() {
    if (eof()) {
        lg->error("Expect form, but got EOF");
        return MalPtr();
    }

    String token = peek();
    Regex r(R"**([\)\]\}])**");
    if (std::regex_match(token, r)) {
        lg->debug("Got a closed token: {}", token);
    } else {
        lg->debug("Got a not close token: {}", token);
    }
    if (token == "(") {
        next();
        return read_list<MalVec>(")");
    }
    if (token == "[") {
        return read_list<MalVec>("]");
    }
    if (token == "{") {
        return read_list<MalVec>("}");
    }
    MalPtr atom = read_atom();
    return atom;
}

template <class T>
MalPtr Reader::read_list(const String& end_str) {
    std::unique_ptr<MalVec> v(new MalVec);
    while (true) {
//        if (eof()) {
//            // todo:
//            cerr << "Expect form, but got EOF" << endl;
//            throw MalSyntaxErrorException();
//        }
        auto current = peek();
        lg->info("current token: {}", current);
        if (current == end_str) {
            lg->info("break, current token: {}", current);
            next();
            break;
        }

        MalPtr form = read_form();
        if (form != nullptr) {
            lg->info("push_back: {}", form->str());
            v->push_back(form);
        }
    }

    return mal::list(v.release());
}

MalPtr Reader::read_atom() {
    const String token = next();
    char first = token[0];
    switch (first) {
        case '"':
            return mal::string(token);
//            return MalPtr(new MalString(token));
            return MalPtr(); //MalKeyword(token);
        case ':':
            return MalPtr(); //MalKeyword(token);
        case '^':
            return MalPtr(); //MalKeyword(token);
        default:
            ;
    }

    struct Constant {
        const char* token;
        MalPtr value;
    };

    Constant const_table[] = {
        { "false",  mal::false_value()  },
        { "nil",    mal::nil_value()    },
        { "true",   mal::true_value()   },
    };
    for (auto &constant : const_table) {
        if (token == constant.token) {
            return constant.value;
        }
    }

    Regex int_regex("^[-+]?\\d+$");
    if (regex_match(token, int_regex)) {
        auto value = stoi(token);
        MalInt mi(value);
        auto i = mal::integer(value);
        return i;
    }

    return nullptr;
}

