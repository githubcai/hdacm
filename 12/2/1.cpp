#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef long long LL;
const int MAX = 1000007;
int ctoi[128];
struct Node{
    char maze[25];
    LL zip(){
        LL res = 0;
        for(int i = 0; i < 24; ++i){
            res *= 6;
            res += ctoi[maze[i]];
        }
        return res;
    }
};

Node s[2];
queue<Node> que[2];
LL vis[2][MAX];
bool flag = false;
int cvr[12][12] = {
    {4, 12, 13, 5, 6, 14, 0, 2, 11, 19, 20, 22},
    {12, 13, 5, 4, 0, 2, 19, 11, 22, 20, 6, 14},
    {8, 9, 17, 16, 7, 15, 1, 3, 10, 18, 21, 23},
    {9, 17, 16, 8, 1, 3, 18, 10, 23, 21, 7, 15},
    {6, 7, 15, 14, 2, 3, 8, 16, 20, 21, 5, 13},
    {7, 15, 14, 6, 8, 16, 21, 20, 5, 13, 3, 2},
    {10, 11, 19, 18, 0, 1, 12, 4, 23, 22, 9, 17},
    {11, 19, 18, 10, 12, 4, 23, 22, 9, 17, 0, 1},
    {0, 1, 3, 2, 4, 5, 6, 7, 8, 9, 10, 11},
    {1, 3, 2, 0, 10, 11, 4, 5, 6, 7, 8, 9},
    {20, 21, 23, 22, 14, 15, 16, 17, 18, 19, 12, 13},
    {21, 23, 22, 20, 16, 17, 18, 19, 12, 13, 14, 15}
};
/*
       0  1
       2  3
 4  5  6  7  8  9 10 11
12 13 14 15 16 17 18 19
      20 21
      22 23
*/

int Hash(LL sz, int x){
    int p = sz % MAX;
    while(true){
        if(vis[x][p] == -1) return p;
        if(vis[x][p] != -1 && vis[x][p] == sz) return p;
        ++p;
        if(p > MAX) p = 0;
    }
    return -1;
}

void bfs(int x){
    int size = que[x].size();
    char tmp[25];
    while(size-- > 0){
        Node u = que[x].front();
        que[x].pop();
        memcpy(tmp, u.maze, sizeof(u.maze));
        for(int i = 0; i < 12; ++i){
            Node v = u;
            for(int j = 0; j < 12; ++j){
                v.maze[cvr[i][j]] = tmp[cvr[i ^ 1][j]];
            }
            LL vz = v.zip();
            int px1 = Hash(vz, x), px2 = Hash(vz, x ^ 1);
            if(vis[x][px1] != -1) continue;
            if(vis[x ^ 1][px2] != -1){
                flag = true;
                return;
            }
            vis[x][px1] = vz;
            que[x].push(v);
        }
    }
}

int dbfs(){
    while(!que[0].empty()) que[0].pop();
    while(!que[1].empty()) que[1].pop();
    memset(vis, -1, sizeof(vis));
    que[0].push(s[0]); que[1].push(s[1]);
    LL sz0 = s[0].zip(), sz1 = s[1].zip();
    vis[0][Hash(sz0, 0)] = sz0;
    if(vis[0][Hash(sz1, 0)] != -1) return 0;
    vis[1][Hash(sz1, 1)] = sz1;
    flag = false;
    int cnt = 0;
    while(true){
        ++cnt;
        if(que[0].size() < que[1].size()){
            bfs(0);
        }else{
            bfs(1);
        }
        if(flag) break;
    }
    return cnt;
}

int main(){
    ctoi['G'] = 0; ctoi['W'] = 1; ctoi['Y'] = 2;
    ctoi['O'] = 3; ctoi['R'] = 4; ctoi['B'] = 5;
    int T; scanf("%d\n", &T);
    while(T-- > 0){
        for(int i = 0; i < 2; ++i){
            int cnt = 0; char c;
            for(int j = 0; j < 6; ++j){
                do{
                    scanf("%c", &c);
                    if(c != ' ' && c != '\n') s[i].maze[cnt++] = c;
                }while(c != '\n');
            }
         }
         printf("%d\n", dbfs());
    }
    return 0;
}
