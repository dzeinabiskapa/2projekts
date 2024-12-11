// Džeina Bīskapa 191RBC018 8.grupa
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string trim(const string &str);
vector<string> splitString(const string &str, char koma);
string join(const vector<string> &vec, char divider);
bool check5Valid (const vector<string> &vec);
void aCommand ();
void bCommand ();
void cCommand ();
void dCommand ();

int main() {
    ifstream inputFile("db.csv");
    ofstream errorFile("err.txt");
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
        lineCheck = trim(line); // drošības pēc, ja kādā līnijā ir vienkārši " "
        if (lineCheck.empty()) continue; // skip tukšās līnijas
        
        lineElem = splitString(line,','); // attīram, sadalam elementus

        static bool firstLineErr = true;
        if (lineElem.size()==5) {
            if (check5Valid(lineElem) == true) {
                static bool firstLineVal = true; // lai pēc pēdājās linijas nebūtu \n
                if (!firstLineVal) validFile << endl;
                validFile << join(lineElem,',');
                firstLineVal = false;
            } else {
                if (!firstLineErr) errorFile << endl;
                errorFile << join(lineElem,',');
                firstLineErr = false;
            }  
        } else {
            if (!firstLineErr) errorFile << endl;
            errorFile << join(lineElem,',');
            firstLineErr = false;
        }
    }
    // cout << "Dati sakārtoti" << endl;

    inputFile.close();
    errorFile.close();
    validFile.close();

    char command;
    do {
        cin >> command;

        switch (command) {
            case 'a':
                aCommand();
                break;
            case 'b':
                bCommand();
                break;
            case 'c':
                cCommand();
                break;
            case 'd':
                dCommand();
                break;
            case 'e':
                break;
            default:
                cout << "wrong command" << endl;
        }
    } while (command != 'e');

    return 0;
}

string trim(const string &str) {
    // atrodam pozīciju pirmam derīgam char
    size_t start = str.find_first_not_of(" \t\n\r\f\v");

    // nav atrasts gadījums
    if (start == string::npos) {
        return "";
    }

    // atrodam pozīciju pēdējam derīgam char
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    return str.substr(start, end - start + 1);
}


vector<string> splitString(const string &str, char koma) {
    string elem;
    vector<string> result;

    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == koma) {
            if (!elem.empty()) {
                result.push_back(trim(elem));
                elem.clear();
            }
        } else {
            elem += str[i];
        }
    }

    if (!elem.empty()) {
        result.push_back(trim(elem));
    }

    return result;
}

string join(const vector<string> &vec, char divider) {
    if (vec.empty()) return "";

    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i < vec.size() - 1) {
            result += divider;
        }
    }
    return result;
}

bool check5Valid (const vector<string> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        string element = vec[i];
        if (i < 3) {
            size_t pos = element.find_first_of("0123456789:.");
            if (pos != string::npos) {
                return false;
            }
        } else if (i == 3) {
            size_t pos = element.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.");
            if (pos != string::npos) {
                return false;
            }
        } else if (i == 4) {
            size_t pos = element.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:");
            if (pos != string::npos) {
                return false;
            }
        }
    }
    return true;
}

void aCommand () {
    ifstream validFile("valid_db.txt");
    string line;
    string start;
    string end;
    vector<string> lineElem;

    cin >> start;
    cin >> end;
    cout << "result:" << endl;
    while (getline(validFile, line)) {
        lineElem = splitString(line,',');
        if (lineElem[0]==start && lineElem[1]==end){ 
            cout << join(lineElem,' ') << endl;
        } 
    }

    validFile.close();
}

void bCommand () {
    ifstream validFile("valid_db.txt");
    string line;
    string day;
    vector<string> lineElem;

    cin >> day;
    cout << "result:" << endl;
    while (getline(validFile, line)) {
        lineElem = splitString(line,',');
        if (lineElem[2]==day){ 
            cout << join(lineElem,' ') << endl;
        }
    }

    validFile.close();
}

void cCommand () {
    ifstream validFile("valid_db.txt");
    string line;
    double price;
    double linePrice;
    vector<string> lineElem;

    cin >> price;
    cout << "result:" << endl;
    while (getline(validFile, line)) {
        lineElem = splitString(line,',');
        linePrice = stod(lineElem[4]); // pieņem faila ir pareizi price values (nav prasīts pārbaudīt)
    
        if (linePrice <= price){ 
            cout << join(lineElem,' ') << endl;
        } 
    }
    validFile.close();
}

void dCommand () {
    ifstream errorFile("err.txt");
    string line;
   
    cout << "result:" << endl;
    while (getline(errorFile, line)) {
        cout << line << endl;
    }
    errorFile.close();
}