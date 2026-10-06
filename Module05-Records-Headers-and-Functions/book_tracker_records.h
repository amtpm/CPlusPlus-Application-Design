#ifndef BOOKTOOLS_H
#define BOOKTOOLS_H

#include <string>
#include <vector>

struct Book {
    std::string title;
    std::string author;
    int pages;
};

void showMessage();
void addBook(std::vector<Book>& books, const std::string& title,
             const std::string& author, int pages);
void displayBooks(const std::vector<Book>& books);
int totalPages(const std::vector<Book>& books);

#endif