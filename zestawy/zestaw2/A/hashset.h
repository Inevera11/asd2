#ifndef HASH_SET_H
#define HASH_SET_H

#include <iostream> // std::cout, std::cerr
#include <cassert>  // assert()
#include <string>
#include <chrono>
#include <fstream>

// Mapowanie dla liczb całkowitych n, n+1, ..., m
int mapConsecutive(int n, int m, int value)
{
    if (value < n || value > m)
        throw std::out_of_range("Value out of range");
    return value - n;
}

int inverseConsecutive(int n, int /*m*/, int index)
{
    return n + index;
}

// Mapowanie dla liczb całkowitych n, n+2, ..., m
int mapEvenlySpaced(int n, int m, int value)
{
    if (value < n || value > m || (value - n) % 2 != 0)
        throw std::out_of_range("Value out of range");
    return (value - n) / 2;
}

int inverseEvenlySpaced(int n, int /*m*/, int index)
{
    return n + 2 * index;
}

// Mapowanie dla liter 'a' - 'z'
int mapSingleLetter(char c)
{
    if (c < 'a' || c > 'z')
        throw std::out_of_range("Character out of range");
    return c - 'a';
}

char inverseSingleLetter(int index)
{
    if (index < 0 || index > 25)
        throw std::out_of_range("Index out of range");
    return 'a' + index;
}

// Mapowanie dla dwuliterowych napisów 'aa' - 'zz'
int mapDoubleLetter(const std::string &str)
{
    if (str.size() != 2 || str[0] < 'a' || str[0] > 'z' || str[1] < 'a' || str[1] > 'z')
        throw std::out_of_range("String out of range");
    return (str[0] - 'a') * 26 + (str[1] - 'a');
}

std::string inverseDoubleLetter(int index)
{
    if (index < 0 || index >= 26 * 26)
        throw std::out_of_range("Index out of range");
    char first = 'a' + index / 26;
    char second = 'a' + index % 26;
    return std::string(1, first) + std::string(1, second);
}

#endif // HASH_SET_H
