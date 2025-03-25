#include "hashset.h"

void measure_time()
{
    std::ofstream file("data.txt");
    if (!file)
    {
        std::cerr << "Error opening file\n";
    }

    for (char c1 = 'a'; c1 <= 'z'; ++c1)
    {
        for (char c2 = 'a'; c2 <= 'z'; ++c2)
        {
            std::string str = {c1, c2};
            double total_time = 0.0;

            for (int i = 0; i < 100; ++i) // 100 prób
            {
                auto start = std::chrono::high_resolution_clock::now();
                volatile int result = mapDoubleLetter(str); // Zapobiega optymalizacji
                auto end = std::chrono::high_resolution_clock::now();

                total_time += std::chrono::duration<double, std::micro>(end - start).count();
            }

            double avg_time = total_time / 100.0;
            file << (c1 - 'a') * 26 + (c2 - 'a') << " " << avg_time << "\n";
        }
    }

    file.close();
}

int main()
{
    // Testy dla różnych przypadków
    std::cout << "Mapowanie liczb 5-10: " << mapConsecutive(5, 10, 7) << " -> " << inverseConsecutive(5, 10, 2) << std::endl;
    std::cout << "Mapowanie liczb 4,6,8,...,12: " << mapEvenlySpaced(4, 12, 8) << " -> " << inverseEvenlySpaced(4, 12, 2) << std::endl;
    std::cout << "Mapowanie liter: " << mapSingleLetter('c') << " -> " << inverseSingleLetter(2) << std::endl;
    std::cout << "Mapowanie dwuliterowych napisów: " << mapDoubleLetter("az") << " -> " << inverseDoubleLetter(25) << std::endl;

    measure_time();
    system("gnuplot plot.gnu");
    return 0;
}