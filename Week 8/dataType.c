#include <stdio.h>
#include <string.h>

struct Book1
{
    char title[50];
    char writer[50];
};

typedef struct Book2
{
    char title[50];
    char writer[50];
} BOOK;

union Saving1
{
    char text[255];
    int number;
};

typedef union Saving2
{
    char text[255];
    int number;
} SAVING;

int main()
{

    // Tanpa typedef
    struct Book1 b1;
    strcpy(b1.title, "The da Vinci Code");
    strcpy(b1.writer, "Dan Brown");
    union Saving1 s1;
    s1.number = 10000;
    printf("TANPA TYPEDEF\n");
    printf("Buku.\nPenulis: %s\nJudul: %s\n", b1.writer, b1.title);
    printf("Menabung.\nNominal Rp%d\n", s1.number);

    // Dengan typedef
    BOOK buku;
    strcpy(buku.title, "The da Vinci Code");
    strcpy(buku.writer, "Dan Brown");
    SAVING setoran;
    setoran.number = 25000;

    printf("\n\nDENGAN TYPEDEF\n");
    printf("Buku.\nPenulis: %s\nJudul: %s\n", buku.writer, buku.title);
    printf("Menabung.\nNominal Rp%d\n", setoran.number);

    return 0;
}