#include "yamlpp/stream.hpp"
#include <cmath>


namespace yamlpp
{

CharStream::UnionValue CharStream::parseToEndOfLine()
{
    ValueType type = None;
    const char *strBegin = &(*iter_);
    int sign = 1;
    char ch;

    int int_ = 0;
    float float_ = 0.0;
    std::string str_;

    ch = rawPeek();
    if (ch > '0' && ch < '9')
    {
        type = Int;
        int_ = parseInt();

        ch = rawPeek();
        if (ch == '.')
        {
            type = Float;
            float f = parseFloatAfterDot();
            float_ = static_cast<float>(int_) + f;

            ch = rawPeek();
            if (ch == 'e' || ch == 'E')
            {
                int exp = parseInt();
                float_ *= std::pow(10, parseInt());
            }
        }
        else if (ch == 'e' || ch == 'E')
        {
                int exp = parseInt();
                float_ = static_cast<float>(int_);
                float_ *= std::pow(10, parseInt());
        }
    }

    // end of file or end of line
    if (!hasNext() || rawPeek() == '\n')
    {
        // int or float
        if (type == Int)
            return UnionValue(Int, std::move(int_));
        else
            return UnionValue(Float, std::move(float_));
    }
    else
    {
        type = Str;
        skipUntilEndOfLine();
        const char *strEnd = &(*iter_);
        str_.assign(strBegin, strEnd);
        return UnionValue(Str, std::move(str_));
        // string
    }
}

}
