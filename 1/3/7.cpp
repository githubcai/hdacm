#include <iostream>
#include <map>

using namespace std;

int main(){
    int num;
    while(cin >> num){
        int tnum, mark;
        multimap<int, int, greater<int>> store;
        while(cin >> tnum >> mark){
            if(tnum == 0 && mark == 0) break;
            store.insert(pair<int, int>(mark, tnum));
        }

        int count = 0, rank = 0, pre = -1;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            count++;
            if(pre != iter->first){
                pre = iter->first;
                rank = count;
            }
            if(iter->second == num){
                break;
            }
        }
        cout << rank << endl;
    }
    return 0;
}
