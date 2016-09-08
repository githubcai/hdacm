#include <queue>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(){
    int t, cnt = 1;
    while(cin >> t && t != 0){
        cout << "Scenario #" << cnt++ << endl;
        map<int, int> store;
        for(int i = 0; i < t; ++i){
            int temp; cin >> temp;
            for(int j = 0; j < temp; ++j){
                int k; cin >> k;
                store[k] = i;
            }
        }
        string input;
        queue<int> qTeam[1001], que;
        bool vis[1001] = {0};
        while(true){
            cin >> input;
            if(input == "ENQUEUE"){
                int temp; cin >> temp;
                if(!vis[store[temp]]){
                    que.push(store[temp]);
                    vis[store[temp]] = true;
                }
                qTeam[store[temp]].push(temp);
            }else if(input == "DEQUEUE"){
                int temp = que.front();
                cout << qTeam[temp].front() << endl;;
                qTeam[temp].pop();
                if(qTeam[temp].empty()){
                    vis[temp] = false;
                    que.pop();
                }
            }else{
                break;
            }
        }
        cout << endl;
    }
    return 0;
}
