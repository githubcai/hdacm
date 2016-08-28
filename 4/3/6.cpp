#include <cstdio>
#include <cmath>
#include <cstring>

const int MAX = 11;
int table[MAX], count, N;
bool vis[MAX][MAX];

void dfs(int row){
    if(row == N){
        ++count;
        return;
    }
    for(int i = 0; i < N; ++i){
        bool flag = true;
        for(int j = 0; j < row && flag; ++j){
            for(int k = 0; k < N && flag; ++k){
                if(vis[j][k] && (fabs(row - j) == fabs(i - k) || k == i)){
                    flag = false;
                }
            }
        }
        if(flag){
            vis[row][i] = true;
            dfs(row + 1);
            vis[row][i] = false;
        }
    }
}

void init(){
    for(int i = 1; i < MAX; ++i){
        memset(vis, 0, sizeof(0));
        count = 0, N = i;
        dfs(0);
        table[i] = count;
    }
}

int main(){
    init();
    while(scanf("%d", &N) == 1 && N != 0){
        printf("%d\n", table[N]);
    }
    return 0;
}
