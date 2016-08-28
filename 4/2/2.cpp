#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node{
    int x, y, z, cost;
};

const int MAX = 50;
int maze[MAX][MAX][MAX], A, B, C, T;
int dir[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1}};
bool vis[MAX][MAX][MAX];

int bfs(){
    queue<Node> que;
    Node st = {0, 0, 0, 0};
    memset(vis, 0, sizeof(vis));
    que.push(st);
    vis[0][0][0] = true;
    while(!que.empty()){
        st = que.front();
        que.pop();
        if(st.x == A - 1 && st.y == B - 1 && st.z == C - 1){
            return st.cost;
        }
        for(int i = 0; i < 6; ++i){
            Node next;
            next.x = st.x + dir[i][0];
            next.y = st.y + dir[i][1];
            next.z = st.z + dir[i][2];
            if(next.x >= 0 && next.x < A &&
               next.y >= 0 && next.y < B &&
               next.z >= 0 && next.z < C &&
               !vis[next.x][next.y][next.z] &&
               maze[next.x][next.y][next.z] == 0 &&
               st.cost < T){
                next.cost = st.cost + 1; 
                vis[next.x][next.y][next.z] = true;
                que.push(next);
            }
        }
    }
    return -1;
}

int main(){
    int K;
    scanf("%d", &K);
    while(K-- > 0){
        scanf("%d%d%d%d", &A, &B, &C, &T);
        for(int i = 0; i < A; ++i){
            for(int j = 0; j < B; ++j){
                for(int k = 0; k < C; ++k){
                    scanf("%d", &maze[i][j][k]);
                }
            }
        }
        int cost = bfs();
        printf("%d\n", cost);
    }
    return 0;
}
