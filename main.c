#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lms.h"

Book *books = NULL;
Issue *issues = NULL;

void read_line(const char *prompt, char *buf, int n)
{
    printf("%s", prompt);
    if (!fgets(buf, n, stdin)) { buf[0] = '\0'; return; }
    buf[strcspn(buf, "\n")] = '\0';
}

int read_int(const char *prompt)
{
    char buf[20];
    read_line(prompt, buf, sizeof buf);
    return atoi(buf);
}

char read_choice(const char *prompt)
{
    char buf[20];
    read_line(prompt, buf, sizeof buf);
    return (char)toupper((unsigned char)buf[0]);
}

int main(void)
{
    int ch;
    load_data();

    for (;;) {
        printf("\n+----------------------------------------+\n");
        printf("|         Book Management Menu           |\n");
        printf("|----------------------------------------|\n");
        printf("| 1. Add New Book                        |\n");
        printf("| 2. Update Book Details                 |\n");
        printf("| 3. Remove Book                         |\n");
        printf("| 4. Search Book                         |\n");
        printf("| 5. View All Books                      |\n");
        printf("| 6. Issue Book                          |\n");
        printf("| 7. Return Book                         |\n");
        printf("| 8. List Issued Books                   |\n");
        printf("| 9. Save                                |\n");
        printf("| 10. Exit                               |\n");
        printf("+----------------------------------------+\n");

        ch = read_int("Enter your choice: ");
        switch (ch) {
        case 1: add_book();    break;
        case 2: update_book(); break;
        case 3: remove_book(); break;
        case 4: search_book(); break;
        case 5: view_books();  break;
        case 6: issue_book();  break;
        case 7: return_book(); break;
        case 8: list_issued(); break;
        case 9: save_data();   break;
        case 10: return 0;
        default: printf("Invalid choice.\n");
        }
    }
}
