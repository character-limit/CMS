#include <iostream>

#include <optional>

#include "Format.h"

int main()
{
    std::cout << formatNumber(25.0) << "\n";
    std::cout << formatNumber(2.5, 2) << "\n";
    std::cout << formatReading(std::nullopt, "mph") << "\n";
    std::cout << formatReading(42.0, "mph") << "\n";
}
