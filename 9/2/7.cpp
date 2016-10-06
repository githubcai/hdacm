#include <cstdio>
#include <cstring>

const int MAX = 300, INF = 1e9;
int maze[MAX][MAX], dp[MAX][MAX], N, M;

void init(){
    memset(maze, 0, sizeof(maze));
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < N; ++i){
        dp[i][i] = 1;
        for(int j = i + 1; j < N; ++j){
            maze[i][j] = maze[j][i] = INF;
        }
    }
}

int max(int a, int b){
    return a > b ? a : b;
}

void floyd(){
    for(int k = 0; k < N; ++k){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                if(maze[i][j] > maze[i][k] + maze[k][j]){
                    maze[i][j] = maze[i][k] + maze[k][j];
                    dp[i][j] = dp[i][k] + dp[k][j] - 1;
                }else if(maze[i][j] == maze[i][k] + maze[k][j]){
                    dp[i][j] = max(dp[i][k] + dp[k][j] - 1, dp[i][j]);
                }
            }
        }
    }
}

int main(){
    while(scanf("%d%d", &N, &M) == 2){
        if(N == 0 && M == 0) break;
        init();
        for(int i = 0; i < M; ++i){
            int x, y, v;
            scanf("%d%d%d", &x, &y, &v);
            if(maze[x - 1][y - 1] > v){
                maze[x - 1][y - 1] = maze[y - 1][x - 1] = v;
                dp[x - 1][y - 1] = dp[y - 1][x - 1] = 2;
            }
        }
        int s1, e1, s2, e2;
        scanf("%d%d%d%d", &s1, &e1, &s2, &e2);
        --s1, --s2, --e1, --e2;
        floyd();
        int res = 0;
        if(maze[s1][e1] != INF && maze[s2][e2] != INF){
            for(int i = 0; i < N; ++i){
                for(int j = 0; j < N; ++j){
                    if(dp[i][j] > res && maze[s1][i] + maze[i][j] + maze[j][e1] == maze[s1][e1] &&
                        maze[s2][i] + maze[i][j] + maze[j][e2] == maze[s2][e2]){
                        res = dp[i][j];
                    }
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
