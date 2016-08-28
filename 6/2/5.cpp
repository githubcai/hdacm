#include <cstdio>
#include <cstring>

const int MAX = 441, INF = 0x7fffff;
int maze[MAX][MAX], dist[MAX], verNum, table[10];
bool used[MAX];

void Dijkstra(int v){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < verNum; ++i){
        dist[i] = maze[v][i];
    }
    used[v] = true;
    for(int i = 1; i < verNum; ++i){
        int tMin = INF, mark;
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
    for(int i = 1; i < 10; ++i){
        table[i] = 2520 / i;
    }
    int ver, hor;
    while(scanf("%d%d", &ver, &hor) == 2 && !(ver == 0 && hor == 0)){
        verNum = (ver + 1) * (hor + 1);
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        int limit = 2 * ver + 1;
        for(int i = 0; i < limit; ++i){
            if(i % 2 == 0){
                for(int j = 0; j < hor; ++j){
                    int start, end;
                    start = (i / 2) * (hor + 1) + j;
                    end = start + 1;
                    int speed;
                    char mark;
                    scanf("%d %c", &speed, &mark);
                    if(speed == 0) continue;
                    switch(mark){
                        case '*':{
                            maze[start][end] = maze[end][start] = table[speed];
                            break;
                        }
                        case '<':{
                            maze[end][start] = table[speed];
                            break;
                        }
                        case '>':{
                            maze[start][end] = table[speed];
                            break;
                        }
                        default:{
                            printf("<1>input error\n");
                            return 0;
                        }
                    }
                }
            }else{
                for(int j = 0; j <= hor; ++j){
                    int start, end;
                    start = (i / 2) * (hor + 1) + j;
                    end = start + hor + 1;
                    int speed;
                    char mark;
                    scanf("%d %c", &speed, &mark);
                    if(speed == 0) continue;
                    switch(mark){
                        case '*':{
                            maze[start][end] = maze[end][start] = table[speed];
                            break;
                        }
                        case 'v':{
                            maze[start][end] = table[speed];
                            break;
                        }
                        case '^':{
                            maze[end][start] = table[speed];
                            break;
                        }
                        default:{
                            printf("<2>input error\n");
                            return 0;
                        }
                    }
                }
            }
        }
        Dijkstra(0);
        if(dist[verNum - 1] == INF){
            printf("Holiday\n");
        }else{
            printf("%d blips\n", dist[verNum - 1]);
        }
    }
    return 0;
}
