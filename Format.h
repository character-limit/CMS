#pragma once

#include <optional>
#include <string>

std::string formatNumber(double value, int decimalPlaces = 1);
std::string formatReading(const std::optional<double>& reading, const std::string& unit);