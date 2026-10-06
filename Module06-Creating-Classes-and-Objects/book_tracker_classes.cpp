#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int pages;

public:
    // Constructor
    Book(string bookTitle, string bookAuthor, int bookPages) {
        title = bookTitle;
        author = bookAuthor;
        pages = bookPages;
    }

    // Member function
    void displayBook() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }

    // Getter
    string getTitle() {
        return title;
    }

    // Setter
    void setPages(int newPages) {
        pages = newPages;
    }
};

int main() {
    Book book1("Demian", "Hermann Hesse", 176);
    Book book2("Crime and Punishment", "Fyodor Dostoevsky", 551);

    book1.displayBook();
    cout << endl;
    book2.displayBook();

    return 0;
}