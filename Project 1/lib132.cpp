#include <fstream>
#include <string>
using namespace std;

/*
toLowerCase takes in a string and changes all characters to lower case.
Parameters:
    s       string      A string to be converted to all lower case.
Returns:
    lower   string      The lower case string.
*/
string toLowerCase(string s) {
    if (s.length() == 0) {
        return string("");
    } else {
        char lower = tolower(s[0]);
        string result = toLowerCase(s.substr(1));
        return lower + result;
    }
}

/*
fileExists checks if a file exists and returns true if it does or false otherwise.
Parameters:
    fileName    string      The filename to be checked if it exists.
Returns:
    fileExists  bool        True if file exists, false if not.
*/
bool fileExists(string fileName) {
    ifstream file(fileName);
    return file.good();
}