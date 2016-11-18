#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef long long LL;
const int MOD = 500009;
const char dest[32] = {
    11, 12, 13, 14, 15, 16, 17, 0,
    21, 22, 23, 24, 25, 26, 27, 0,
    31, 32, 33, 34, 35, 36, 37, 0,
    41, 42, 43, 44, 45, 46, 47, 0
};
struct Node{
    char maze[32];
    int step, trans[4], flag[48];
};

char input[4][8];
LL vis[MOD];
int dStat;
Node now, nx;

LL zip(const char *maze){
    LL res = 0;
    for(int i = 0; i < 32; ++i){
        res = (res << 1) + maze[i];
    }
    return res;
}

int getHash(LL res){
    int p = res % MOD;
    while(true){
        if(vis[p] == -1) return p;
        if(vis[p] == res) return p;
        ++p;
        if(p >= MOD) p = 0;
    }
    return -1;
}

int bfs(){
    queue<Node> que;
    memset(vis, -1, sizeof(vis));
    LL res = zip(now.maze);
    int status = getHash(res);
    if(status == dStat) return 0;
    vis[status] = res;
    que.push(now);
    while(!que.empty()){
        now = que.front();
        que.pop();
        for(int i = 0; i < 4; ++i){
            int pre = now.trans[i] - 1;
            if(now.maze[pre] == 0 || now.maze[pre] % 10 == 7) continue;
            nx = now; ++nx.step;
            nx.trans[i] = now.flag[now.maze[pre] + 1];
            nx.maze[now.trans[i]] = now.maze[nx.trans[i]];
            nx.maze[nx.trans[i]] = 0;
            nx.flag[now.maze[nx.trans[i]]] = now.trans[i];
            res = zip(nx.maze);
            status = getHash(res);
            if(vis[status] != -1) continue;
            if(status == dStat) return nx.step;
            vis[status] = res;
            que.push(nx);
        }
    }
    return -1;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        memset(now.trans, -1, sizeof(now.trans));
        now.maze[0] = 11; now.maze[8] = 21; now.maze[16] = 31; now.maze[24] = 41;
        now.flag[11] = 0; now.flag[21] = 8; now.flag[31] = 16; now.flag[41] = 24;
        for(int i = 0; i < 4; ++i){
            for(int j = 1; j <= 7; ++j){
                int t; scanf("%d", &t);
                int temp = i * 8 + j;
                if(t == 11 || t == 21 || t == 31 || t == 41){
                    now.maze[temp] = 0;
                    now.trans[t / 10 - 1] = temp;
                }else{
                    now.maze[temp] = (char)t;
                    now.flag[t] = temp;
                }
            }
        }
        now.step = 0;
        dStat = zip(dest) % MOD;
        printf("%d\n", bfs());
    }
    return 0;
}
