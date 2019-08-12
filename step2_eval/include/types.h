#ifndef MAL_TYPES_H
#define MAL_TYPES_H

#include "mal.h"
#include <iostream>
#include <map>

class MalList;

namespace mal {

    MalPtr atom(MalPtr value);
    MalPtr boolean(bool value);
    MalPtr false_value();
    MalPtr integer(int64_t value);
    MalPtr integer(const String& token);

    MalPtr string(const String& token);

    MalPtr list(MalVec* items);
    MalPtr list(::MalList& items);
    MalPtr list(MalIter begin, MalIter  end);
    MalPtr list(MalPtr& a);
    MalPtr list(MalPtr a, MalPtr b);
    MalPtr list(MalPtr a, MalPtr b, MalPtr c);
    MalPtr nil_value ();
    MalPtr true_value();
};

class MalValue : public RefCounted {
public:
    MalValue() : m_meta(nullptr) {};
    explicit MalValue(MalPtr& meta) : m_meta(meta) {};

    virtual String str() const = 0;

    virtual String form() const {
        return std::string("unknown");
    };

    virtual MalPtr eval() {
        return this;
    };

    MalPtr value() {
        return this;
    };

private:
    MalPtr m_meta;
};


class MalConstant : public MalValue {
public:
    explicit MalConstant(const String& name) : m_name(name) {
    }

    String str() const override {
        return m_name;
    }
private:
    const String m_name;
};


class MalInt : public MalValue {
public:
    explicit MalInt(int64_t value) : m_value(value) {}
    MalInt(const String& token) : m_value(std::stoi(token)) {}
    String str() const override {
        return std::to_string(m_value);
    }

    String form() const override {
        return std::string("MalInt");
    };

    int64_t value() const {
        return m_value;
    };

private:
    const int64_t m_value;
};


class MalStringBase : public MalValue {
public:
    MalStringBase() = default;

    explicit MalStringBase(const String& token) : m_value(token) {
    };

    String str() const override {
        return m_value;
    }

    String form() const override {
        return std::string("MalStringBase");
    };
protected:
    const String m_value;
};


class MalString : public MalStringBase {
public:
    explicit MalString(const String& token) : MalStringBase(token) {
    };
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
    explicit MalList(MalVec * items) : MalSeq(items) { }
    String str() const override {
        return fmt::format("({})", MalSeq::str());
    }

    MalPtr eval() override {
        auto first_token = begin()->ptr()->str();
        if (first_token  == "+") {
            lg->info("MalList start with an op: {}, evaluating...", first_token);

            int64_t val(0);
            auto it = begin();
            it++;
            for(; it != end(); it++) {
                auto tok = it->ptr()->str();
                lg->info("MalInt token: {}", tok);
                if (it->ptr()->form() == "MalInt") {
                    val += ((MalInt *)(it->ptr()))->value();
                } else {
                    lg->info("skipped non-MalInt token: {}", tok);
                }
            }

            return mal::integer(val);
        }

        return this;
    };
};


class MalVector : public MalSeq {

};


class MalHash : public MalValue {
public:
    String str() const override {
        return "this is a hash";
    }

    void push(const MalPtr &k) {
    }

private:
    std::map<MalPtr, MalPtr>* m_values;
};




#endif
