#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    int pages;
    bool isBorrowed;

public:
    Book(int id, std::string t, std::string a, int p, bool status)
        : id(id), title(t), author(a), pages(p), isBorrowed(status) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    
    void display() const {
        std::cout << "[" << id << "] " << title << " by " << author 
                  << " (" << pages << " pages) - " 
                  << (isBorrowed ? "Borrowed" : "Available") << "\n";
    }

    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            std::cout << "You successfully borrowed '" << title << "'.\n";
        } else {
            std::cout << "Sorry, this book is already borrowed.\n";
        }
    }

    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            std::cout << "You successfully returned '" << title << "'.\n";
        } else {
            std::cout << "This book was not borrowed.\n";
        }
    }
};

std::vector<Book> loadBooks(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, author, pagesStr, statusStr;

        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, title, ',') &&
            std::getline(ss, author, ',') &&
            std::getline(ss, pagesStr, ',') &&
            std::getline(ss, statusStr, ',')) {
            
            int id = std::stoi(idStr);
            int pages = std::stoi(pagesStr);
            bool isBorrowed = (statusStr == "Borrowed");
            books.push_back(Book(id, title, author, pages, isBorrowed));
        }
    }
    return books;
}

int main() {
    auto books = loadBooks("bookData.txt");
    if (books.empty()) {
        std::cout << "No books loaded. Check bookData.txt file.\n";
        return 1;
    }

    int choice = 0;
    while (choice != 5) {
        std::cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
        std::cout << "1. Display All Books\n";
        std::cout << "2. View Specific Book\n";
        std::cout << "3. Borrow a Book\n";
        std::cout << "4. Return a Book\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\n--- Book List ---\n";
            for (const auto& b : books) b.display();
        } else if (choice == 2 || choice == 3 || choice == 4) {
            int bookId;
            std::cout << "Enter Book ID: ";
            std::cin >> bookId;
            bool found = false;

            for (auto& b : books) {
                if (b.getId() == bookId) {
                    found = true;
                    if (choice == 2) b.display();
                    else if (choice == 3) b.borrowBook();
                    else if (choice == 4) b.returnBook();
                    break;
                }
            }
            if (!found) std::cout << "Book ID not found!\n";
        }
    }
    std::cout << "Exiting system. Goodbye!\n";
    return 0;
}