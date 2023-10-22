#include <stdio.h>

int main() {
    char data[100];
    
    // Membaca data dari stdin (keyboard) dan menyimpannya ke dalam data
    printf("Masukkan data: ");
    fgets(data, sizeof(data), stdin);
    
    // Menulis data ke stdout (layar)
    printf("Anda memasukkan: %s", data);
    
    return 0;
}
