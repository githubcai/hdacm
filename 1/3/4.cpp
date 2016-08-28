#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int C;
    cin >> C;
    while(C--){
        int n;
        cin >> n;
        
        vector<int> store;
        for(int i = 0; i < n; ++i){
            int tmp;
            cin >> tmp;
            store.push_back(tmp);
        }
        sort(store.begin(), store.end());
        cout << store[1] << endl;
    }
    return 0;
}
