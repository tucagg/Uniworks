#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_BOOKS 100
#define MAX_STUDENTS 100

typedef struct {
    char isbn[20];
    char title[50];
    char author[50];
    int publicationYear;
    int isBorrowed;
    char borrower[50];
} Book;

typedef struct {
    Book books[MAX_BOOKS];
    int count;
} Library;

typedef struct {
    char name[50];
    char studentID[10];
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} StudentList;



int maona();
void displayMenu();
void addBook(const char *isbn, const char *title, const char *author, int publicationYear, int isBorrowed, const char *borrower) ;
void deleteBook(const char *isbn) ;
void updateBook(const char *isbn, const char *property, const char *value);
void displayBookList(const Book *bookList, int count);
void displayBookInfo(const Book *book);
void filterAndSortBooks(int filterOption, const char *keyword, int sortOption);
void borrowBook(const char *isbn, const char *studentName);
void returnBook(const char *isbn);
void saveLibraryToFile(const char *filename);
void loadLibraryFromFile(const char *filename);
void addStudent(const char *name, const char *studentID);
void loadStudentsFromFile(const char *filename);


#endif /* _UTIL_H_ */
