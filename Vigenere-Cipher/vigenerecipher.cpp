/*
Nama    : Kharisma Fitri Nurunnisa Siahaan
NPM     : 140810200047
Kelas   : A
Program : Vigenere Cipher
*/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int mod(int x,int y){
    return x >= 0 ? (x%y) : y-(abs(x)%y) ; 
}
void keyBaru(string a, string &key){
    string keytemp;
    keytemp = key;
    int i = 0;
    while(keytemp.size()< a.size()){
        keytemp.push_back(key[i]);
        i++;
        if(i == key.size()){
            i = 0;
        }
    }
    key = keytemp;
}

void encrypt(string pt, string &ct, string key){
    ct ="";
    keyBaru(pt,key);
    for(int i = 0; i<pt.size(); i++){
        pt[i] = toupper(pt[i]);
        key[i] = toupper(key[i]);
        ct += mod(((pt[i]-'A')+(key[i]-'A')),26) + 'A';
    }
}

void decrypt(string &pt, string ct, string key){
    pt="";
    keyBaru(ct,key);
    for(int i = 0; i<ct.size(); i++){
        ct[i] = toupper(ct[i]);
        key[i] = toupper(key[i]);
        pt += mod(((ct[i]-'A')-(key[i]-'A')),26) + 'A';
    }
}

int main(){
    string pt, ct, key;
    int pilihan;
    char ulang;
    do{
        cout << "------------------------------\n";
        cout << "Program Vigenere Cipher\n";
        cout << "------------------------------\n";
        cout << "1. Enkripsi\n2. Deskripsi\n";
        cout << "------------------------------\n";
        cout << "pilihan: ";
        cin >> pilihan;
        cout << "------------------------------\n";


        switch (pilihan)
        {
        case 1:
            cout << "1. Enkripsi\n";
            cout << "Masukkan plain teks:\n>> ";
            cin >> pt;
            cout << "Masukkan key:\n>> ";
            cin >> key;
            encrypt(pt,ct,key);
            cout << "Enkripsi: \nCipher teks :" << ct << endl;
            break;
        case 2:
            cout << "2. Deskripsi\n";
            cout << "Masukkan cipher teks:\n>> ";
            cin >> ct;
            cout << "Masukkan key:\n>> ";
            cin >> key;
            decrypt(pt,ct,key);
            cout << "Deskripsi: \nPlain teks :"<< pt << endl;
            break;
        default:
            cout << "input salah\n";
            break;
        }
        cout << "------------------------------\n";
        cout << "Mulai ulang program? (y/t) : ";
        cin >> ulang;
        if(ulang != 'Y' || ulang != 'y' || ulang != 't' || ulang != 'T');
    }while(ulang == 'Y' || ulang == 'y');
}