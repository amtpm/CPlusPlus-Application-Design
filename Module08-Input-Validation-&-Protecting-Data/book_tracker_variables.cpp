#include <iostream>
#include <string>
using namespace std;

int main() {
    // Book tracker variable types

    string title="Demian";                    // book title
    string author="Hermann Hesse";            // book author
    char status = 'R';                        // reading status
    int pages = 176;                          // total pages
    int pagesRead = 86;                       // pages read
    string developerName= "Brian Molina";     // developer name
    float version = 1.0;                      // application version

    cout << "Welcome to Book Tracker" << endl;
    cout << "================================" << endl;
    cout << "Developer Name: " << developerName << endl;
    cout << "Version: " << version << endl;
    cout << "================================" << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl; 
    cout << "Pages: " << pages << endl;
    cout << "Pages Read: " << pagesRead << endl;
    cout << "Status: " << status << " (U=Unread, R=Reading, D=Done)" << endl;
    return 0;
}