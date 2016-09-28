#include <cstdio>
#include <cstring>

struct Node{
    int x, y;
};

const int INF = 0x7fffff, MAX = 100;
int maze[MAX][MAX], dist[MAX], verNum, num[MAX][MAX], preNode[MAX];
bool used[MAX], visEdge[MAX][MAX][MAX];
Node saveEdge[3000];

void Dijkstra(int v, bool isFirst){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < verNum; ++i){
        dist[i] = maze[v][i];
        preNode[i] = v;
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
        if(isFirst) visEdge[v][preNode[mark]][mark] = visEdge[v][mark][preNode[mark]] = true;
        for(int j = 0; j < verNum; ++j){
            if(!used[j] && dist[j] > dist[mark] + maze[mark][j]){
                dist[j] = dist[mark] + maze[mark][j];
                preNode[j] = mark;
            }
        }
    }
}


int main(){
     int M, sum[MAX], totalSum;
     while(scanf("%d%d", &verNum, &M) == 2){
        memset(maze, 0, sizeof(maze));
        memset(num, 0, sizeof(num));
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        for(int i = 0; i < M; ++i){
            int a, b; scanf("%d%d", &a, &b);
            maze[a - 1][b - 1] = maze[b - 1][a - 1] = 1;
            ++num[a - 1][b - 1], ++num[b - 1][a - 1];
            saveEdge[i].x = a - 1, saveEdge[i].y = b - 1;
        }
        bool result = true;
        memset(sum, 0, sizeof(sum));
        memset(visEdge, 0, sizeof(visEdge));
        totalSum = 0;
        for(int i = 0; i < verNum && result; ++i){
            Dijkstra(i, true);
            for(int j = 0; j < verNum && result; ++j){
                if(dist[j] == INF){
                    result = false;
                    break;
                }
                sum[i] += dist[j];
            }
            totalSum += sum[i];
        }
        for(int i = 0; i < M; ++i){
            if(!result){
                printf("INF\n");
            }else{
                if(num[saveEdge[i].x][saveEdge[i].y] > 1){
                    printf("%d\n", totalSum);
                    continue;
                }
                int sumResult = totalSum;
                bool tempResult = true;
                for(int j = 0; j < verNum && tempResult; ++j){
                    if(visEdge[j][saveEdge[i].x][saveEdge[i].y]){
                        maze[saveEdge[i].x][saveEdge[i].y] = maze[saveEdge[i].y][saveEdge[i].x] = INF;
                        Dijkstra(j, false);
                        int sumTemp = 0;
                        for(int k = 0; k < verNum && tempResult; ++k){
                            if(dist[k] == INF){
                                tempResult = false;
                                break;
                            }
                            sumTemp += dist[k];
                        }
                        sumResult = sumResult - sum[j] + sumTemp;
                        maze[saveEdge[i].x][saveEdge[i].y] = maze[saveEdge[i].y][saveEdge[i].x] = 1;
                    }
                }
                if(tempResult){
                    printf("%d\n", sumResult);
                }else{
                    printf("INF\n");
                }
            }
        }
     }
     return 0;
}
