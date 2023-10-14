#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Import required module based on host OS (Windows or Unix/MacOS/Linux)
#ifdef _WIN32
#include <conio.h>
#elif defined(unix) || defined(__unix__) || defined(__unix) || \
    (defined(__APPLE__) && defined(__MACH__))
#include <termios.h>
#include <unistd.h>
#endif

typedef enum Month
{
    JAN,
    FEB,
    MAR,
    APR,
    MEI,
    JUN,
    JUL,
    AGU,
    SEP,
    OKT,
    NOV,
    DES
} MONTH;
char LIST_MONTH[12][20] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
/**
 * Function to handle menu "Pilih Bulan"
 */
void menuChooseMonth();
/**
 * Function to print all months
 */
void printAllMonths();
/**
 * Function to get month
 */
char *getMonth(MONTH month);
/**
 * Function to analyze a month (get vocal letters and consonant letters)
 */
void analyzingMonth(MONTH month);
char getSingleChar(char prompt[]);

/**
 * Function to clear the screen
 */
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

int main()
{
    bool stillPlay = true;
    while (stillPlay)
    {
        clearscr();
        printf("========================================\n");
        printf("PROGRAM CHECK NAMA BULAN\n");
        printf("========================================\n");

        printf("\nMenu:\n");
        printf("1. Pilih Bulan\n");
        printf("2. Keluar\n");

        int menu = 0;
        while (true)
        {
            // ask input from user
            char input = getSingleChar("Pilih menu (1/2)");
            // Check input is a valid number
            if (isdigit(input))
            {
                char str[10] = {input, '\0'};
                // convert into integer
                int number = atoi(str);
                // check is valid option
                if (number >= 1 && number <= 2)
                {
                    menu = number;
                    break;
                }
            }
            printf("Menu tidak valid!\n");
        }
        switch (menu)
        {
        case 1:
            menuChooseMonth();
            break;
        case 2:
            printf("\nTerima kasih sudah menggunakan program kami.\n");
            stillPlay = false;
            break;
        default:
            stillPlay = false;
            break;
        }
    }

    return 0;
}
void menuChooseMonth()
{
    bool stillHere = true;
    while (stillHere)
    {
        clearscr();
        printAllMonths();
        char firstLetter = 'a';
        while (true)
        {
            firstLetter = getSingleChar("Masukkan huruf pertama dari nama bulan");
            if (isalpha(firstLetter))
            {
                firstLetter = toupper(firstLetter);
                break;
            }
            printf("Input tidak valid. Silahkan masukkan huruf.\n");
        }

        int countMatch = 0;
        int listIndexMatch[12];
        int i = JAN;
        for (; i <= DES; i++)
        {
            char strMonth[20];
            //!!Potnetial Error
            char *mnth = getMonth(i);

            strcpy(strMonth, mnth);
            free(mnth);
            if (strMonth[0] == firstLetter)
            {
                listIndexMatch[countMatch] = i;
                countMatch += 1;
            }
        }

        if (countMatch == 0)
        {
            printf("\nTidak ada nama bulan yang memiliki huruf pertama %c\n", firstLetter);
        }
        else
        {
            printf("\nDaftar nama bulan yang berawalan huruf %c:\n", firstLetter);
            int j = 0;
            for (; j < countMatch; j++)
            {
                printf("%d. %s\n", j + 1, getMonth(listIndexMatch[j]));
            }

            int indexSelectedMonth = 0;
            while (true)
            {
                char ch = getSingleChar("\nSilahkan masukkan nomor urut bulan yang ingin anda pilih");
                char stringInput[10] = {ch, '\0'};
                // Check input is valid number
                if (isdigit(ch))
                {
                    indexSelectedMonth = atoi(stringInput);
                    // Check is valid index
                    if (indexSelectedMonth >= 1 && indexSelectedMonth <= countMatch)
                    {
                        break;
                    }
                }
                printf("Input tidak valid. Tolong pilih nomor urut bulan.\n");
            }
            printf("\n\n");
            // Print Month data such as how much vocal letters
            analyzingMonth(listIndexMatch[indexSelectedMonth - 1]);
        }

        while (true)
        {
            char ch = getSingleChar("Apakah anda ingin input lagi? (y/n)");
            if (ch == 'y' || ch == 'Y')
            {
                break;
            }
            else if (ch == 'n' || ch == 'N')
            {
                stillHere = false;
                break;
            }
            else
            {
                printf("Input tidak valid!\n");
            }
        }
    }
}
void printAllMonths()
{
    printf("Daftar nama bulan: \n");
    int i = JAN;
    for (; i <= DES; i++)
    {
        printf("%2d. %s\n", i + 1, getMonth(i));
    }
}
char *getMonth(MONTH month)
{
    if (month >= JAN && month <= DES)
    {
        char *str = (char *)malloc(20 * sizeof(char));

        if (str == NULL)
        {
            printf("Memory allocation failed.\n");
            return NULL; // Return NULL to indicate an error
        }
        strcpy(str, LIST_MONTH[month]);
        return str;
    }
    return "";
}
void analyzingMonth(MONTH month)
{
    int countVocal = 0;
    int listIndexVocal[20];
    int countOthers = 0;
    int listIndexOthers[20];

    char strMonth[20] = "";
    strcpy(strMonth, getMonth(month));
    int i = 0;
    for (; i < strlen(strMonth); i++)
    {
        char lowerCase = tolower(strMonth[i]);
        if (lowerCase == 'a' || lowerCase == 'i' || lowerCase == 'u' || lowerCase == 'e' || lowerCase == 'o')
        {
            listIndexVocal[countVocal] = i;
            countVocal += 1;
        }
        else
        {
            listIndexOthers[countOthers] = i;
            countOthers += 1;
        }
    }

    printf("%-30s: %s\n", "Nama Bulan", strMonth);
    printf("%-30s: %d\n", "Jumlah huruf vokal", countVocal);
    printf("%-30s: ", "Daftar huruf vokal");
    int j = 0;
    for (; j < countVocal; j++)
    {
        char letter = strMonth[listIndexVocal[j]];
        printf("%c", letter);
        if (j != countVocal)
        {
            printf(", ");
        }
    }
    printf("\n");
    printf("%-30s: %d\n", "Jumlah huruf konsonan", countOthers);
    printf("%-30s: ", "Daftar huruf konsonan");
    j = 0;
    for (; j < countOthers; j++)
    {
        char letter = strMonth[listIndexOthers[j]];
        printf("%c", letter);
        if (j != countOthers)
        {
            printf(", ");
        }
    }
    printf("\n");
}
char getSingleChar(char prompt[])
{

    char ch;
    printf("%s: ", prompt);
#ifdef _WIN32
    ch = getch();
#elif defined(unix) || defined(__unix__) || defined(__unix) || \
    (defined(__APPLE__) && defined(__MACH__))
    // Change terminal settings to disable line buffering
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    // Read a single character
    ch = getchar();

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
#else
#error "OS not supported."
#endif
    printf("%c\n", ch);
    return ch;
}
