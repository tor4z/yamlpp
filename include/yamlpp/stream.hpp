#pragma once

#include <string>

namespace yamlpp
{

class CharStream
{
public:
    enum ValueType
    {
        None,
        Int,
        Float,
        Str
    };

    struct UnionValue
    {
        ValueType type;
        union{
            int int_;
            float float_;
            std::string str_;
        };

        UnionValue(ValueType t, int && d)
            : type(t), int_(std::move(d))
        {}
        UnionValue(ValueType t, float && d)
            : type(t), float_(std::move(d))
        {}
        UnionValue(ValueType t, std::string && d)
            : type(t), str_(std::move(d))
        {}

        ~UnionValue()
        {}
    };

    using Iter = std::string_view::iterator;

    CharStream(const char *str);
    CharStream(const std::string &str);
    CharStream(const std::string_view &str);

    char peek() const;
    char next();
    void rollBack();
    char rawPeek() const;
    char rawNext();
    bool hasNext() const;
    void skipWitespace();
    bool isNewLine();
    void assertChar(char ch) const;
    int parseInt();
    float parseFloatAfterDot();
    void skipUntilEndOfLine();
    UnionValue parseToEndOfLine();

    std::string parseKey();
private:
    const std::string_view dataStr_;
    Iter iter_;
};

}
