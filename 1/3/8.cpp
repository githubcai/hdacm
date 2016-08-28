#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int T;
    cin >> T;
    while(T-- > 0){
        int N;
        vector<int> store;
        cin >> N;
        for(int i = 0; i < N; ++i){
            int tmp;
            cin >> tmp;
            store.push_back(tmp);
        }
        sort(store.begin(), store.end());

        cout << store[0];
        for(auto iter = store.begin() + 1; iter != store.end(); ++iter){
            cout << " " << *iter;
        }
        cout << endl;
    }
    return 0;
}
