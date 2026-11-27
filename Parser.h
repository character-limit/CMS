#pragma once

#include <optional>
#include <string>

std::string trim(const std::string& text);

std::optional<double> parseFiniteNumber(const std::string& text);

std::optional<long int> parseWholeNumber(const std::string& text);