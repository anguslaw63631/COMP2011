#include "Book.h"
#include <iostream>
#include <cstring>

using namespace std;

/*
 * Task 1: Constructor of a new book.
 * In this part, all the information of a book including numPages, numAuthor, authorList, 
 * name, next will be initialized.
 * Note that next would be initialized as nullptr in the constructor, and its value would 
 * be set in main.cpp after a book is constructed. 
 * Remember to allocate memory for variable name, numAuthor, and each element in the array
 * numAuthor.
 */
Book::Book(const char * name, char * const * authorList, int numPages, int numAuthor) 
    //: numPages(numPages), numAuthor(numAuthor), next(nullptr)  //this is called a member initialization which will be covered in COMP2012, don't worry about it now. you don't need to use this line
{
    this->numPages = numPages;
    this->numAuthor = numAuthor;
    this->next = next;
    
    this->name = new char [strlen(name) + 1];
    strcpy(this->name, name);
    this->authorList = new char* [numAuthor + 1];
    for (int index = 0; index < numAuthor; ++index) {
        this->authorList[index] = new char[strlen(authorList[index]) + 1];
        strcpy(this->authorList[index], authorList[index]);
    }
}

/*
 * Task 2: Destructor to delete an existing book.
 * In this part, all the memory allocated previously in the constructor should be deallocated.
 * Note that for an array (e.g., numAuthor), the array as a whole and each element in the 
 * array should be deallocated respectively.
 */
Book::~Book() {
    cout << "Delete the book titled \"" << name << "\"" << endl;
    delete [] name;
    for (int index = 0; index < numAuthor; ++index) {
        delete [] authorList[index];
    }
    delete [] authorList;
}

/*
 * A given function to print out the information of one single book.
 */
void Book::printSingleBookInfo() const {
    cout << name<<" : "<< numPages <<" Pages, By ";
    for (int index = 0; index < numAuthor; ++index) {
        if (index != 0) {
            cout << ", ";
        }
        cout << authorList[index];
    }
    cout << "." << endl;

}

/*
 * Task 3: Search for and print out information of book(s) with a given name.
 * Note that the strcmp function can be used to compare two strings.
 * The function printSingleBookInfo() can be used to print out the information of a given book.
 * Since the books are stored in a linked list, next is a pointer to the next book. And for 
 * the last book, next should be nullptr.
 */
void Book::printBookInfoByName(const char * name) const {
    if (strcmp(this -> name, name) == 0) {
        printSingleBookInfo();
    }
    if (next != nullptr) {
        next -> printBookInfoByName(name);
    }
}

/*
 * Task 4: Search for and print out information of book(s) of a given author.
 * Note that the strcmp function can be used to compare two strings.
 * The function printSingleBookInfo() can be used to print out the information of a given book.
 * Since the books are stored in a linked list, next is a pointer to the next book. And for 
 * the last book, next should be nullptr.
 */
 void Book::printBooksInfoByAuthor(const char * authorName) const {
    for (int index = 0; index < numAuthor; ++index) {
        if (strcmp(authorList[index], authorName) == 0) {
            printSingleBookInfo();
            break;
        }
    }
    if (next != nullptr) {
        next -> printBooksInfoByAuthor(authorName);
    }
}

/*
 * Print out the information of all the books.
 */
void Book::printAllBooks() const {
    printSingleBookInfo();
    if (next != nullptr) {
        next -> printAllBooks();
    }
}

void Book::setNext(Book* book) {
    next = book;
}

/*
 * Task 5: Search for and delete book(s) of a given name.
 * Note that the strcmp function can be used to compare two strings.
 * Since the books are stored in a linked list, next is a pointer to the next book. And for 
 * the last book, next should be nullptr.
 */
void Book::deleteBookByName(const char * name) {
    while (next != nullptr && strcmp(next -> name, name) == 0) {
        Book* toDelete = next;
        next = next -> next;
        delete toDelete;
    }
    if (next != nullptr) {
        next -> deleteBookByName(name);
    }
}

const char* Book::getName() const {
    return name;
}

Book* Book::getNext() {
    return next;
}