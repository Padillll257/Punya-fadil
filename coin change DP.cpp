#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;

    vector<int> koin(N);

    for(int i = 0; i < N; i++){
        cin >> koin[i];
    }

    int K;
    cin >> K;

    const int unlimited = 1e9;

    vector<int> jumlah( K + 1 , unlimited);
    jumlah[0] = 0;

    for(int i = 1; i <= K; i++){
        for( int x : koin ){
            if( i - x >= 0 ){
                jumlah[i] = min(jumlah[i] , jumlah[i-x] + 1);
            }
        }
    }

    if(jumlah[K] == unlimited){
        cout << -1;
        return 0;
    }
    else{
        cout << jumlah[K];
    }
}
