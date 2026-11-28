#include "Format.h"

#include <iomanip>
#include <sstream>

//convert to text, 1dp by default, saves repetition across all outputs

std::string formatNumber(double value, const int decimalPlaces)
{
    std::ostringstream text;
    text << std::fixed << std::setprecision(decimalPlaces) << value;
    return text.str();
}

std::string formatReading(const std::optional<double>& reading, const std::string& unit)
{
    if (reading.has_value())
    {
        return formatNumber(reading.value()) + " " + unit;
    }
    return "NO READING";
}
