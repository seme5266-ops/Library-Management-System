#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lms.h"

static void fmt_date(time_t t, char *out)
{
    if (t == 0) strcpy(out, "-");
    else strftime(out, 16, "%d-%m-%Y", localtime(&t));
}

void issue_book(void)
{
    Issue *n, *p;
    Book *b;
    int bid = read_int("Enter Book ID: ");

    b = find_book(bid);
    if (!b) { printf("Book not found.\n"); return; }
    if (b->qty <= 0) { printf("Book not available.\n"); return; }

    n = malloc(sizeof(Issue));
    if (!n) return;

    n->issue_id = 1;
    for (p = issues; p; p = p->next)
        if (p->issue_id >= n->issue_id) n->issue_id = p->issue_id + 1;

    n->book_id = bid;
    n->user_id = read_int("Enter User ID: ");
    read_line("Enter User Name: ", n->user_name, sizeof n->user_name);
    n->issue_date = time(NULL);
    n->due_date = n->issue_date + LOAN_DAYS * 24 * 60 * 60;
    n->return_date = 0;
    n->fine = 0;
    n->next = NULL;

    if (!issues) issues = n;
    else {
        for (p = issues; p->next; p = p->next) ;
        p->next = n;
    }
    b->qty--;

    char d1[16], d2[16];
    fmt_date(n->issue_date, d1);
    fmt_date(n->due_date, d2);
    printf("Book issued. Issue ID: %d  Issue Date: %s  Due Date: %s\n", n->issue_id, d1, d2);
}

void return_book(void)
{
    int bid = read_int("Enter Book ID: ");
    int uid = read_int("Enter User ID: ");
    Issue *p;

    for (p = issues; p; p = p->next)
        if (p->book_id == bid && p->user_id == uid && p->return_date == 0) break;
    if (!p) { printf("Issue record not found.\n"); return; }

    p->return_date = time(NULL);
    if (p->return_date > p->due_date) {
        int days = (int)((p->return_date - p->due_date) / (24 * 60 * 60));
        p->fine = days * FINE_PER_DAY;
    }

    Book *b = find_book(bid);
    if (b) b->qty++;

    printf("Book returned. Fine: Rs. %d\n", p->fine);
}

void list_issued(void)
{
    if (!issues) { printf("No issued books.\n"); return; }

    printf("\n%-6s %-8s %-25s %-8s %-15s %-12s %-12s %-12s %s\n",
           "Issue", "Book ID", "Book Title", "User ID", "User Name",
           "Issue Date", "Due Date", "Return Date", "Fine");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    for (Issue *p = issues; p; p = p->next) {
        char d1[16], d2[16], d3[16];
        Book *b = find_book(p->book_id);
        fmt_date(p->issue_date, d1);
        fmt_date(p->due_date, d2);
        fmt_date(p->return_date, d3);
        printf("%-6d %-8d %-25s %-8d %-15s %-12s %-12s %-12s %d\n",
               p->issue_id, p->book_id, b ? b->title : "(removed)",
               p->user_id, p->user_name, d1, d2, d3, p->fine);
    }
}
