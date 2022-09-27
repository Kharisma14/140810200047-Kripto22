/*
Nama    : Kharisma Fitri Nurunnisa Siahaan
NPM     : 140810200047
Kelas   : A
Program : Hill Cipher
*/

#include <iostream>
#include <vector>
#include<bits/stdc++.h>


using namespace std;

//untuk matriks
void inputMatriks(int n, vector<vector<int> > &a){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
}
//mod 26
int mod26(int x){
    return x >= 0 ? (x%26) : 26-(abs(x)%26) ; 
}

//modulo invers
int modInverse(int det, int m){
    det=det%m; 
    for(int x=-det;x<m;x++) 
       if((det*x)%m==1) 
          return x;
}

//mendapatkan kofaktor
void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0,j=0; 
    for(int row=0;row<n;row++){ 
        for(int col=0;col<n;col++){ 
            if(row!=p&&col!=q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}

//mencari determinan
int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
}

//mencari adjoint
void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){ 
        for(int j=0;j<N;j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
}

//invers matriks
bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){ 
    int det = determinant(a, N, N);
    if(det == 0){ 
        cout << "Inverse does not exist"; 
        return false; 
    }
    int invDet = modInverse(det,26);
    if(invDet == -1){ 
        cout << "Inverse does not exist"; 
        return false; 
    }
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);  
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++) 
            inv[i][j] = mod26((adj[i][j]*invDet)); 
    return true; 
}

//enkripsi
void encrypt(int n, vector<vector<int> > &a){
    string plaintext;
    cout<<"plaintext : ";
    cin>> plaintext;
    int temp = (n-plaintext.size()%n)%n;
    for(int i=0; i<temp; i++){
        plaintext+='x';
    }
    int k=0;
    string ans="";
    while(k<plaintext.size()){
        for(int i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(int j=0;j<n;j++){
                sum += mod26(mod26(a[i][j])*mod26(plaintext[temp++]-'a'));
                sum = mod26(sum);
            }
            ans+=(sum+'a');
        }
        k+=n;
    }
    cout << "ciphertext : " << ans << endl;
}

//deskripsi
void decrypt(int n, vector<vector<int> > a, vector<vector<int> > inv){
    cout<<"ciphertext :";
    string s;
    cin>>s;
    int k = 0;
    string ans;
    while(k<s.size()){
        for(int i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(int j=0;j<n;j++){
                sum += mod26(mod26(inv[i][j] + 26)*mod26(s[temp++]-'a'));
                sum = mod26(sum);
            }
            ans+=(sum+'a');
        }
        k+=n;
    }
    cout << "plaintext : " << ans << endl;
}

//mencari kunci
void cariKeyMatrix(int n, vector<vector<int> > &key, vector<vector<int> > &inv){
    vector<vector<int> > pt(n, vector<int>(n));
    vector<vector<int> > ct(n, vector<int>(n));
    string plaintext, ciphertext;
    cout << "Masukkan plaintext :"; cin >> plaintext;
    cout << "Masukkan ciphertext :"; cin >> ciphertext;
    int jml = n*n;
    int temp = (jml-plaintext.size()%n)%n;
    for(int i=0; i<temp; i++){
        plaintext+='x';
    }
    temp = (jml-ciphertext.size()%n)%n;
    for(int i=0; i<temp; i++){
        ciphertext+='x';
    }
    temp = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            pt[j][i] = plaintext[temp]-'a';
            ct[j][i] = ciphertext[temp]-'a';
            temp++;
        }
    }
    if(inverse(pt,inv,n)){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                for(int k = 0; k < n; ++k){
                    key[i][j] += ct[i][k] * inv[k][j];
                    key[i][j] = mod26(key[i][j]);
                }
            }  
        }
    }
    cout << "matriks kunci = \n";
    for(int i = 0; i< n; i++){
        for(int j = 0; j< n; j++){
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
}


int main(){
    int n;
    int pilihan;
    
    do{
        cout << "------------------\nMenu :\n1. Enkripsi\n2. Deskripsi\n3. Cari Key\n0. Exit\n";
        cout << "------------------\nMasukkan ukuran matriks kunci : ";
        cin >> n;
        cout << "------------------\nMasukkan pilihan :";
        cin >> pilihan;
        vector<vector<int> > a(n, vector<int>(n));
        vector<vector<int> > adj(n, vector<int>(n));
        vector<vector<int> > inv(n, vector<int>(n));
        switch (pilihan){
        case 1:
            cout << "masukkan matriks kunci : \n";
            inputMatriks(n, a);
            if(!inverse(a,inv,n)){
                break;
            }
            cout << "Enkripsi:\n";
            encrypt(n,a);
            break;
        case 2:
            cout << "masukkan matriks kunci : \n";
            inputMatriks(n, a);
            if(!inverse(a,inv,n)){
                break;
            }
            cout << "Deskripsi:\n";
            decrypt(n,a,inv);
            break;
        case 3:
            cariKeyMatrix(n,a,inv);
            break;
        case 0:
            cout << "exit program";
            break;
        default:
            cout << "input salah\n";
            break;
        }
    }while(pilihan != 0);
}