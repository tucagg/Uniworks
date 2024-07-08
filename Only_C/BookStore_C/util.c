#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

Library library;
StudentList studentList;

void displayMenu() {
    printf("----- LIBRARY MANAGEMENT SYSTEM -----\n");
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. Update Book\n");
    printf("4. Filter and Sort Books\n");
    printf("5. Reverse Library\n");
    printf("6. Search Book\n");
    printf("7. Borrow Book\n");
    printf("8. Return Book\n");
    printf("9. Save Library to File\n");
    printf("10. Load Library from File\n");
    printf("11. Add Student\n");
    printf("12. Load Students from File\n");
    printf("13. Exit\n");
    printf("Enter your choice: ");
}

void addBook(const char *isbn, const char *title, const char *author, int publicationYear, int isBorrowed, const char *borrower) {
    if (library.count >= MAX_BOOKS) {
        printf("Library is full. Book cannot be added.\n");
        return;
    }

    strcpy(library.books[library.count].isbn, isbn);
    strcpy(library.books[library.count].title, title);
    strcpy(library.books[library.count].author, author);
    library.books[library.count].publicationYear = publicationYear;
    library.books[library.count].isBorrowed = isBorrowed;
    strcpy(library.books[library.count].borrower, borrower);

    library.count++;

    printf("Book added successfully.\n");

    // Add book information to file
    FILE *file = fopen("books.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s|%s|%d|%d|%s\n", isbn, title, author, publicationYear, isBorrowed, borrower);
        fclose(file);
    } else {
        printf("File could not be opened.\n");
    }
}

void deleteBook(const char *isbn) {
    int found = 0;
    int index = -1;

    for (int i = 0; i < library.count; i++) {
        if (strcmp(library.books[i].isbn, isbn) == 0) {
            index = i;
            found = 1;
            break;
        }
    }

    if (found) {
        for (int i = index; i < library.count - 1; i++) {
            library.books[i] = library.books[i + 1];
        }
        library.count--;
        printf("Book deleted successfully.\n");

        // Remove book from file
        FILE *file = fopen("books.txt", "w");
        if (file != NULL) {
            for (int i = 0; i < library.count; i++) {
                fprintf(file, "%s|%s|%s|%d|%d|%s\n",
                        library.books[i].isbn,
                        library.books[i].title,
                        library.books[i].author,
                        library.books[i].publicationYear,
                        library.books[i].isBorrowed,
                        library.books[i].borrower);
            }
            fclose(file);
        } else {
            printf("File could not be opened.\n");
        }
    } else {
        printf("Book not found.\n");
    }
}

void updateBook(const char *isbn, const char *property, const char *value) {
    int found = 0;

    for (int i = 0; i < library.count; i++) {
        if (strcmp(library.books[i].isbn, isbn) == 0) {
            if (strcmp(property, "isbn") == 0) {
                strcpy(library.books[i].isbn, value);
            } else if (strcmp(property, "title") == 0) {
                strcpy(library.books[i].title, value);
            } else if (strcmp(property, "author") == 0) {
                strcpy(library.books[i].author, value);
            } else if (strcmp(property, "publicationYear") == 0) {
                library.books[i].publicationYear = atoi(value);
            } else {
                printf("Invalid property name.\n");
                return;
            }

            found = 1;
            break;
        }
    }

    if (found) {
        printf("Book updated successfully.\n");
    } else {
        printf("Book not found.\n");
    }
}

void displayBookList(const Book *bookList, int count) {
    if (count == 0) {
        printf("No books found in the library.\n");
        return;
    }

    printf("%-15s%-30s%-30s%-10s%-15s\n", "ISBN", "Title", "Author", "Year", "Borrower");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-15s%-30s%-30s%-10d%-15s\n",
               bookList[i].isbn,
               bookList[i].title,
               bookList[i].author,
               bookList[i].publicationYear,
               bookList[i].borrower);
    }
}

void displayBookInfo(const Book *book) {
    printf("ISBN: %s\n", book->isbn);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Publication Year: %d\n", book->publicationYear);
    printf("Status: %s\n", book->isBorrowed ? "Borrowed" : "Available");
    if (book->isBorrowed) {
        printf("Borrower: %s\n", book->borrower);
    }
}

void filterAndSortBooks(int filterOption, const char *keyword, int sortOption) {
    Book filteredList[MAX_BOOKS];
    int count = 0;

    for (int i = 0; i < library.count; i++) {
        if (filterOption == 1 && strstr(library.books[i].title, keyword) != NULL) {
            filteredList[count] = library.books[i];
            count++;
        } else if (filterOption == 2 && strstr(library.books[i].author, keyword) != NULL) {
            filteredList[count] = library.books[i];
            count++;
        } else if (filterOption == 3 && library.books[i].publicationYear == atoi(keyword)) {
            filteredList[count] = library.books[i];
            count++;
        }
    }

    switch (sortOption) {
        case 1:
            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (strcmp(filteredList[j].title, filteredList[j + 1].title) > 0) {
                        Book temp = filteredList[j];
                        filteredList[j] = filteredList[j + 1];
                        filteredList[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (strcmp(filteredList[j].author, filteredList[j + 1].author) > 0) {
                        Book temp = filteredList[j];
                        filteredList[j] = filteredList[j + 1];
                        filteredList[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (filteredList[j].publicationYear > filteredList[j + 1].publicationYear) {
                        Book temp = filteredList[j];
                        filteredList[j] = filteredList[j + 1];
                        filteredList[j + 1] = temp;
                    }
                }
            }
            break;
    }

    displayBookList(filteredList, count);
}

void borrowBook(const char *isbn, const char *studentName) {
    int found = 0;

    for (int i = 0; i < library.count; i++) {
        if (strcmp(library.books[i].isbn, isbn) == 0) {
            if (library.books[i].isBorrowed) {
                printf("This book is already borrowed.\n");
            } else {
                library.books[i].isBorrowed = 1;
                strcpy(library.books[i].borrower, studentName);
                printf("Book borrowed successfully.\n");

                // Save borrowing information
                FILE *file = fopen("borrows.txt", "a");
                if (file != NULL) {
                    fprintf(file, "%s|%s\n", studentName, isbn);
                    fclose(file);
                } else {
                    printf("File could not be opened.\n");
                }
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void returnBook(const char *isbn) {
    int found = 0;

    for (int i = 0; i < library.count; i++) {
        if (strcmp(library.books[i].isbn, isbn) == 0) {
            if (library.books[i].isBorrowed) {
                library.books[i].isBorrowed = 0;
                library.books[i].borrower[0] = '\0';
                printf("Book returned successfully.\n");

                // Update borrowing information
                FILE *file = fopen("borrows.txt", "r");
                if (file != NULL) {
                    FILE *tempFile = fopen("temp.txt", "w");
                    if (tempFile != NULL) {
                        char studentName[50], bookISBN[20];
                        while (fscanf(file, "%[^|]|%[^\n]\n", studentName, bookISBN) != EOF) {
                            if (strcmp(bookISBN, isbn) != 0) {
                                fprintf(tempFile, "%s|%s\n", studentName, bookISBN);
                            }
                        }
                        fclose(tempFile);
                        fclose(file);
                        remove("borrows.txt");
                        rename("temp.txt", "borrows.txt");
                    } else {
                        fclose(file);
                        printf("Temporary file could not be created.\n");
                    }
                } else {
                    printf("File could not be opened.\n");
                }
            } else {
                printf("This book is already in the library.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void saveLibraryToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    for (int i = 0; i < library.count; i++) {
        fprintf(file, "%s|%s|%s|%d|%d|%s\n",
                library.books[i].isbn,
                library.books[i].title,
                library.books[i].author,
                library.books[i].publicationYear,
                library.books[i].isBorrowed,
                library.books[i].borrower);
    }

    fclose(file);
    printf("Library saved to file successfully.\n");
}

void loadLibraryFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    library.count = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]\n",
                  library.books[library.count].isbn,
                  library.books[library.count].title,
                  library.books[library.count].author,
                  &library.books[library.count].publicationYear,
                  &library.books[library.count].isBorrowed,
                  library.books[library.count].borrower) == 6) {
        library.count++;
    }

    fclose(file);
    printf("Library loaded from file successfully.\n");
}

void addStudent(const char *name, const char *studentID) {
    if (studentList.count >= MAX_STUDENTS) {
        printf("Student list is full. Student cannot be added.\n");
        return;
    }

    strcpy(studentList.students[studentList.count].name, name);
    strcpy(studentList.students[studentList.count].studentID, studentID);

    studentList.count++;

    printf("Student added successfully.\n");

    // Add student information to file
    FILE *file = fopen("students.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s\n", name, studentID);
        fclose(file);
    } else {
        printf("File could not be opened.\n");
    }
}

void loadStudentsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    studentList.count = 0;
    while (fscanf(file, "%[^|]|%[^\n]\n",
                  studentList.students[studentList.count].name,
                  studentList.students[studentList.count].studentID) == 2) {
        studentList.count++;
    }

    fclose(file);
    printf("Student list loaded from file successfully.\n");
}

int maona() {
    library.count = 0;
    studentList.count = 0;

    int choice;
    char isbn[20], title[50], author[50], keyword[50], value[50], studentName[50], studentID[10];
    int publicationYear, filterOption, sortOption;

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("ISBN: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strlen(isbn) - 1] = '\0';

                printf("Title: ");
                fgets(title, sizeof(title), stdin);
                title[strlen(title) - 1] = '\0';

                printf("Author: ");
                fgets(author, sizeof(author), stdin);
                author[strlen(author) - 1] = '\0';

                printf("Publication Year: ");
                scanf("%d", &publicationYear);
                getchar();

                addBook(isbn, title, author, publicationYear, 0, "");
                break;
            case 2:
                printf("ISBN: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strlen(isbn) - 1] = '\0';

                deleteBook(isbn);
                break;
            case 3:
                printf("ISBN: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strlen(isbn) - 1] = '\0';

                printf("Property: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strlen(keyword) - 1] = '\0';

                printf("Value: ");
                fgets(value, sizeof(value), stdin);
                value[strlen(value) - 1] = '\0';

                updateBook(isbn, keyword, value);
                break;
            case 4:
                printf("Filter Options:\n");
                printf("1. Title\n");
                printf("2. Author\n");
                printf("3. Publication Year\n");
                printf("Enter your choice: ");
                scanf("%d", &filterOption);
                getchar();

                printf("Keyword: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strlen(keyword) - 1] = '\0';

                printf("Sort Options:\n");
                printf("1. Title\n");
                printf("2. Author\n");
                printf("3. Publication Year\n");
                printf("Enter your choice: ");
                scanf("%d", &sortOption);
                getchar();

                filterAndSortBooks(filterOption, keyword, sortOption);
                break;
            case 5:
                for (int i = 0, j = library.count - 1; i < j; i++, j--) {
                    Book temp = library.books[i];
                    library.books[i] = library.books[j];
                    library.books[j] = temp;
                }
                printf("Library reversed successfully.\n");
                break;
            case 6:
                printf("ISBN: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strlen(keyword) - 1] = '\0';

                for (int i = 0; i < library.count; i++) {
                    if (strcmp(library.books[i].isbn, keyword) == 0) {
                        displayBookInfo(&library.books[i]);
                        break;
                    }
                }
                break;
            case 7:
                printf("Student Name: ");
                fgets(studentName, sizeof(studentName), stdin);
                studentName[strlen(studentName) - 1] = '\0';

                printf("ISBN: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strlen(isbn) - 1] = '\0';

                borrowBook(isbn, studentName);
                break;
            case 8:
                printf("Enter the ISBN of the book to be returned: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strlen(isbn) - 1] = '\0';

                returnBook(isbn);
                break;
            case 9:
                printf("Enter the filename: ");
                fgets(value, sizeof(value), stdin);
                value[strlen(value) - 1] = '\0';

                saveLibraryToFile(value);
                break;
            case 10:
                printf("Enter the filename: ");
                fgets(value, sizeof(value), stdin);
                value[strlen(value) - 1] = '\0';

                loadLibraryFromFile(value);
                break;
            case 11:
                printf("Student Name: ");
                fgets(studentName, sizeof(studentName), stdin);
                studentName[strlen(studentName) - 1] = '\0';

                printf("Student ID: ");
                fgets(studentID, sizeof(studentID), stdin);
                studentID[strlen(studentID) - 1] = '\0';

                addStudent(studentName, studentID);
                break;
            case 12:
                printf("Enter the filename: ");
                fgets(value, sizeof(value), stdin);
                value[strlen(value) - 1] = '\0';

                loadStudentsFromFile(value);
                break;
            case 13:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        printf("\n");
    } while (choice != 13);

    return 0;
}
