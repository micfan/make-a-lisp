//
// Created by mic on 6/24/18.
//

#ifndef MAL_TYPES_H
#define MAL_TYPES_H

#include "mal.h"
#include <iostream>
#include <map>


class MalValue : public RefCounted {
public:
    MalValue() : m_meta(nullptr) {};
    MalValue(MalPtr& meta) : m_meta(meta) {};
//    virtual ~MalValue() {
//    }

////    template <typename T>
//    virtual MalPtr ptr() {
//        return MalPtr(this);
//    }
    virtual String str() const = 0;
//        {
//        auto s = "virtual str() called";
//        return s;
//    };

//    virtual bool operator ! () const { return false; };
//    virtual bool operator == (const MalValue& mv) const { return false; };
//    virtual eval(MalEnvPtr env);
private:
    MalPtr m_meta;
};


class MalConstant : public MalValue {
public:
    MalConstant(const String& name) : m_name(name) {
//        lg->debug("MalConstant().m_name: {}", m_name);
    }
    virtual String str() const override {
        return m_name;
    }
private:
    const String m_name;
};


class MalInt : public MalValue {
public:
//    MalInt(int64_t value) : m_value(value) {}
    MalInt(int64_t value) : m_value(value) {}
    MalInt(const String& token) : m_value(std::stoi(token)) {}
    virtual String str() const override {
        auto s = std::to_string(m_value);
        return s;
    }

private:
    const int64_t m_value;
};


class MalStringBase : public MalValue {
public:
    MalStringBase() = default;
    explicit MalStringBase(const String& token) : m_value(token) {};
    String str() const override { return m_value; }
protected:
    const String m_value;
};


class MalString : public MalStringBase {
public:
    MalString(const String& token) : MalStringBase(token) {};
    String str() const override { return m_value; }
private:
};


class MalKeyword : public MalStringBase {
};


class MalSeq : public  MalValue {
private:
    MalVec* m_items;

public:
    MalSeq() : m_items() {};
    explicit MalSeq(MalVec* items) : m_items(items) {
        int a = 1;
    };
    MalSeq(MalIter begin, MalIter end) : m_items(new MalVec(begin, end)) {};
    MalSeq(MalSeq& that, MalPtr meta)
        : MalValue(meta)
        , m_items(new MalVec(*(that.m_items))) {}

    String str() const override {
        String ss;
        auto last = m_items->cend() -1;
        for ( auto it = m_items->cbegin(); it != m_items->cend(); it++) {
            ss += (*it)->str();
            if (it != last) {
                ss += " ";
            }
        }
        return ss;
    }

    MalIter begin() const { return m_items->begin(); }
    MalIter end() const { return m_items->end(); }
    MalVec* items() const { return m_items;}
};


class MalList : public MalSeq {
public:
    MalList(MalVec * items) : MalSeq(items) { }
    String str() const override {
        return '(' + MalSeq::str() + ')';
    }
};


class MalVector : public MalSeq {

};


class MalHash : public MalValue {
public:
    String str() const override { return "this is a hash"; } //std::to_string(m_value); }
    // fixme
//    void push(const MalPtr k) { return m_values->insert(k, MalStringBase("").ptr()); }
    void push(const MalPtr k) { return; }

private:
    std::map<MalPtr, MalPtr>* m_values;
};

namespace mal {
  MalPtr integer(int64_t value);
};

namespace mal {
    MalPtr atom(MalPtr value);
    MalPtr boolean(bool value);
//    MalPtr builtin(const String& name, malBuiltIn::ApplyFunc handler);
    MalPtr false_value();
//    MalPtr hash(malValueIter argsBegin, malValueIter argsEnd,
//                     bool isEvaluated);
//    MalPtr hash(const malHash::Map& map);
    MalPtr integer(int64_t value);
    MalPtr integer(const String& token);
//    MalPtr keyword(const String& token);
//    MalPtr lambda(const StringVec&, MalPtr, malEnvPtr);
//    template <class T>
//    MalPtr list(T items);

    MalPtr string(const String& token);

    MalPtr list(MalVec* items);
    MalPtr list(MalList& items);
    MalPtr list(MalIter begin, MalIter  end);
    MalPtr list(MalPtr& a);
    MalPtr list(MalPtr a, MalPtr b);
    MalPtr list(MalPtr a, MalPtr b, MalPtr c);
//    MalPtr macro(const malLambda& lambda);
    MalPtr nil_value ();
//    MalPtr string(const String& token);
//    MalPtr symbol(const String& token);
    MalPtr true_value();
//    MalPtr vector(malValueVec* items);
//    MalPtr vector(malValueIter begin, malValueIter end);
};

#endif //MAL_TYPES_H
