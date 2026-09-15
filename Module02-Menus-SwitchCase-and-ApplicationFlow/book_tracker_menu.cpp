#include <iostream>
#include <string>
using namespace std;

void addBook() {
    cout << "Add Book selected." << endl;
}

void removeBook() {
    cout << "Remove Book selected." << endl;
}

void viewBooks() {
    cout << "View Books selected." << endl;
}

void searchBooks() {
    cout << "Search Books selected." << endl;
}

void markBookRead() {
    cout << "Mark Book as Read selected." << endl;
}

void markBookUnread() {
    cout << "Mark Book as Unread selected." << endl;
}

int main() {
    int choice = 0;

    while (choice != 7) {
        cout << "\n=== Book Tracker ===" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. View Books" << endl;
        cout << "3. Search Books" << endl;
        cout << "4. Remove Book" << endl;
        cout << "5. Mark Book as Read" << endl;
        cout << "6. Mark Book as Unread" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBooks();
                break;
            case 4:
                removeBook();
                break;
            case 5:
                markBookRead();
                break;
            case 6:
                markBookUnread();
                break;
            case 7:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}