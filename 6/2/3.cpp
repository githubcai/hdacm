#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MAX = 30;
int verNum;
double maze[MAX][MAX], dist[MAX];
bool vis[MAX];

bool spfa(int s){
    queue<int> que;
    fill(dist, dist + verNum, 0);
    fill(vis, vis + verNum, false);
    que.push(s);
    dist[s] = 1;
    while(!que.empty()){
        int now = que.front();
        que.pop();
        vis[now] = false;
        for(int i = 0; i < verNum; ++i){
            if(maze[now][i] > 0){
                if(dist[i] < dist[now] * maze[now][i]){
                    dist[i] = dist[now] * maze[now][i];
                    if(!vis[i]){
                        vis[i] = true;
                        que.push(i);
                    }
                }
            }
            if(i == s && dist[i] > 1.0){
                return true;
            }
        }
    }
    return false;
}

int main(){
    int cnt;
    while(cin >> verNum && verNum != 0){
        ++cnt;
        for(int i = 0; i < verNum; ++i){
            for(int j = 0; j < verNum; ++j){
                maze[i][j] = -1;
            }
        }
        map<string, int> store;
        for(int i = 0; i < verNum; ++i){
            string curr;
            cin >> curr;
            store[curr] = i;
        }
        int m;
        cin >> m;
        for(int i = 0; i < m; ++i){
            string a, b;
            double rate;
            cin >> a >> rate >> b;
            maze[store[a]][store[b]] = rate;
        }
        if(spfa(0)){
            cout << "Case " << cnt << ": Yes" << endl;;
        }else{
            cout << "Case " << cnt << ": No" << endl;;
        }
    }
    return 0;
}
