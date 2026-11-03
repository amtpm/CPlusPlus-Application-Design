#include <iostream>
#include <fstream>   // File I/O
#include <sstream>   // Splitting lines from file
#include <string>
using namespace std;

// -- Helper functions --

// Lowercase title for case-insensitive search 
string toLower(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

// Keep prompting until user enters a number in range
int readInt(const string& prompt, int min, int max) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        try {
            size_t pos;
            int value = stoi(line, &pos);
            if (pos == line.size() && value >= min && value <= max) {
                return value;
            }
        } catch (...) {
            // Invalid input fall through to error message
        }
        cout << "Invalid input. Enter a number from " << min << " to " << max << "." << endl;
    }
}

// Keep prompting until input is valid
string readText(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        if (!line.empty() && line.find('|') == string::npos) {
            return line;
        }
        cout << "Invalid input. Cannot be empty or contain '|'." << endl;
    }
}

// Keep prompting user until user picks U, R, or D
char readStatus() {
    while (true) {
        cout << "Status (U=Unread, R=Reading, D=Done): ";
        string line;
        getline(cin, line);
        if (!line.empty()) {
            char c = static_cast<char>(toupper(static_cast<unsigned char>(line[0])));
            if (line.size() == 1 && (c == 'U' || c == 'R' || c == 'D')) {
                return c;
            }
        }
        cout << "Invalid status. Enter U, R, or D." << endl;
    }
}

// -- Book --
// Holds info for one book

class Book {
private:
    string title;
    string author;
    string genre;
    int pages;
    char status;  // U = unread, R = reading, D = done

public:
    Book() : title(""), author(""), genre(""), pages(0), status('U') {}

    Book(string t, string a, string g, int p, char s)
        : title(t), author(a), genre(g), pages(p), status(s) {}

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    int getPages() const { return pages; }
    char getStatus() const { return status; }

    // Setter
    void setStatus(char s) { status = s; }

    // Convert status letter into a readable label
    string statusName() const {
        if (status == 'R') return "Reading";
        if (status == 'D') return "Done";
        return "Unread";
    }

    void display() const {
        cout << "Title:  " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Genre:  " << genre << endl;
        cout << "Pages:  " << pages << endl;
        cout << "Status: " << statusName() << endl;
    }
};

// -- Library --
// Stores books sorted by title for binary search

class Library {
private:
    Book* books;    // Pointer to array
    int count;      // Current number of books
    int capacity;   // Total number of slots

    // Increase array when full
    void grow() {
        capacity *= 2;
        Book* bigger = new Book[capacity];   // Dynamic memory
        for (int i = 0; i < count; i++) {
            bigger[i] = books[i];
        }
        delete[] books;
        books = bigger;
    }

public:
    Library() : count(0), capacity(4) {
        books = new Book[capacity];
    }

    // Frees array to avoid memory leaks
    ~Library() {
        delete[] books;
    }

    // Prevent copy so two libraries dont share array and cause double delete
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    int getCount() const { return count; }

    // Insert book in sorted order
    void addBook(const Book& book) {
        if (count == capacity) {
            grow();
        }
        int i = count;
        while (i > 0 && toLower(books[i - 1].getTitle()) > toLower(book.getTitle())) {
            books[i] = books[i - 1];
            i--;
        }
        books[i] = book;
        count++;
    }

    // Binary search by title
    int findIndex(const string& title) const {
        string target = toLower(title);
        int left = 0, right = count - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            string current = toLower(books[mid].getTitle());
            if (current == target) return mid;
            if (current < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    // Pointer to match or null
    Book* search(const string& title) {
        int index = findIndex(title);
        if (index == -1) return nullptr;
        return &books[index];
    }

    // Remove matching book
    bool removeBook(const string& title) {
        int index = findIndex(title);
        if (index == -1) return false;
        for (int i = index; i < count - 1; i++) {
            books[i] = books[i + 1];
        }
        count--;
        return true;
    }

    // Print books in alphabetical order
    void viewAll() const {
        if (count == 0) {
            cout << "No books in the library." << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "\n#" << i + 1 << endl;
            books[i].display();
        }
    }

    // Save book as one line each by title, author, genre, pages,and status
    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) return false;
        for (int i = 0; i < count; i++) {
            file << books[i].getTitle() << "|"
                 << books[i].getAuthor() << "|"
                 << books[i].getGenre() << "|"
                 << books[i].getPages() << "|"
                 << books[i].getStatus() << "\n";
        }
        return true;
    }

    // Load books from file 
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;

        count = 0;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author, genre, pagesText, statusText;
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, genre, '|');
            getline(ss, pagesText, '|');
            getline(ss, statusText, '|');
            if (title.empty() || pagesText.empty() || statusText.empty()) continue;
            try {
                addBook(Book(title, author, genre, stoi(pagesText), statusText[0]));
            } catch (...) {
                // Skip damaged lines
            }
        }
        return true;
    }
};

// -- Data type sizes --
// Show byte sizes
void showDataSizes() {
    cout << "\n=== Data Type Sizes (bytes) ===" << endl;
    cout << "char:      " << sizeof(char) << endl;
    cout << "bool:      " << sizeof(bool) << endl;
    cout << "int:       " << sizeof(int) << endl;
    cout << "float:     " << sizeof(float) << endl;
    cout << "double:    " << sizeof(double) << endl;
    cout << "long long: " << sizeof(long long) << endl;
    cout << "string:    " << sizeof(string) << endl;
    cout << "Book:      " << sizeof(Book) << endl;
    cout << "Book*:     " << sizeof(Book*) << " (a pointer)" << endl;
}

// -- Main --

int main() {
    const string FILENAME = "books.txt";
    Library library;
    int choice = 0;

    // Keep menu open until user exits
    while (choice != 8) {
        cout << "\n=== Book Tracker ===" << endl;
        cout << "1. Add book" << endl;
        cout << "2. View all books" << endl;
        cout << "3. Search by title (binary search)" << endl;
        cout << "4. Remove book" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Load from file" << endl;
        cout << "7. Show data type sizes" << endl;
        cout << "8. Exit" << endl;
        choice = readInt("Choose an option: ", 1, 8);

        switch (choice) {
            case 1: {
                string title = readText("Title: ");
                string author = readText("Author: ");
                string genre = readText("Genre: ");
                int pages = readInt("Pages: ", 1, 10000);
                char status = readStatus();
                library.addBook(Book(title, author, genre, pages, status));
                cout << "Book added." << endl;
                break;
            }
            case 2:
                library.viewAll();
                break;
            case 3: {
                string title = readText("Title to search for: ");
                Book* found = library.search(title);  // Pointer to match
                if (found != nullptr) {
                    cout << "\nFound:" << endl;
                    found->display();  // Use -> because found is a pointer
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 4: {
                string title = readText("Title to remove: ");
                if (library.removeBook(title)) {
                    cout << "Book removed." << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 5:
                if (library.saveToFile(FILENAME)) {
                    cout << "Saved " << library.getCount() << " book(s) to " << FILENAME << endl;
                } else {
                    cout << "Error: could not write to " << FILENAME << endl;
                }
                break;
            case 6:
                if (library.loadFromFile(FILENAME)) {
                    cout << "Loaded " << library.getCount() << " book(s) from " << FILENAME << endl;
                } else {
                    cout << "Error: could not open " << FILENAME << endl;
                }
                break;
            case 7:
                showDataSizes();
                break;
            case 8:
                cout << "Goodbye!" << endl;
                break;
        }
    }

    return 0;
}