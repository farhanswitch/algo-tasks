#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum Type
{
    NOVEL = 1,
    HISTORY,
    COURSE,
    OTHERS
} TYPE;
typedef struct Book
{
    char code[50];
    char title[100];
    TYPE bookType;
    unsigned int stock;
    float price;
} BOOK;
typedef struct Transaction
{
    char code[50];
    char title[100];
    float price;
    int count;
    float totalPrice;
} TRANSACTION;
char LIST_TYPE[5][20] = {"Novel", "Sejarah", "Pembelajaran", "Lainnya"};
/**
 * Function to clear the screen
 */
void clearscr();
/**
 * Function to read list book from a file
 */
bool loadBook(BOOK *listBook, int *count);
/**
 * Function to read list history transaction from a file
 */
bool loadTransaction(TRANSACTION *listTransaction, int *countH);
/**
 * Function to print a book
 */
void printBook(BOOK book);
/**
 * Function to print a transaction history
 */
void printTransaction(TRANSACTION transaction);
/**
 * Function to get book type from an enum
 */
char *getBookType(TYPE type);
/**
 * Function to write to a file
 */
void writeBook(FILE *fp, BOOK book);
/**
 * Function to write to a file
 */
void writeTransaction(FILE *fp, TRANSACTION trx);
/**
 * Delete newline (\n) character at the end of string
 */
char *trim(char *s);
/**
 * Fungsi untuk memeriksa apakah sebuah string adalah angka (positif/negatif & integer/decimal).
 * @param str - String yang ingin diperiksa.
 * @param acceptNegative - Apakah menerima angka negatif atau tidak.
 * @param acceptFloat - Apakah menerima angka desimal atau tidak.
 * @return true jika string adalah angka yang valid, false sebaliknya.
 */
bool isValidNumber(char str[], bool acceptNegative, bool acceptFloat);
/**
 * Function to check book name is valid or not
 * @param {char[]} name - Book Name
 * @returns {bool}
 */
bool isValidBookName(char name[]);
/**
 * Function to handle menu Input
 */
void menuInputBook(BOOK *listBook, int *count);
/**
 * Function to handle menu Pembelian
 */
void menuInputTransaction(TRANSACTION *listTransaction, BOOK *listBook, int *countH, int *count);
/**
 * Function to handle menu View Book
 */
void menuViewBooks(BOOK *listBook, int count);
/**
 * Function to handle menu View History
 */
void menuViewHistories(TRANSACTION *listTransaction, int countH);
/**
 * Function to handle menu Delete Book
 */
void menuDeleteBook(BOOK *listBook, int *count);
/**
 * Function to handle menu Delete History
 */
void menuDeleteHistory(TRANSACTION *listTransaction, int *countH);
/**
 * Function check is exists a book with same title
 */
int isBookExistsByTitle(BOOK *listBook, int count, char title[]);
int isBookExistsByCode(BOOK *listBook, int count, char code[]);
int main()
{

    BOOK *listBook = (BOOK *)calloc(10, sizeof(BOOK));
    if (listBook == NULL)
    {
        printf("Tidak bisa mengalokasikan memori.\n");
        return 1;
    }
    TRANSACTION *listTransaction = (TRANSACTION *)calloc(10, sizeof(TRANSACTION));
    if (listTransaction == NULL)
    {

        printf("Tidak bisa mengalokasikan memori.\n");
        return 1;
    }
    int count = -1;
    int countH = -1;
    int res = loadBook(listBook, &count);
    int resH = loadTransaction(listTransaction, &countH);

    bool stillPlay = true;
    while (stillPlay)
    {
        clearscr();
        printf("========================================\n");
        printf("PROGRAM PERPUSTAKAAN\n");
        printf("========================================\n");

        printf("\nMenu:\n");
        printf("1. Input\n");
        printf("2. View History\n");
        printf("3. View Buku\n");
        printf("4. Pembelian\n");
        printf("5. Delete History\n");
        printf("6. Delete Buku\n");
        printf("7. Keluar\n");

        int menu = 0;
        while (true)
        {
            char input[20];
            printf("\nSilahkan pilih menu (1-6): ");
            scanf("%[^\n]s", input);
            getchar();

            // Check is valid number
            if (isValidNumber(input, false, false))
            {
                // Convert string to int
                menu = atoi(input);
                if (menu >= 1 && menu <= 7)
                {
                    break;
                }
            }
            printf("Menu yang anda pilih tidak valid!\n");
        }

        switch (menu)
        {
        case 1:
            menuInputBook(listBook, &count);
            break;
        case 2:
            menuViewHistories(listTransaction, countH);
            break;
        case 3:
            menuViewBooks(listBook, count);
            break;
        case 4:
            menuInputTransaction(listTransaction, listBook, &countH, &count);
            break;
        case 5:
            menuDeleteHistory(listTransaction, &countH);
            break;
        case 6:
            menuDeleteBook(listBook, &count);
            break;
        case 7:
            printf("Terima kasih sudah menggunakan program kami.\n");
            stillPlay = false;
            break;
        }
    }

    FILE *fwrite = fopen("databuku.txt", "w");
    FILE *fwriteH = fopen("datapembelian.txt", "w");
    int i;
    for (i = 0; i <= count; i++)
    {
        writeBook(fwrite, listBook[i]);
    }
    for (i = 0; i <= countH; i++)
    {
        writeTransaction(fwriteH, listTransaction[i]);
    }
    // fclose(fread);
    fclose(fwrite);
    fclose(fwriteH);
    free(listBook);
    free(listTransaction);
    return 0;
}
void menuInputTransaction(TRANSACTION *listTransaction, BOOK *listBook, int *countH, int *count)
{
    bool stillNext = true;
    while (stillNext)
    {
        clearscr();
        TRANSACTION trx;
        BOOK selectedBook;

        // Print All Books
        if (*count < 0)
        {
            printf("Tidak ada buku yang tersedia.\n");
            break;
        }
        else
        {
            for (int i = 0; i <= *count; i++)
            {
                printf("\nBuku ke: %-2d\n", i + 1);
                printBook(listBook[i]);
            }

            // Select book
            int idxBook = 0;
            while (true)
            {
                char input[20];
                printf("Masukkan judul buku yang akan dibeli: ");
                scanf("%[^\n]s", input);
                getchar();

                // get index
                int idx = isBookExistsByTitle(listBook, *count, input);
                // check is book exists
                if (idx != -1)
                {
                    idxBook = idx;
                    selectedBook = listBook[idx];
                    if (selectedBook.stock > 0)
                    {

                        strcpy(trx.title, selectedBook.title);
                        strcpy(trx.code, selectedBook.code);
                        trx.price = selectedBook.price;
                        break;
                    }
                    else
                    {
                        printf("Stok buku yang anda pilih sudah habis\n");
                        continue;
                    }
                }
                printf("Judul Buku tidak valid. Silahkan pilih dari daftar yang tersedia\n");
            }
            // Input count
            while (true)
            {
                char input[20];
                printf("Masukkan jumlah buku yang akan dibeli: ");
                scanf("%[^\n]s", input);
                getchar();

                // check is valid number
                if (isValidNumber(input, false, false))
                {
                    // convert string to int
                    trx.count = atoi(input);
                    int left = selectedBook.stock - trx.count;

                    // check is book stock is enough
                    if (left >= 0 && trx.count > 0)
                    {
                        trx.totalPrice = trx.count * trx.price;
                        listBook[idxBook].stock -= trx.count;
                        break;
                    }
                    else
                    {
                        printf("Jumlah tidak valid. Jumlah tidak bisa melebihi stok yang tersedia\n");
                        continue;
                    }
                }
                printf("Jumlah tidak valid. Jumlah harus berupa angka\n");
            }

            // save transaction
            *countH += 1;
            listTransaction[*countH] = trx;

            printf("\nTransaksi berhasil disimpan.\n");
            while (true)
            {
                char input[20];
                printf("\nApakah anda ingin membeli lagi (y/n) ?");
                scanf("%[^\n]s", input);
                getchar();
                if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0)
                {
                    break;
                }
                else if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0)
                {
                    stillNext = false;
                    break;
                }
            }
        }
    }
}
void menuInputBook(BOOK *listBook, int *count)
{
    clearscr();
    BOOK currentBook;

    // Input Book Code
    while (true)
    {
        char input[20];
        printf("Masukkan Kode Buku: ");
        scanf("%[^\n]s", input);
        getchar();

        // Check is valid string
        if (!isValidBookName(input))
        {

            printf("Kode Buku tidak valid.\n");
            continue;
        }
        int idxExisting = isBookExistsByCode(listBook, *count, input);
        // Handle if exists
        if (idxExisting != -1)
        {
            printf("Kode Buku sudah digunakan. Silahkan gunakan kode yang lain\n");
            continue;
        }
        strcpy(currentBook.code, input);
        break;
    }

    // Input Book Title
    while (true)
    {
        char input[20];
        printf("Masukkan Judul Buku: ");
        scanf("%[^\n]s", input);
        getchar();

        // Check is valid string
        if (!isValidBookName(input))
        {

            printf("Judul Buku tidak valid.\n");
            continue;
        }
        // Check is already exists

        int idxExisting = isBookExistsByTitle(listBook, *count, input);
        if (idxExisting != -1)
        {
            printf("Judul buku sudah digunakan.\n");
            continue;
            ;
        }
        strcpy(currentBook.title, input);
        break;
    }

    printf("\nJenis Buku: \n");
    printf("1. Novel\n");
    printf("2. Sejarah\n");
    printf("3. Pembelajaran\n");
    printf("4. Lainnya\n");

    while (true)
    {
        char input[20];
        printf("Masukkan jenis buku (1-4): ");
        scanf("%[^\n]s", input);
        getchar();

        // Check is valid number
        if (isValidNumber(input, false, false))
        {
            // Convert string to number
            int bookType = atoi(input);
            // Check is valid book type
            if (bookType >= NOVEL && bookType <= OTHERS)
            {
                currentBook.bookType = bookType;
                break;
            }
        }
        printf("Jenis Buku tidak valid. Silahkan pilih dari daftar yang tersedia.\n");
    }

    // Input Book Stock
    while (true)
    {
        char input[20];
        printf("Masukkan jumlah stok: ");
        scanf("%[^\n]s", input);
        getchar();

        // Check input is valid number
        if (isValidNumber(input, false, false))
        {
            // Convert to int and assign the value
            currentBook.stock = atoi(input);
            break;
        }
        printf("Stok Buku harus merupakan angka yang valid.\n");
    }
    // Input Book Price
    while (true)
    {
        char input[20];
        printf("Masukkan harga buku: Rp ");
        scanf("%[^\n]s", input);
        getchar();

        // check is valid price
        if (isValidNumber(input, false, true))
        {
            currentBook.price = atof(input);
            break;
        }
        printf("Harga Buku tidak valid.\n");
    }

    // set value
    *count += 1;
    listBook[*count] = currentBook;
    printf("\nBuku berhasil disimpan\n");
    printf("\nKetik enter untuk kembali ke menu utama...");
    while (getchar() != '\n')
    {
    }
}
void menuViewHistories(TRANSACTION *listTransaction, int countH)
{
    clearscr();
    if (countH < 0)
    {
        printf("Anda tidak memiliki catatan penjualan!\n");
    }
    else
    {

        for (int i = 0; i <= countH; i++)
        {
            printf("\nTransaksi ke: %-2d\n", i + 1);
            printTransaction(listTransaction[i]);
        }
    }
    printf("\nTekan enter untuk kembali ke menu utama...");
    while (getchar() != '\n')
    {
    }
}
void menuViewBooks(BOOK *listBook, int count)
{
    clearscr();
    if (count < 0)
    {
        printf("Anda tidak memiliki buku!\n");
    }
    else
    {

        for (int i = 0; i <= count; i++)
        {
            printf("\nBuku ke: %-2d\n", i + 1);
            printBook(listBook[i]);
        }
    }
    printf("\nTekan enter untuk kembali ke menu utama...");
    while (getchar() != '\n')
    {
    }
}
void printBook(BOOK book)
{
    printf("%-20s: %s\n", "Kode Buku", book.code);
    printf("%-20s: %s\n", "Judul Buku", book.title);
    printf("%-20s: %d\n", "Stok", book.stock);
    printf("%-20s: Rp%.2f\n", "Harga Buku", book.price);
}
void printTransaction(TRANSACTION transaction)
{
    printf("%-20s: %s\n", "Kode Buku", transaction.code);
    printf("%-20s: %s\n", "Judul Buku", transaction.title);
    printf("%-20s: Rp%.2f\n", "Harga Buku", transaction.price);
    printf("%-20s: %d pcs\n", "Jumlah", transaction.count);
    printf("%-20s: Rp%.2f\n", "Total Harga Buku", transaction.totalPrice);
}
void menuDeleteHistory(TRANSACTION *listTransaction, int *countH)
{
    clearscr();
    if (*countH < 0)
    {
        printf("Anda tidak memiliki catatan penjualan!\n");
    }
    else
    {

        for (int i = 0; i <= *countH; i++)
        {
            printf("\nTransaksi ke: %-2d\n", i + 1);
            printTransaction(listTransaction[i]);
        }

        int indexToDelete = -1;
        while (true)
        {
            char input[20];
            printf("Masukkan nomor urut transaksi untuk dihapus (1-%d): ", *countH + 1);
            scanf("%[^\n]s", input);
            getchar();

            // Check is valid number
            if (isValidNumber(input, false, false))
            {
                // Convert to int
                indexToDelete = atoi(input);
                // Check is valid index
                if (indexToDelete >= 1 && indexToDelete <= *countH + 1)
                {
                    break;
                }
            }
            printf("Nomor urut transsaksi tidak valid.\n");
        }
        int i;
        for (i = indexToDelete - 1; i < *countH; i++)
        {
            if ((i + 1) <= *countH)
            {

                listTransaction[i] = listTransaction[i + 1];
            }
        }
        *countH -= 1;
        printf("Data Successfully delete...\n");
    }
    printf("\nTekan enter untuk kembali ke menu utama...");
    while (getchar() != '\n')
    {
    }
}
void menuDeleteBook(BOOK *listBook, int *count)
{
    clearscr();
    if (*count < 0)
    {
        printf("Anda tidak memiliki buku!\n");
    }
    else
    {

        for (int i = 0; i <= *count; i++)
        {
            printf("\nBuku ke: %-2d\n", i + 1);
            printBook(listBook[i]);
        }

        int indexToDelete = -1;
        while (true)
        {
            char input[20];
            printf("Masukkan nomor urut buku untuk dihapus (1-%d): ", *count + 1);
            scanf("%[^\n]s", input);
            getchar();

            // Check is valid number
            if (isValidNumber(input, false, false))
            {
                // Convert to int
                indexToDelete = atoi(input);
                // Check is valid index
                if (indexToDelete >= 1 && indexToDelete <= *count + 1)
                {
                    break;
                }
            }
            printf("Nomor urut buku tidak valid.\n");
        }
        int i;
        for (i = indexToDelete - 1; i < *count; i++)
        {
            if ((i + 1) <= *count)
            {

                listBook[i] = listBook[i + 1];
            }
        }
        *count -= 1;
        printf("Book Successfully delete...\n");
    }
    printf("\nTekan enter untuk kembali ke menu utama...");
    while (getchar() != '\n')
    {
    }
}
char *trim(char *s)
{
    int i = strlen(s) - 1;
    if ((i > 0) && (s[i] == '\n'))
        s[i] = '\0';
    return s;
}
int isBookExistsByTitle(BOOK *listBook, int count, char title[])
{

    int i;
    for (i = 0; i <= count; i++)
    {
        if (strcmp(listBook[i].title, title) == 0)
        {
            return i;
        }
    }
    return -1;
}
int isBookExistsByCode(BOOK *listBook, int count, char code[])
{
    int i;
    for (i = 0; i <= count; i++)
    {
        if (strcmp(listBook[i].code, code) == 0)
        {
            return i;
        }
    }
    return -1;
}
void writeBook(FILE *fp, BOOK book)
{
    fputs("---\n", fp);
    fprintf(fp, "%s\n", book.code);
    fprintf(fp, "%s\n", book.title);
    fprintf(fp, "%d\n", book.bookType);
    fprintf(fp, "%d\n", book.stock);
    fprintf(fp, "%.2f\n", book.price);
}
void writeTransaction(FILE *fp, TRANSACTION trx)
{
    fputs("---\n", fp);
    fprintf(fp, "%s\n", trx.code);
    fprintf(fp, "%s\n", trx.title);
    fprintf(fp, "%.2f\n", trx.price);
    fprintf(fp, "%d\n", trx.count);
    fprintf(fp, "%.2f\n", trx.totalPrice);
}
char *getBookType(TYPE type)
{
    if (type >= NOVEL && type <= OTHERS)
    {
        char *str = (char *)malloc(10 * sizeof(char));
        if (str == NULL)
        {
            printf("Memory allocation failed.\n");
            return NULL;
        }
        strcpy(str, LIST_TYPE[type]);
        return str;
    }
    return "";
}
bool loadTransaction(TRANSACTION *listTransaction, int *countH)
{
    FILE *fread = fopen("datapembelian.txt", "r");
    if (fread == NULL)
    {
        return false;
    }
    int bufferLength = 255;
    char buffer[255];
    int sequence = 0;
    TRANSACTION currentTransaction;
    while (fgets(buffer, bufferLength, fread))
    {
        if (strcmp(buffer, "---\n") == 0)
        {

            *countH += 1;
            sequence = 0;
        }
        else
        {
            if (*countH > -1)
            {
                switch (sequence)
                {
                case 0:

                    strcpy(currentTransaction.code, trim(buffer));

                    sequence++;
                    break;
                case 1:
                    strcpy(currentTransaction.title, trim(buffer));
                    sequence++;
                    break;
                case 2:
                    currentTransaction.price = atof(buffer);
                    sequence++;
                    break;
                case 3:
                    currentTransaction.count = atoi(buffer);
                    sequence++;
                    break;
                case 4:
                    currentTransaction.totalPrice = atof(buffer);
                    sequence = 0;
                    listTransaction[*countH] = currentTransaction;
                    break;
                }
            }
        }
    }
    fclose(fread);
    return true;
}
bool loadBook(BOOK *listBook, int *count)
{
    FILE *fread = fopen("databuku.txt", "r");
    if (fread == NULL)
    {
        return false;
    }
    int bufferLength = 255;
    char buffer[255];
    int sequence = 0;
    BOOK currentBook;
    while (fgets(buffer, bufferLength, fread))
    {
        if (strcmp(buffer, "---\n") == 0)
        {

            *count += 1;
            sequence = 0;
        }
        else
        {
            if (*count > -1)
            {
                switch (sequence)
                {
                case 0:

                    strcpy(currentBook.code, trim(buffer));

                    sequence++;
                    break;
                case 1:
                    strcpy(currentBook.title, trim(buffer));
                    sequence++;
                    break;
                case 2:
                    currentBook.bookType = (TYPE)atoi(buffer);
                    sequence++;
                    break;
                case 3:
                    currentBook.stock = atoi(buffer);
                    sequence++;
                    break;
                case 4:
                    currentBook.price = atof(buffer);
                    sequence = 0;
                    listBook[*count] = currentBook;
                    break;
                }
            }
        }
    }
    fclose(fread);
    return true;
}
void clearscr()
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || \
    (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
#error "OS not supported."
#endif
}
bool isValidNumber(char str[], bool acceptNegative, bool acceptFloat)
{
    bool isValid = true;
    int startIndex = 0;
    int endIndex = strlen(str) - 1;
    int dotCount = 0;

    if (acceptNegative && str[startIndex] == '-')
    {
        startIndex = 1; // Mengabaikan tanda negatif jika diterima
    }

    for (int i = startIndex; i <= endIndex; i++)
    {
        if (str[i] == '.')
        {
            dotCount++;
            if (dotCount > 1 || !acceptFloat)
            {
                isValid = false;
                break;
            }
        }
        else if (str[i] < '0' || str[i] > '9')
        {
            isValid = false;
            break;
        }
    }

    return isValid;
}
bool isValidBookName(char name[])
{
    int len = strlen(name);
    // Name cannot be empty
    if (len == 0)
    {
        return false;
    }
    // Name cannot be the same as the separator
    else if (strcmp(name, "---") == 0)
    {
        return false;
    }
    return true;
}