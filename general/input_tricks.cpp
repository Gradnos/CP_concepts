#include <iostream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;
string var;
int main(){
    string str; int var; char ch;

    // 1. EXTRACTION OPERATOR: Reads single tokens. Skips spaces. Leaves '\n'.
    cin >> var; 
    
    // 2. GETLINE: Reads full lines with spaces. Extracts and discards '\n'.
    getline(cin, str); 
    
    // 3. GET CHAR: Reads next raw byte (including spaces and '\n').
    cin.get(ch); 
    
    // 4. THE FIX: Clears '\n' left by 'cin >>' so 'getline' works after it.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // 5. ISTRINGSTREAM: Input-only. Great for parsing existing string data.
    istringstream iss("Data 42");
    iss >> str >> var;
    
    // 6. STRINGSTREAM: Bidirectional. Read and write to the same buffer.
    stringstream ss;
    ss << "Format " << 100; // Write
    ss >> str >> var;     // Read
    
    // 7. SAFE LOOPS: Put read operation inside condition (handles EOF safely).
    string token, line;
    while (cin >> token) {}           // Word by word
    while (getline(cin, line)) {} // Line by line
    while (cin.get(ch)) {}             // Char by char
    
}