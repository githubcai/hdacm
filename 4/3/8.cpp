#include <cstdio>
#include <cstring>
#include <cmath>

const int MAX = 8;
bool conect[MAX][MAX] = {
    {false, true, true, true, false, false, false, false},
    {true, false, true, false, true, true, false, false},
    {true, true, false, true, true, true, true, false},
    {true, false, true, false, false, true, true, false},
    {false, true, true, false, false, true, false, true},
    {false, true, true, true, true, false, true, true},
    {false, false, true, true, false, true, false, true},
    {false, false, false, false, true, true, true, false},
};
int input[MAX], result[MAX], count;
bool vis[MAX + 1];

void dfs(int n){
    if(count >= 2) return;
    if(n == 8){
        ++count;
        memcpy(result, input, sizeof(input));
        return;
    }
    if(input[n] != 0){
        if(vis[input[n]]) return;
        for(int i = 0; i < MAX; ++i){
            if(i == n) continue;
            if(conect[n][i] && input[i] != 0 && fabs(input[n] - input[i]) == 1) return;
        }
        vis[input[n]] = true;
        dfs(n + 1);
        vis[input[n]] = false;
    }else{
        for(int i = 1; i <= MAX; ++i){
            if(!vis[i]){
                bool flag = true;
                for(int j = 0; j < MAX; ++j){
                    if(j == n) continue;
                    if(conect[n][j] && input[j] != 0 && fabs(i - input[j]) == 1){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    vis[i] = true;
                    input[n] = i;
                    dfs(n + 1);
                    input[n] = 0;
                    vis[i] = false;
                }
            }
        }
    }
}

int main(){
    int T, cnt = 0;
    scanf("%d", &T);
    while(T-- > 0){
        ++cnt;
        for(int i = 0; i < MAX; ++i){
            scanf("%d", &input[i]);
        }
        count = 0;
        memset(vis, 0, sizeof(vis));
        dfs(0);
        printf("Case %d:", cnt);
        if(count == 0){
            printf(" No answer\n");
        }else if(count == 1){
            for(int i = 0; i < MAX; ++i){
                printf(" %d", result[i]);
            }
            printf("\n");
        }else{
            printf(" Not unique\n");
        }
    }
}
