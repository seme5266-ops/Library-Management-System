#include <stdio.h>
#include <stdlib.h>
#include "lms.h"

void save_data(void)
{
    FILE *fp = fopen("books.dat", "wb");
    if (!fp) { printf("Cannot open books.dat\n"); return; }
    for (Book *b = books; b; b = b->next) fwrite(b, sizeof(Book), 1, fp);
    fclose(fp);

    fp = fopen("issued.dat", "wb");
    if (!fp) { printf("Cannot open issued.dat\n"); return; }
    for (Issue *p = issues; p; p = p->next) fwrite(p, sizeof(Issue), 1, fp);
    fclose(fp);

    printf("Data saved.\n");
}

void load_data(void)
{
    FILE *fp = fopen("books.dat", "rb");
    Book *bt = NULL;
    if (fp) {
        for (;;) {
            Book *b = malloc(sizeof(Book));
            if (!b) break;
            if (fread(b, sizeof(Book), 1, fp) != 1) { free(b); break; }
            b->next = NULL;
            if (bt) bt->next = b; else books = b;
            bt = b;
        }
        fclose(fp);
    }

    fp = fopen("issued.dat", "rb");
    Issue *it = NULL;
    if (fp) {
        for (;;) {
            Issue *p = malloc(sizeof(Issue));
            if (!p) break;
            if (fread(p, sizeof(Issue), 1, fp) != 1) { free(p); break; }
            p->next = NULL;
            if (it) it->next = p; else issues = p;
            it = p;
        }
        fclose(fp);
    }
}
