#include <iostream>
#include <map>

using namespace std;

void print(int Ai, int Bi){
    for(int i = 0; i < Bi; ++i){
        cout << ">+";
        for(int j = 2; j < Ai; ++j){
            cout << "-";
        }
        cout << "+>" << endl;
    }
    cout << endl;
}

int main(){
    int t, N, Ai, Bi;
    map<int, int> store;
    cin >> t;
    while(t-- > 0){
        store.clear();
        cin >> N;
        for(int i =0; i < N; ++i){
            cin >> Ai >> Bi;
            store[Ai] = Bi;
        }
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            print(iter->first, iter->second);
        }
    }
    return 0;
}
