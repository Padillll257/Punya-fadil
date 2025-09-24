#include <bits/stdc++.h>
using namespace std;

int main(){

    string nama;
    string password;
    string jawaban;
    string norek;
    string pass;
    int narik;

    cout << "HALLOO GUYSSS, Kali ini kita akan belajar algoritma untuk menarik uang dari ATM \n APAKAH KALIAN SIAPP??";

    while(jawaban != "IYA" || jawaban != "iya"){
        cin >> jawaban;

        if( jawaban == "IYA" || jawaban == "iya"){
            cout << "Okee kita lanjut yaa!!\n";
            break;
        }
        else{
        cout << "Kok gk mauuu??? :( \n Jawab iya yaaaa";

        }
    }

    cout << "==Pertama : Buat nama rekening dan password kalian==\n";
    cout << "==Masukkan Nama Rekening kalian :\n ";
    cin >> nama;

    cout <<"==Masukkan Password Rekening kalian : \n";
    cin >> password;

    cout << "==Setelah itu, kita masuk ke akun rekening yang telah kita buat\n Masukkan nama rekening kalian : ";

    int percobaan = 3;

while(norek != nama){
    cin >> norek;
    if(norek == nama){
        cout << "==Silahkan masukkan password :\n";
        break;
    }
    else{
        cout << "Maaf username anda salah, tolong masukkan ulang";
    }
}

while(pass != password){
    cin >> pass;
    if(pass == password){
        cout <<"Masukkan nominal yang kalian ingin ambil : \n";

        cout << "Masukkan angka berikut sesuai pilihan atau nominal yang ingin kalian ambil :\n 1. 50.000\n2. 100.000\n 3. 150.000";
while(narik != 1 || narik != 2 || narik != 3 || narik < 1000){
cin >> narik;
if(narik == 1){
    cout << "Silahkan mengambil tunai anda sejumlah Rp 50.000";
    break;
}
else if(narik == 2){
    cout << "Silahkan mengambil tunai anda sejumlah Rp 100.000";
    break;
}
else if(narik == 3){
    cout << "Silahkan mengambil tunai anda sejumlah Rp 150.000";
    break;
}
else if(narik < 1000){
    cout << "Tolong masukkan angka 1 atau 2 atau 3 atau masukkan nilai minimal Rp 1000";
}
else{
    cout << "Silahkan mengambil tunai anda sejumlah Rp " << narik;
    break;
}
}

    }
    else{
        cout <<"Maaf password anda salah, tolong masukkan ulang \n Sisa kesempatan :" << percobaan-1 << " ";

        percobaan--;
        if(percobaan == 0){
            cout << "Maaf, akun anda telah diblokir";
            break;
        }
    }
}
}