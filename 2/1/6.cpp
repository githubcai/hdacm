#include <iostream>
#include <array>

using namespace std;

const int MAX = 500001;

array<int, MAX> table;

void init(){
    table.fill(1);
    for(int i = 2; i < MAX; ++i){
        for(int j = i * 2; j < MAX; j += i){
            table[j] += i;
        }
    }
}

int main(){
    init();
    
    int T, N;
    cin >> T;
    while(T--){
        cin >> N;
        cout << table[N] << endl;
    }
    return 0;
}
