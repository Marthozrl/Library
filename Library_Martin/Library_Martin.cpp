// Library_Martin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Book {
private:
    std::string title;
    std::string author;
    std::string publicationDate;
    bool available;

public:
    Book(const std::string& title, const std::string& author, const std::string& publicationDate)
        : title(title), author(author), publicationDate(publicationDate), available(true) {}

    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getPublicationDate() const { return publicationDate; }
    bool isAvailable() const { return available; }

    void setAvailable(bool avail) { available = avail; }
};

class User {
private:
    std::string name;
    std::vector<std::pair<Book*, std::string>> borrowedBooks; 
public:
    User(const std::string& name) : name(name) {}

    const std::string& getName() const { return name; }

    void borrowBook(Book* book, const std::string& dueDate) {
        borrowedBooks.push_back(std::make_pair(book, dueDate));
        book->setAvailable(false);
    }

    void returnBook(Book* book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (it->first == book) {
                borrowedBooks.erase(it);
                book->setAvailable(true);
                return;
            }
        }
        std::cout << "You don't have this book to return!" << std::endl;
    }

    void displayBorrowedBooks() const {
        std::cout << "Books borrowed by " << name << ":" << std::endl;
        for (const auto& pair : borrowedBooks) {
            std::cout << pair.first->getTitle() << " (Due: " << pair.second << ")" << std::endl;
        }
    }
};

int main() {
    
    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "1925");
    Book book2("To Kill a Mockingbird", "Harper Lee", "1960");

    User user1("Alice");
    User user2("Bob");

    user1.borrowBook(&book1, "2024-04-15");
    user2.borrowBook(&book2, "2024-04-20");

    std::cout << "Books available after borrowing:" << std::endl;
    std::cout << book1.getTitle() << ": " << (book1.isAvailable() ? "Available" : "Not available") << std::endl;
    std::cout << book2.getTitle() << ": " << (book2.isAvailable() ? "Available" : "Not available") << std::endl;

    std::cout << std::endl;
    user1.displayBorrowedBooks();
    user2.displayBorrowedBooks();

    user1.returnBook(&book1);

    std::cout << std::endl;
    std::cout << "Books available after returning:" << std::endl;
    std::cout << book1.getTitle() << ": " << (book1.isAvailable() ? "Available" : "Not available") << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
