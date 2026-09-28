#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string names[10]   = {};
    string authors[10] = {};
    int years[10]      = {};

    int *yearPtr = &years[0];

    fstream file("bestsellers with categories.csv");

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return 1;
    }

    string header;
    getline(file, header);

    int count = 0;
    string line;
    while (getline(file, line) && count < 10) {
        int firstComma = line.find_last_of(',', line.rfind(',') - 1);
        int lastComma = line.rfind(',');

        names[count]   = line.substr(0, firstComma);
        authors[count] = line.substr(firstComma + 1, lastComma - firstComma - 1);
        years[count]   = stoi(line.substr(lastComma + 1));

        count++;
    }

    file.close();

    for (int i = 0; i < count; i++) {
        cout << names[i] << " | " << authors[i] << " | " << years[i] << endl;
    }

    cout << "\nFirst year through pointer: " << *yearPtr << endl;

    return 0;
}