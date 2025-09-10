#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct TestCase {
    string input;
    string expected;
};

string runProgram(const string& input) {
    ofstream inputFile("input.txt");
    inputFile << input << endl;
    inputFile.close();

    system("Part3.exe < input.txt > output.txt");

    ifstream outputFile("output.txt");
    stringstream buffer;
    buffer << outputFile.rdbuf();
    string output = buffer.str();

    if (!output.empty() && output.back() == '\n') {
        output.pop_back();
    }

    outputFile.close();
    return output;
}

int main() {
    int compileResult = system("g++ Part3.cpp -o Part3");
    if (compileResult != 0) {
        cout << "Compilation failed!" << endl;
        return 1;
    }

    vector<TestCase> testCases = {
        {"0 0 0", "Infinite solutions."},
        {"0 0 1", "No solution."},
        {"0 1 1", "No solution."},
        {"0 1 -4", "The equation has 2 real solution(s): 2 -2 "},
        {"1 2 2", "No solution."},
        {"1 -2 1", "The equation has 2 real solution(s): 1 -1 "},
        {"1 -5 6", "The equation has 4 real solution(s): 2 -2 1.41421 -1.41421 "},
        {"1 0 0", "The equation has 2 real solution(s): 0 0 "},
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& test = testCases[i];
        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "Input: " << test.input << endl;
        cout << "Expected Output: " << test.expected << endl;

        string actualOutput = runProgram(test.input);
        cout << "Actual Output: " << actualOutput << endl;

        if (actualOutput == test.expected) {
            cout << "Result: CORRECT" << endl;
        } else {
            cout << "Result: INCORRECT" << endl;
        }
        cout << endl;
    }

    remove("input.txt");
    remove("output.txt");
    remove("Part3.exe");

    return 0;
}