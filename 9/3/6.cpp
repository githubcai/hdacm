#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 100, INF = 0x4fffffff;
int maze[MAX][MAX], dist[MAX], height[MAX], tHeight[MAX], verNum;
bool used[MAX];

void Dijkstra(int v, int left, int right){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < verNum; ++i){
        if(tHeight[i] >= left && tHeight[i] <= right){
            dist[i] = maze[v][i];
        }else{
            used[i] = true;
            dist[i] = INF;
        }
    }
    used[v] = true;
    for(int i = 1; i < verNum; ++i){
        int tMin = INF, mark = 0;
        for(int j = 0; j < verNum; ++j){
            if(dist[j] < tMin && !used[j]){
                tMin = dist[j];
                mark = j;
            }
        }
        used[mark] = true;
        for(int j = 0; j < verNum; ++j){
            if(!used[j] && dist[j] > dist[mark] + maze[mark][j]){
                dist[j] = dist[mark] + maze[mark][j];
            }
        }
    }
}

int main(){
    int T, m; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &verNum, &m);
        for(int i = 0; i < verNum; ++i){
            scanf("%d", &height[i]);
        }
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        for(int i = 0; i < m; ++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if(maze[a - 1][b - 1] > c){
                maze[a - 1][b - 1] = maze[b - 1][a - 1] = c;
            }
        }
        int startH = height[0], endH = height[verNum - 1];
        memcpy(tHeight, height, sizeof(height));
        sort(height, height + verNum);
        int mDis = INF, path = INF;
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                if(startH < height[i] || startH > height[j]) continue;
                if(endH < height[i] || endH > height[j]) continue;
                if(height[j] - height[i] > mDis) break;
                Dijkstra(0, height[i], height[j]);
                if(height[j] - height[i] == mDis && dist[verNum - 1] != INF){
                    if(path > dist[verNum - 1]) path = dist[verNum - 1];
                }
                if(height[j] - height[i] < mDis && dist[verNum - 1] != INF){
                    path = dist[verNum - 1];
                    mDis = height[j] - height[i];
                }
            }
        }
        if(verNum == 1){
            printf("0 0\n");
        }else{
            printf("%d %d\n", mDis, path);
        }
    }
    return 0;
}
