#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

struct Node{
    int v, length;
};

const int MAX = 50, INF = 0x7fffff;
int verNum, dist[MAX][2], cnt[MAX][2];
bool vis[MAX][2];
vector<Node> maze[MAX];

void init(){
    for(int i = 0; i < MAX; ++i){
        maze[i].clear();
    }
}

void Dijkstra(int s){
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < verNum; ++i){
        dist[i][0] = dist[i][1] = INF;
    }
    dist[s][0] = 0;
    cnt[s][0] = 1;
    for(int i = 0; i < 2 * verNum; ++i){
        int tMin = INF, mark = -1, k;
        for(int j = 0; j < verNum; ++j){
            if(!vis[j][0] && dist[j][0] < tMin){
                k = 0;
                tMin = dist[j][0];
                mark = j;
            }else if(!vis[j][1] && dist[j][1] < tMin){
                k = 1;
                tMin = dist[j][1];
                mark = j;
            }
        }
        if(mark == -1) break;
        vis[mark][k] = true;
        for(auto iter = maze[mark].begin(); iter != maze[mark].end(); ++iter){
            int newDis = dist[mark][k] + iter->length, v = iter->v;
            if(newDis < dist[v][0]){
                dist[v][1] = dist[v][0];
                cnt[v][1] = cnt[v][0];
                dist[v][0] = newDis;
                cnt[v][0] = cnt[mark][k];
            }else if(newDis == dist[v][0]){
                cnt[v][0] += cnt[mark][k];
            }else if(newDis < dist[v][1]){
                dist[v][1] = newDis;
                cnt[v][1] = cnt[mark][k];
            }else if(newDis == dist[v][1]){
                cnt[v][1] += cnt[mark][k];
            }
        }
    }
}

int main(){
    int M, S, E;
    while(scanf("%d%d%d%d", &verNum, &M, &S, &E) == 4){
        init();
        for(int i = 0; i < M; ++i){
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            Node node = {y, w};
            maze[x].push_back(node);
        }
        Dijkstra(S);
        printf("%d %d\n", dist[E][1], cnt[E][1]);
    }
    return 0;
}
