#ifndef LMS_H
#define LMS_H

#include <time.h>

#define FINE_PER_DAY 5
#define LOAN_DAYS 7

typedef struct book {
    int id;
    char title[50];
    char author[50];
    int qty;
    struct book *next;
} Book;

typedef struct issue {
    int issue_id;
    int book_id;
    int user_id;
    char user_name[50];
    time_t issue_date;
    time_t due_date;
    time_t return_date;     /* 0 = not returned yet */
    int fine;
    struct issue *next;
} Issue;

extern Book *books;
extern Issue *issues;

void read_line(const char *prompt, char *buf, int n);
int  read_int(const char *prompt);
char read_choice(const char *prompt);

void add_book(void);
void update_book(void);
void remove_book(void);
void search_book(void);
void view_books(void);
Book *find_book(int id);

void issue_book(void);
void return_book(void);
void list_issued(void);

void save_data(void);
void load_data(void);

#endif
