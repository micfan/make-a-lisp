//
// Created by mic on 6/22/18.
//

#ifndef MAL_READER_H
#define MAL_READER_H

#include "mal.h"
#include "types.h"
#include <string>
#include <vector>
#include <array>
#include <map>
#include <iostream>
#include <regex>
#include <iterator>
#include <functional>

//using MalDict = map;
using MalAny = void*;
using MalNil = void;
using MalBool = bool;

class Reader {
public:
    Reader(const std::string& input);

    ~Reader() {
        // todo:
    }

    bool eof() const;

    String peek() const;

    String next();

    MalPtr read_form();

    MalPtr read_atom();

    template <class T>
    MalPtr read_list(const String& end_str);

private:
    using StrIter = String::const_iterator;
    String m_token;
    StrIter m_iter;
    StrIter m_end;

    bool regex_matched(const Regex& re);

    void next_token();
};

MalPtr read(const String &input);

#endif //MAL_READER_H

