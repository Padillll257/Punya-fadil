#include <bits/stdc++.h>
using namespace std;

int main(){
    int X , Y;

    cout << "Algoritma untuk Menghitung Luas Persegi Panjang. \n";
    cout << "Pertama, kita memerlukan Input, Yaitu X sebagai Panjang dan Y sebagai Lebar. \n";
    cout << "Masukkan Nilai X dan Y (Misal 2 3) : \n";

    cin >> X >> Y;

    cout << "Setelah itu, kita akan memprogram komputer untuk menghitung luasnya dengan rumus P * L atau dalam hal ini X * Y. \n";
    cout << "\n";
    cout <<  "Apakah anda ingin melihat hasilnyaa???. \n Ketik Iya jika mau :) \n Ketik Tidak jika nggak :( \n";

    string Jawaban;

    while(Jawaban != "Iya" || Jawaban != "iya" || Jawaban != "IYA"){
    cin >> Jawaban;
        if(Jawaban == "Iya" || Jawaban == "iya" ){
        cout << "Hasilnya adalahhh!!! : " << X * Y << "\n" << "SELAMAATT!! , Kita sudah belajar algoritma menghitung luas persegiii!!!";
        break;
    }
    else if(Jawaban == "Tidak" || Jawaban == "tidak" ){
        cout << "Yaahhhh kok gak mauuu :( \n" << "Aku tanya sekali lagi nihh \n" << "Jawab Iya YAAAA!!";
    }
    }
}