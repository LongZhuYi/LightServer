#pragma once
#include <iostream>

#define LogDebug(format, ...) { std::cout << format << std::endl; }
#define LogErr(format, ...) { std::cout << format << std::endl; }
#define LogWarr(format, ...) { std::cout << format << std::endl; }