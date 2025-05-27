#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Funkcja sprawdzająca, czy dwa słowa różnią się dokładnie jedną literą
bool oneLetterDifference(const string &a, const string &b)
{
    int diffCount = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (a[i] != b[i])
        {
            ++diffCount;
            if (diffCount > 1)
                return false;
        }
    }
    return diffCount == 1;
}

// Odczytuje słowa z pliku do zbioru
unordered_set<string> loadWords(const string &filename)
{
    unordered_set<string> wordSet;
    ifstream file(filename);
    string word;
    while (file >> word)
    {
        if (word.size() == 4)
        {
            wordSet.insert(word);
        }
    }
    return wordSet;
}

// Szuka najkrótszej ścieżki transformacji za pomocą BFS
vector<string> findShortestPath(const string &start, const string &end, const unordered_set<string> &dictionary)
{
    unordered_set<string> visited;
    unordered_map<string, string> parent;
    queue<string> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty())
    {
        string current = q.front();
        q.pop();

        if (current == end)
        {
            // Rekonstrukcja ścieżki
            vector<string> path;
            while (current != start)
            {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; ++i)
        {
            string next = current;
            for (char c = 'a'; c <= 'z'; ++c)
            {
                if (next[i] == c)
                    continue;
                next[i] = c;
                if (dictionary.count(next) && !visited.count(next))
                {
                    visited.insert(next);
                    parent[next] = current;
                    q.push(next);
                }
            }
        }
    }

    return {}; // Brak ścieżki
}

void findPathAndPrint(const string &start, const string &end, const unordered_set<string> &dictionary)
{
    if (!dictionary.count(start) || !dictionary.count(end))
    {
        cout << "Słowo początkowe lub końcowe nie istnieje w słowniku.\n";
        return;
    }

    vector<string> path = findShortestPath(start, end, dictionary);

    if (!path.empty())
    {
        cout << "Najkrótsza ścieżka " << start << " -> " << end << " (" << path.size() - 1 << " kroków):\n";
        for (const string &word : path)
        {
            cout << word << "\n";
        }
    }
    else
    {
        cout << "Brak możliwej ścieżki między słowami.\n";
    }
}

int main()
{

    unordered_set<string> dictionary = loadWords("slowa.txt");
    findPathAndPrint("ster", "atom", dictionary);
    findPathAndPrint("ryba", "krem", dictionary);

    return 0;
}
