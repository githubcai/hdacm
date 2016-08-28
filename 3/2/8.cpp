#include <cstdio>
#include <cstring>

const int NMAX = 21, MMAX = 1001;
int map[NMAX][MMAX];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int C;
    scanf("%d", &C);
    while(C-- > 0){
        int n, m;
        scanf("%d%d", &n, &m);
        map[0][1] = map[1][0] = 0;
        for(int i = 2; i <= m; ++i) map[0][i] = -101;
        for(int i = 2; i <= n; ++i) map[i][0] = -101;
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j){
                scanf("%d", &map[i][j]);
            }
        }
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j){
                int temp = max(map[i][j - 1], map[i - 1][j]);
                for(int k = 1; k < j - 1; ++k){
                    if(j % k == 0 && temp < map[i][k]) temp = map[i][k];
                }
                map[i][j] = temp + map[i][j];
            }
        }
        printf("%d\n", map[n][m]);
    }
    return 0;
}
