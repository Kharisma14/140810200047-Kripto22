/*
Nama    : Kharisma Fitri Nurunnisa Siahaan
NPM     : 140810200047
Kelas   : A
Program : Shift Cipher
Tanggal : 16/9/2022
*/

#include <iostream>

std::string encrypt();
std::string decrypt();

int main(){
    int pilihan = 1;
    do
    {
        std::cout << "------------------------\nMenu:\n1. Enkripsi\n2. Dekripsi\n0. Keluar\n";
        std::cout << "------------------------\nMasukkan pilihan: ";
        std::cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            std::cout<<"------------------------\nEncryption:\n";
            std::cout << encrypt() << "\n";
            break;
        case 2:
            std::cout<<"------------------------\nDecryption:\n";
            std::cout <<decrypt()<< "\n";
            break;
        case 0:
            std::cout << "------------------------\nkeluar program.";
            break;
        default:
            std::cout << "------------------------\ninput salah!\n";
            break;
        }
    } while (pilihan != 0);
}
//enkripsi
std::string encrypt()
{
    std::string plaintext, answer;
    int key;
    
    std::cout << "Enter plain text: ";
    std::cin.ignore();
    getline(std::cin, plaintext);
    std::cout << "Enter key: ";
    std::cin >> key;
    for (char ch : plaintext)
    {
        if (islower(ch))    // jika huruf lowercase
        {
            ch = (((ch - 'a') + key) % 26) + 'a';
        }
        else if (isupper(ch))   // jika huruf uppercase
        {
            ch = (((ch - 'A') + key) % 26) + 'A';
        }
        answer.push_back(ch);
    }
    return "Cipher text : " + answer;
}
//deskripsi
std::string decrypt()
{
    std::string ciphertext, answer;
    int key;
    std::cout << "Enter cipher text: ";
    std::cin.ignore();
    getline(std::cin, ciphertext);
    std::cout << "Enter key: ";
    std::cin >> key;
    for (char ch : ciphertext)
    {
        if (islower(ch))    // jika huruf lowercase
        {
            ch = ((ch + (26 - key) - 'a') % 26) + 'a';
        }
        else if (isupper(ch)) // jika huruf uppercase
        {
            ch = ((ch + (26 - key) - 'A') % 26) + 'A';
        }
        answer.push_back(ch);
    }
    return "Plain text : " + answer;
}