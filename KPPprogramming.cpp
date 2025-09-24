#include <bits/stdc++.h>
using namespace std;

struct hubungan {
    string tujuan;
    int berat;
};

int jam; 

vector<string> pathfinder(unordered_map<string , vector<hubungan>> &graf , string start, string target) {
    const int unlimited = 1e9;  
    unordered_map<string , int > jarak;
    unordered_map<string , string > hubungannode;


    for (auto &x : graf) {
        jarak[x.first] = unlimited;
        for (auto& y : x.second) {
            jarak[y.tujuan] = unlimited; 
        }
    }

    jarak[start] = 0;

    using P = pair<int , string>;
    priority_queue<P , vector<P> , greater<P>> antriancek;

    antriancek.push({0, start});

    while (!antriancek.empty()) {
        auto [meter , node] = antriancek.top();
        antriancek.pop();

        if (meter > jarak[node]) continue;

        for (auto& hub : graf[node]) {
            string x = hub.tujuan;
            int weight = hub.berat;

            if (jarak[node] + weight < jarak[x]) {
                jarak[x] = jarak[node] + weight;
                hubungannode[x] = node;
                antriancek.push({jarak[x] , x});
            }
        }
    }

    if (jarak[target] == unlimited) return {};

    vector<string> jalan;
    for (string x = target; x != ""; x = hubungannode.count(x) ? hubungannode[x] : "") {
        jalan.push_back(x);
        if (x == start) break;
    }
    reverse(jalan.begin(), jalan.end()); 

    return jalan;
}

int main() {

        /* Disini saya memiliki beberapa catatan : 
    1. Untuk sistem Electric dan Mech saya abaikan dikarenakan tidak adanya penjelasan dari keguaan nodenya di aturan 
    2. Untuk sistem waktu, nilai minimal dan rest, saya menemukan bahwa apabila kita menggunakan asumsi jikalau rest nya ini dummy maka nilainya terlalu jauh dari 
    di output, maka saya mengasumsikan bahwa rest ini pasti rest nya menambahkan beberapa menit secara tetap dan setelah melalui trial dan error menggunakan hitung
    manual dengan menganggap bahwa setelah dia memasuki node C maka dia mengalami penambahan waktu sebanyak x. Untuk mencari x nya kita perlu asumsi bahwa kita mulai dari
    jam y:00 ( misal input 1 artinya jam 1:00) lalu dari sini kita bisa melakukan beberapa asumsi misal nilai x nya segini hingga di node ini dia jadi negatif lagi dan kembali
    kali 1.3 .  Disini saya menemukan bahwa setelah melewati node C dia tidak langsung berganti jam tapi sempat lewat dulu sekali (+2 menit) lalu ke genap ( yang apabila
    di lakukan dengan kalkulasi sesuai aturan dan asumsi yaitu (200 + 150) * 1.3 + (100+200 + 250) * 0.8 maka menghasilkan nilai terdekat yaitu 895) dan pada saat di node 
    selanjutnya sudah genap ( jam 2:00) maka apabila saat di node C sudah mencapai menit ke 5 maka kita bisa mengasumsikan kalau dia menambah selama 54 menit ( 2:00 - 0:04 - 0:02)
    tapi disini dikatakan bahwa saat dia sampai di node selanjutnya sudah menit ke 6 (menggunakan asumsi poin ke 3) maka cukup gampang kita sisa menambah 6 menit sehingga
    dia beristirahat selama 60 menit tepat (sebenarnya ada opsi yang lebih tepat tapi akan bentrok dengan sistem waktu nya maka opsi yang mengeluarkan energi paling kecil +
    paling sesuai kode + tidak bentrok dengan sistem waktunya adalah opsi ini)
    3. Disini saya mengasumsikan output menit adalah menit yang merujuk di belakang jam nya, jadi ketika dia jam 2:06 misalnya dia sampai di menit ke 6 */

    int N , M;
    cin >> N >> M;

    unordered_map<string , vector<hubungan>> graf;

    for (int i = 0; i < M; i++) {
        string u , v;
        int  w ,o;
        cin >> u >> v >> w >> o;
        int total = w + o;
        graf[u].push_back({ v , total});
        graf[v].push_back({u , total});
    }

    string start , target;
    cin >> start >> target;

    string istirahat;
    getline(cin , istirahat);
    string Mech , Electric ;
    getline(cin , Mech);
    getline(cin , Electric);

    cin >> jam;


    unordered_set<string> istirahatNode;
    stringstream nodetambahan(istirahat + " " + Mech + " " + Electric);
    string tmp;
    while (nodetambahan >> tmp) {
        istirahatNode.insert(tmp);
    }

    vector<string> jalan = pathfinder(graf , start , target);

    int energiAwal = 1000;
    int energi = energiAwal;
    int totalMenit = jam * 60;
    int totalenergi = 0;

    if (jalan.empty()) {
        cout << "Robot gagal dalam mencapai tujuan :(";
        return 0;
    }

    for (int i = 0; i + 1 < jalan.size(); i++) {
        string u = jalan[i], v = jalan[i+1];
        for (auto& hub : graf[u]) {
            if (hub.tujuan == v) {

                int jamSekarang = (totalMenit / 60) % 24;



                double faktor = (jamSekarang % 2 == 0 ? 0.8 : 1.3);
                int biaya = ceil(hub.berat * faktor);

                energi -= biaya;
                totalenergi += biaya;

                if (energi <= 0) {
                    cout << "Robot gagal dalam mencapai tujuan :(\n";
                    return 0;
                }

                totalMenit += 2;

                if (istirahatNode.count(v)) {
                    totalMenit += 60;
                }

                break;
            }
        }
    }

    cout << "Total energi minimum : " << totalenergi <<"\n";

    cout << "Jalur \n";
    for (auto& node : jalan) {
        cout << node << "->";
    }
    cout << "END\n";

    int waktu = 0;
    for(auto& node : jalan){
        cout <<  node <<"(menit "<< waktu <<")" << "\n";
        waktu += 2;
    }
}
