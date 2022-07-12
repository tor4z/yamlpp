#pragma once

#include <string>
#include <vector>


namespace yamlpp
{

class Member;


class Value
{
public:
    enum Type
    {
        Doc,
        Int,
        Float,
        Str,
        List
    };

    Value(int val) :int_(val), type_(Int)
    {}

    Value(float val) :float_(val), type_(Float)
    {}

    Value(std::string &&val)
        :str_(Str, val), type_(Str)
    {}

    // for array
    Value()
    {}

    // for copy
    Value(const Value &value);

    // for move
    // Value()
    // {}

    ~Value();

    void push_back(Value &&value);
    const Value &operator[](const std::string &key) const;

    void insertMember(const std::string &key, Value &&value);
    Value &findValue();

private:
    template<typename T>
    class ObjectContainer_
    {
    public:
        template<typename ...Args>
        ObjectContainer_(Type type, Args&&... args)
            : type_(type), data_(std::move<Args>(args)...)
        {}
        Type type() const
        {
            return type_;
        }

        T data() const 
        {
            return data_;
        }
    private:
        Type type_;
        T data_;
    };

    using StrObject = ObjectContainer_<std::string>;
    using ListObject = ObjectContainer_<std::vector<Value>>;
    using DocObject = ObjectContainer_<std::vector<Member>>;

    union
    {
        int int_;
        float float_;
        StrObject str_;
        ListObject list_;
        DocObject doc_;
    };
    Type type_;
};


class Member
{
public:
private:
    std::string key_;
    Value value_;
};

}
