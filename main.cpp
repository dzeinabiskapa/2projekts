#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function declarations
string trim(const string &str);
vector<string> splitString(const string &str, char koma);
string join(const vector<string> &vec);

// Main function
int main() {
    ifstream inputFile("db.csv");
    ofstream errorFile("err.txt"); //output file stream
    ofstream validFile("valid_db.txt");

    if (!inputFile.is_open()) {
        cout << "Failed to open db.csv" << endl;
        return 1;
    }

    if (!errorFile.is_open()) {
        cout << "Failed to open err.txt" << endl;
        return 1;
    }

    if (!validFile.is_open()) {
        cout << "Failed to open valid_db.txt" << endl;
        return 1;
    }

    string line;
    string lineCheck;
    vector<string> lineElem;
    while (getline(inputFile, line)) {
        lineCheck = trim(line); // Trim leading/trailing whitespace
        if (lineCheck.empty()) continue; // Skip empty or whitespace-only lines
        
        lineElem = splitString(line,','); // Remove any extra spaces

        
        if (lineElem.size()==5) {
            validFile << join(lineElem) << endl;
            lineElem.clear();
        } else {
            errorFile << join(lineElem) << endl;
            lineElem.clear();
        }

        
    }

    cout << "Processing completed. Check err.txt for errors and valid_routes.txt for valid data." << endl;

    inputFile.close();
    errorFile.close();
    validFile.close();

    return 0;
}

// Function definitions

string trim(const string &str) {
    // Find the first character that is not a whitespace character
    size_t start = str.find_first_not_of(" \t\n\r\f\v");

    // If no non-whitespace character is found, return an empty string
    if (start == string::npos) {
        return "";
    }

    // Find the last character that is not a whitespace character
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    // Return the substring from 'start' to 'end'
    return str.substr(start, end - start + 1);
}


vector<string> splitString(const string &str, char koma) {
    string elem;
    vector<string> result;

    // Loop through each character in the string
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == koma) {
            // Trim the element before appending to result
            if (!elem.empty()) {
                result.push_back(trim(elem));
                elem.clear();  // Reset the element for the next substring
            }
        } else {
            elem += str[i];  // Add character to the current element
        }
    }

    // Don't forget to trim and add the last element if it's non-empty
    if (!elem.empty()) {
        result.push_back(trim(elem));
    }

    return result;
}

string join(const vector<string> &vec) {
    if (vec.empty()) return "";  // If the vector is empty, return an empty string

    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];  // Add the element to the result string
        if (i < vec.size() - 1) {
            result += ",";  // Add a comma and space after each element except the last one
        }
    }
    return result;
}

