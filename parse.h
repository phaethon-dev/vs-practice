#pragma once
#include <optional>
#include <string>
#include "money.h"

std::string trim(const std::string &text);
std::optional<long long> parseInteger(const std::string &text);
std::optional<Money> parseMoney(const std::string &text);