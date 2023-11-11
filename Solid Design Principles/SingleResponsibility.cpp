/* Simple Demostaration of a libraray management system */

#include <iostream>
#include <ostream>
#include <string>

struct Book {
   std::string title, author;
   double price;
   Book(std::string title, std::string author, double price) : title{title}, author{author}, price{price} {};
   friend std::ostream &operator<<(std::ostream &os, const Book &book) {
      os << "Title: " << book.title << "\nAuthor: " << book.author << "\nPrice: " << book.price << std::endl;
      return os;
   }
};

struct Journal {
   std::string title, author, publisher;
   double price;

   Journal(std::string title, std::string author, std::string publisher, double price) 
      : title {title}, author {author}, publisher {publisher}, price {price} {}
   friend std::ostream &operator<<(std::ostream &os, const Journal &journal) {
      os << "Title: " << journal.title << "\nAuthor: " << journal.author << "\nPublisher name: " << journal.publisher << 
         "\nPrice: "<< journal.price << std::endl;
      return os;
   }
};

template<typename T> struct LibraryManager {
   static void add(const T &item) {
      std::cout << "Adding ..." << std::endl;
      std::cout << item;
   }

   static void edit(const T &item) {
      std::cout << "Editing..." << std::endl;
      std::cout << item;
   }
};

int main() {
   Book book("Hello World", "What", 599.22);
   Journal journal("Hello journalist", "why", "some publisher", 48.33);

   LibraryManager<Book> pm;
   pm.add(book);

   std::cout << "\n";

   LibraryManager<Journal> pm1;
   pm1.edit(journal);
   return 0;
}
