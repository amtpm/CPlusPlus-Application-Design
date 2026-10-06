#include <iostream>
#include "book_tracker_records.h"
using namespace std;

void showMessage() {
    cout << "Book tracker ready!" << endl;
}

void addBook(vector<Book>& books, const string& title,
             const string& author, int pages) {
    Book b;
    b.title = title;
    b.author = author;
    b.pages = pages;
    books.push_back(b);
}

void displayBooks(const vector<Book>& books) {
    for (size_t i = 0; i < books.size(); i++) {
        cout << i + 1 << ". " << books[i].title << " by " << books[i].author
             << " (" << books[i].pages << " pages)" << endl;
    }
}

int totalPages(const vector<Book>& books) {
    int total = 0;
    for (const Book& b : books) {
        total += b.pages;
    }
    return total;
}

int main() {
    vector<Book> books;

    showMessage();

    addBook(books, "Demian", "Hermann Hesse", 176);
    addBook(books, "Crime and Punishment", "Fyodor Dostoevsky", 551);

    displayBooks(books);
    cout << "Total pages: " << totalPages(books) << endl;

    return 0;
}