#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int isIssued;
    struct Book* next;
};

struct Book* head = NULL;

// Create new node
struct Book* createNode(int id, char title[], char author[], int isIssued) {
    struct Book* newNode = (struct Book*)malloc(sizeof(struct Book));
    newNode->id = id;
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->isIssued = isIssued;
    newNode->next = NULL;
    return newNode;
}

// Add book
void addBook() {
    int id;
    char title[50], author[50];

    printf("Enter Book ID: ");
    scanf("%d", &id);

    printf("Enter Title (no spaces): ");
    scanf("%s", title);

    printf("Enter Author (no spaces): ");
    scanf("%s", author);

    struct Book* newNode = createNode(id, title, author, 0);

    if (head == NULL) {
        head = newNode;
    } else {
        struct Book* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Book added successfully!\n");
}

// Display books
void displayBooks() {
    if (head == NULL) {
        printf("No books available.\n");
        return;
    }

    struct Book* temp = head;
    while (temp != NULL) {
        printf("ID: %d | Title: %s | Author: %s | %s\n",
               temp->id,
               temp->title,
               temp->author,
               temp->isIssued ? "Borrowed" : "Available");
        temp = temp->next;
    }
}

// Search book
struct Book* searchBook(int id) {
    struct Book* temp = head;
    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Borrow book
void borrowBook() {
    int id;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);

    struct Book* book = searchBook(id);

    if (book == NULL) {
        printf("Book not found.\n");
    } else if (book->isIssued) {
        printf("Book already borrowed.\n");
    } else {
        book->isIssued = 1;
        printf("Book borrowed successfully!\n");
    }
}

// Return book
void returnBook() {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    struct Book* book = searchBook(id);

    if (book == NULL) {
        printf("Book not found.\n");
    } else if (!book->isIssued) {
        printf("Book is already available.\n");
    } else {
        book->isIssued = 0;
        printf("Book returned successfully!\n");
    }
}

// Save to file
void saveToFile() {
    FILE* file = fopen("books.txt", "w");
    struct Book* temp = head;

    while (temp != NULL) {
        fprintf(file, "%d %s %s %d\n",
                temp->id,
                temp->title,
                temp->author,
                temp->isIssued);
        temp = temp->next;
    }

    fclose(file);
}

// Load from file
void loadFromFile() {
    FILE* file = fopen("books.txt", "r");
    if (file == NULL)
        return;

    int id, isIssued;
    char title[50], author[50];

    while (fscanf(file, "%d %s %s %d", &id, title, author, &isIssued) != EOF) {
        struct Book* newNode = createNode(id, title, author, isIssued);

        if (head == NULL) {
            head = newNode;
        } else {
            struct Book* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    fclose(file);
}

// Main menu
int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n--- Library Menu ---\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Borrow Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3: {
                int id;
                printf("Enter Book ID: ");
                scanf("%d", &id);
                struct Book* book = searchBook(id);
                if (book)
                    printf("Found: %s by %s (%s)\n",
                           book->title,
                           book->author,
                           book->isIssued ? "Borrowed" : "Available");
                else
                    printf("Book not found.\n");
                break;
            }
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                saveToFile();
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}