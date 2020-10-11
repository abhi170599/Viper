//
// Utility functions
//


#include<string>
#include<vector>
#include<sstream>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

using namespace std;

// function to split a string by a delimiter
vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}

//function to convert hex to decimal
string hex2decimal(string hex_num){
    int dec;
    stringstream ss;
    ss << hex << hex_num;
    ss >> dec;

    return to_string(dec);
}

bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::string exec(const char * cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}