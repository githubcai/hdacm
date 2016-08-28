#include <iostream>
#include <map>

using namespace std;

int main(){
    int v, n, pi, mi;
    while(cin >> v, v != 0){
        cin >> n;

        map<int, int, greater<int>> store;
        for(int i = 0; i < n; ++i){
            cin >> pi >> mi;
            store[pi] += mi;
        }

        int sum = 0;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            if(v > iter->second){
                v -= iter->second;
                sum += iter->second * iter->first;
            }else{
                sum += v * iter->first;
                break;
            }
        }
        cout << sum << endl;
    }
    return 0;
}
