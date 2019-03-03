//
// Created by mic on 7/23/18.
//

#include "types.h"

namespace mal {
    MalPtr integer(int64_t value) {
        return MalPtr(new MalInt(value));
    };

    MalPtr nil_value() {
//        static MalPtr c(new MalConstant("nil"));
        return MalPtr(new MalConstant("nil"));
    }

    MalPtr true_value() {
        static MalPtr c(new MalConstant("true"));
        return MalPtr(c);
    }

    MalPtr false_value() {
        static MalPtr c(new MalConstant("false"));
        return MalPtr(c);
    }

    MalPtr boolean(bool value) {
        return value ? true_value() : false_value();
    }

    MalPtr list(bool value) {
        return value ? true_value() : false_value();
    }

    template <class T>
    MalPtr list(T value) {
        return MalPtr(new T(value));
    }

//    MalPtr list(MalList& value) {
//        return MalPtr(new MalList(value.begin(), value.end()));
//    }

    MalPtr list(MalVec* v) {
        return MalPtr(new MalList(v));
    }

    MalPtr string(const String& token) {
        return MalPtr(new MalString(token));
    };
};