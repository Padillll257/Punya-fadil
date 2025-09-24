#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "Algoritma Dan Simulasi Membuat Nasi Goreng\n\n";

    string nama;
    cout << "Sebutkan Nama mu :) : ";
    getline(cin, nama);

    cout << "\nHalo, " << nama << "! Mari kita masak nasi goreng.\n\n";

    cout << "Adapun Karena ini adalah algoritma, maka kita memerlukan input. Inputnya adalah bahan nasi gorenggg.\n";
    cout << "Adapun Bahan dasarnya adalah : Nasi putih, minyak, bawang merah dan putih, cabai dan garam serta kecap.\n";

    cout << "\n Kamu bisa memilih berbagai jenis bahan tambahan loohhh!!!! (ketik angkanya, bisa lebih dari satu):\n";
    cout << "1. Telur\n2. Ayam\n3. Sosis\n4. Seafood (udang & cumi)\n5. Tidak ada tambahan\n";
    cout << "Masukkan pilihan (misal: 1 3): ";

    vector<int> tambahan;
    int x;
    while (cin >> x) {
        if (x < 1 || x > 5) break;
        tambahan.push_back(x);
        if (cin.peek() == '\n') break;
    }

    cout << "\nLangkah atau Algoritma Memasak Nasi Goreng\n";
    cout << "1. Siapkan bahan dasar.\n";
    cout << "2. Haluskan bawang & cabai.\n";
    cout << "3. Panaskan minyak di wajan.\n";
    cout << "4. Tumis bumbu hingga harum.\n";

    if (!tambahan.empty()) {
        for (int p : tambahan) {
            switch (p) {
                case 1: cout << "5. Masukkan telur, orak-arik sebentar.\n"; break;
                case 2: cout << "5. Masukkan ayam, tumis hingga matang.\n"; break;
                case 3: cout << "5. Masukkan sosis, tumis hingga harum.\n"; break;
                case 4: cout << "5. Masukkan udang & cumi, masak hingga setengah matang.\n"; break;
                case 5: cout << "5. Tidak ada bahan tambahan, lanjutkan.\n"; break;
            }
        }
    }

    cout << "6. Masukkan nasi putih, aduk rata.\n";
    cout << "7. Tambahkan kecap manis, garam, dan penyedap sesuai selera.\n";
    cout << "8. Aduk hingga tercampur rata dan harum.\n";
    cout << "9. Sajikan di piring.\n";
    cout << "\n Adapun hasil atau outputnya adalahhh: Sepiring nasi goreng buatan " << nama << " Siap Dinikmatiii!!\n";

    return 0;
}
