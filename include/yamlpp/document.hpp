#pragma once

#include <string>
#include "yamlpp/stream.hpp"
#include "yamlpp/value.hpp"


namespace yamlpp
{

class CharStream;


class Document: public Value
{
public:
    void parse(const char *str);
    void parse(const std::string &str);
    void parse(const std::string_view &str);
    ~Document();
private:
    void parse_doc(CharStream &cs, Value *currDoc);
    Value &&parse_array(CharStream &cs);
    Value &&parse_trivial(CharStream &cs);
};

}
