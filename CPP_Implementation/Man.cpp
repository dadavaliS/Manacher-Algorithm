#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string preprocessString(const string &s) {
    string processed = "^";
    for (char c : s) {
        processed += "#";
        processed += c;
    }
    processed += "#$";
    return processed;
}

string manacher(const string &s) {
    string processed = preprocessString(s);
    int n = processed.length();
    vector<int> P(n, 0);
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;

        if (i < right)
            P[i] = min(right - i, P[mirror]);

        while (processed[i + (1 + P[i])] == processed[i - (1 + P[i])])
            P[i]++;

        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    return s.substr((centerIndex - 1 - maxLen) / 2, maxLen);
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening the input file." << endl;
        return 1;
    }

    string inputString;
    while (getline(inputFile, inputString)) {
        string result = manacher(inputString);
        cout << "Longest palindromic substring for \"" << inputString << "\": " << result << endl;
    }

    inputFile.close();
    return 0;
}
