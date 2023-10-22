#include <stdio.h>

int main() {
    FILE *file; // Mendeklarasikan pointer ke FILE
    char data[] = "Ini adalah contoh tulisan ke dalam file.";
    
    // Membuka file untuk ditulis
    file = fopen("contoh.txt", "w");
    
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }
    
    // Menulis data ke dalam file
    fputs(data, file);
    
    // Menutup file
    fclose(file);
    
    return 0;
}
