#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<string, unordered_set<string>> readData(const string& filename) {
    unordered_map<string, unordered_set<string>> data;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            int comma1 = line.find(',');
            int comma2 = line.find(',', comma1 + 1);

            if (comma1 != -1 && comma2 != -1) {
                string user = line.substr(0, comma1);
                string product = line.substr(comma1 + 1, comma2 - comma1 - 1);
                if (!user.empty() && !product.empty()) {
                    data[user].insert(product);
                }
            }
        }
        file.close();
    }
    else {
        cout << "Не вдалося відкрити " << filename << endl;
    }
    return data;
}

//Варіант 1: Користувачі, які були в обидва дні і в другий день відвідали нові сторінки другого дня
void printUsersWithNewPages(const unordered_map<string, unordered_set<string>>& day1Data, const unordered_map<string, unordered_set<string>>& day2Data) {
    cout << "Користувачі, які були в обидва дні і відвідали нові сторінки на другий день:\n";
    for (auto it = day2Data.begin(); it != day2Data.end(); ++it) {
        const string& user = it->first;
        const unordered_set<string>& productsDay2 = it->second;

        auto day1It = day1Data.find(user);
        if (day1It != day1Data.end()) {
            const unordered_set<string>& productsDay1 = day1It->second;

            for (const string& product : productsDay2) {
                if (productsDay1.count(product) == 0) {
                    cout << user << endl;
                    break;
                }
            }
        }
    }
}

//Варіант 2:
// 2.1) Користувачі, які були в обидва дні
void printUsersInBothDays(const unordered_map<string, unordered_set<string>>& day1Data, const unordered_map<string, unordered_set<string>>& day2Data) {
    cout << "Користувачі, які були в обидва дні:\n";
    for (auto it = day2Data.begin(); it != day2Data.end(); ++it) {
        const string& user = it->first;
        if (day1Data.count(user) != 0) {
            cout << user << endl;
        }
    }
}

//Варіант 2:
// 2.2) Користувачі, які другого дня відвідали нові сторінки (незалежно від першого дня - тобто навіть якщо цього користувача не було в перший день)
void printUsersWithAnyNewPages(const unordered_map<string, unordered_set<string>>& day1Data, const unordered_map<string, unordered_set<string>>& day2Data) {
    cout << "Користувачі, які на другий день відвідали нові сторінки (навіть якщо їх не було в перший день):\n";
    for (auto it = day2Data.begin(); it != day2Data.end(); ++it) {
        const string& user = it->first;
        const unordered_set<string>& productsDay2 = it->second;
        auto day1It = day1Data.find(user);
        if (day1It == day1Data.end()) {
            // Користувач не був у перший день, отже, всі сторінки нові - виводимо
            cout << user << endl;
        }
        else {
            const unordered_set<string>& productsDay1 = day1It->second;
            for (const string& product : productsDay2) {
                if (productsDay1.count(product) == 0) {
                    cout << user << endl;
                    break;
                }
            }
        }
    }
}

int main()
{
    system("chcp 1251 > nul");

    unordered_map<string, unordered_set<string>> day1Data = readData("day1.csv");
    unordered_map<string, unordered_set<string>> day2Data = readData("day2.csv");

    printUsersWithNewPages(day1Data, day2Data);
    cout << "\n-----------------------\n";
    printUsersInBothDays(day1Data, day2Data);
    cout << "\n-----------------------\n";
    printUsersWithAnyNewPages(day1Data, day2Data);

    return 0;
}