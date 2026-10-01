#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lms.h"

Book *find_book(int id)
{
    for (Book *b = books; b; b = b->next)
        if (b->id == id) return b;
    return NULL;
}

static Book *find_book_by_name(const char *name)
{
    for (Book *b = books; b; b = b->next)
        if (strcmp(b->title, name) == 0) return b;
    return NULL;
}

/* Asks "By Book ID / By Book Name" and returns the book, or NULL. */
static Book *select_book(void)
{
    printf("\nA. By Book ID\nB. By Book Name\nC. Back to Main Menu\n");
    char c = read_choice("Enter your choice: ");
    Book *b = NULL;

    if (c == 'A') {
        b = find_book(read_int("Enter Book ID: "));
    } else if (c == 'B') {
        char name[50];
        read_line("Enter Book Name: ", name, sizeof name);
        b = find_book_by_name(name);
    } else return NULL;

    if (!b) printf("Book not found.\n");
    return b;
}

static void print_header(void)
{
    printf("\n%-8s %-30s %-20s %s\n", "Book ID", "Title", "Author", "Quantity");
    printf("--------------------------------------------------------------------\n");
}

static void print_book(const Book *b)
{
    printf("%-8d %-30s %-20s %d\n", b->id, b->title, b->author, b->qty);
}

void add_book(void)
{
    Book *b = malloc(sizeof(Book));
    if (!b) return;

    b->id = read_int("Enter Book ID: ");
    if (find_book(b->id)) {
        printf("Book ID already exists.\n");
        free(b);
        return;
    }
    read_line("Enter Title: ", b->title, sizeof b->title);
    read_line("Enter Author: ", b->author, sizeof b->author);
    b->qty = read_int("Enter Quantity: ");
    b->next = NULL;

    if (!books) books = b;
    else {
        Book *p = books;
        while (p->next) p = p->next;
        p->next = b;
    }
    printf("Book added.\n");
}

void update_book(void)
{
    char buf[50];
    Book *b = select_book();
    if (!b) return;

    read_line("Enter New Title: ", b->title, sizeof b->title);
    read_line("Enter New Author: ", b->author, sizeof b->author);
    read_line("Enter New Quantity: ", buf, sizeof buf);
    b->qty = atoi(buf);
    printf("Book updated.\n");
}

void remove_book(void)
{
    Book *b = select_book();
    if (!b) return;

    if (b == books) books = b->next;
    else {
        Book *p = books;
        while (p->next != b) p = p->next;
        p->next = b->next;
    }
    free(b);
    printf("Book removed.\n");
}

void search_book(void)
{
    char key[50], c;
    int id = 0, found = 0;

    printf("\nA. By Book ID\nB. By Book Name\nC. By Author Name\nD. Back to Main Menu\n");
    c = read_choice("Enter your choice: ");
    if (c == 'A') id = read_int("Enter Book ID: ");
    else if (c == 'B') read_line("Enter Book Name: ", key, sizeof key);
    else if (c == 'C') read_line("Enter Author Name: ", key, sizeof key);
    else return;

    for (Book *b = books; b; b = b->next) {
        if ((c == 'A' && b->id == id) ||
            (c == 'B' && strcmp(b->title, key) == 0) ||
            (c == 'C' && strcmp(b->author, key) == 0)) {
            if (!found) print_header();
            print_book(b);
            found = 1;
        }
    }
    if (!found) printf("Book not found.\n");
}

void view_books(void)
{
    if (!books) { printf("No books available.\n"); return; }
    print_header();
    for (Book *b = books; b; b = b->next) print_book(b);
}
