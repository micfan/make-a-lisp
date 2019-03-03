//
// Created by mic on 6/24/18.
//

#pragma once

#include "ref_count.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <string>
#include <regex>
#include <vector>

extern std::shared_ptr<spdlog::logger> lg;

using String = std::string;
using Regex = std::regex;

class MalValue;
using MalPtr = RefCountedPtr<MalValue>;
using MalVec = std::vector<MalPtr>;
using MalIter = MalVec::iterator;

class MalEmptyInputException : public std::exception {};
class MalSyntaxErrorException : public std::exception {};

//#endif //QUUX_MAL_H
