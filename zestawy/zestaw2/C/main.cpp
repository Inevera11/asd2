#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include "set_simple.h"
#include "set_linked.h"
#include "set_hashed.h"

using namespace std;
using namespace chrono;

const int TEST_SIZES[] = {100, 500, 1000};

int generateNumber()
{
    int number = 0;
    for (int i = 0; i < 5; i++)
    {
        number = number * 10 + (rand() % 10);
    }
    return number;
}

void testPerformance()
{
    ofstream pushFile("push_results.dat");
    ofstream searchFile("search_results.dat");
    ofstream popFile("pop_results.dat");

    pushFile << "Size SimpleDict LinkedSet SetHashed\n";
    searchFile << "Size SimpleDict LinkedSet SetHashed\n";
    popFile << "Size SimpleDict LinkedSet SetHashed\n";

    for (int size : TEST_SIZES)
    {
        vector<int> words;
        for (int i = 0; i < size; i++)
        {
            words.push_back(generateNumber());
        }

        SimpleSet dict;
        LinkedSet<int> linkedSet;
        SetHashed hashedSet(size / 2);

        // Test push
        auto start = high_resolution_clock::now();
        for (const auto &word : words)
            dict.push(word);
        auto end = high_resolution_clock::now();
        double timeDictPush = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (const auto &word : words)
            linkedSet.push(word);
        end = high_resolution_clock::now();
        double timeLinkedSetPush = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (const auto &word : words)
            hashedSet.push(word);
        end = high_resolution_clock::now();
        double timeHashedSetPush = duration<double, milli>(end - start).count();

        pushFile << size << " " << timeDictPush << " " << timeLinkedSetPush << " " << timeHashedSetPush << "\n";

        // Test search
        start = high_resolution_clock::now();
        for (const auto &word : words)
            dict.includes(word);
        end = high_resolution_clock::now();
        double timeDictSearch = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (const auto &word : words)
            linkedSet.includes(word);
        end = high_resolution_clock::now();
        double timeLinkedSetSearch = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (const auto &word : words)
            hashedSet.includes(word);
        end = high_resolution_clock::now();
        double timeHashedSetSearch = duration<double, milli>(end - start).count();

        searchFile << size << " " << timeDictSearch << " " << timeLinkedSetSearch << " " << timeHashedSetSearch << "\n";

        // Test pop
        start = high_resolution_clock::now();
        for (const auto &word : words)
            dict.pop(word);
        end = high_resolution_clock::now();
        double timeDictPop = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (const auto &word : words)
            linkedSet.pop(word);
        end = high_resolution_clock::now();
        double timeLinkedSetPop = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (const auto &word : words)
            hashedSet.pop(word);
        end = high_resolution_clock::now();
        double timeHashedSetPop = duration<double, milli>(end - start).count();

        popFile << size << " " << timeDictPop << " " << timeLinkedSetPop << " " << timeHashedSetPop << "\n";
    }

    pushFile.close();
    searchFile.close();
    popFile.close();
}

int main()
{
    srand(time(nullptr));
    testPerformance();
    cout << "Testy zakończone. Wyniki zapisane w plikach .dat" << endl;
    system("gnuplot plot.gnu");
    return 0;
}