#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string username;
public:
    User(string name) : username(name) {}
    
    void viewBooks(string titles[], int size) {
        cout << "\n=== Book List ===" << endl;
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << titles[i] << endl;
        }
    }
};

class Admin : public User {
public:
    Admin(string name) : User(name) {}
    
    void addBook(string titles[], int& size, string newTitle) {
        titles[size] = newTitle;
        size++;
        // Sort after adding
        for (int i = size - 1; i > 0 && titles[i] < titles[i-1]; i--) {
            swap(titles[i], titles[i-1]);
        }
        cout << "Book added: " << newTitle << endl;
    }
    
    void deleteBook(string titles[], int& size, int index) {
        cout << "Deleted: " << titles[index] << endl;
        for (int i = index; i < size - 1; i++) {
            titles[i] = titles[i + 1];
        }
        size--;
    }
};

int binarySearch(string titles[], int size, string target) {
    int left = 0, right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (titles[mid] == target) return mid;
        if (titles[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    // Start with sorted titles
    string titles[10] = {"Crime and Punishment", "Demian", "The Alchemist"};
    int size = 3;
    
    Admin admin("Brian");
    User user("Guest");
    
    // Admin actions
    cout << "=== Admin ===" << endl;
    admin.viewBooks(titles, size);
    admin.addBook(titles, size, "1984");
    admin.viewBooks(titles, size);
    admin.deleteBook(titles, size, 1);
    admin.viewBooks(titles, size);
    
    // Regular user
    cout << "\n=== Regular User ===" << endl;
    user.viewBooks(titles, size);
    
    // Binary search
    cout << "\n=== Search ===" << endl;
    string target = "The Alchemist";
    int result = binarySearch(titles, size, target);
    if (result != -1) {
        cout << "\"" << target << "\" found at position " << result + 1 << endl;
    } else {
        cout << "\"" << target << "\" not found." << endl;
    }
    
    return 0;
}