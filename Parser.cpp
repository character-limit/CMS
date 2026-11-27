#include "Parser.h"

#include <cctype>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace
{
    void skipSign(const std::string& text, std::size_t& position)
    {
        if (position < text.size() && (text[position] == '+' || text[position] == '-'))
        {
            ++position;
        }
    }

    std::size_t skipDigits(const std::string& text, std::size_t& position)
    {
        std::size_t i = 0;
        while (position < text.size() && isdigit(text[position]))
        {
            ++position;
            ++i;
        }
        return i;
    }
}

std::string trim(const std::string& text)
{
    std::size_t start = 0;
    while (start < text.size() && isspace(text[start]))
    {
        ++start;
    }
    std::size_t end = text.size();
    while (end > start && isspace(text[end -1]))
    {
        --end;
    }
    return text.substr(start, end - start);

}

std::optional<double> parseFiniteNumber(const std::string& text)
{
    const std::string value = trim(text);

    std::size_t position = 0;
    skipSign(value, position);

    std::size_t digitCount = skipDigits(value, position);
    if (position < value.size() && value[position] == '.')
    {
        ++position;
        digitCount += skipDigits(value, position);
    }
    if (digitCount == 0 || position != value.size())
    {
        return std::nullopt;
    }

    try
    {
        const double number = std::stod(value);
        if (!std::isfinite(number))
        {
            return std::nullopt;
        }
        return number;
    }
    catch (const std::out_of_range&)
    {
        return std::nullopt;
    }
}

std::optional<long int> parseWholeNumber(const std::string& text) {
    const std::string value = trim(text);

    std::size_t position = 0;
    skipSign(value, position);
    const std::size_t digitCount = skipDigits(value, position);
    if (digitCount == 0 || position != value.size())
    {
        return std::nullopt;
    }

    try
    {
        return std::stoi(value);
    }
    catch (const std::out_of_range&)
    {
        return std::nullopt;
    }
}
