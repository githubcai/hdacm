#include <cstdio>
#include <cstring>

const int MAX = 21;
long long table[MAX][MAX];

void init(){
    memset(table, 0, sizeof(table));
    for(int i = 1; i < MAX; ++i){
        table[i][0] = 1;
    }
    table[1][1] = 1;
    for(int i = 2; i < MAX; ++i){
        for(int j = 1; j < MAX; ++j){
            if(i < j) break;
            table[i][j] = table[i - 1][j] + table[i][j - 1];
        }
    }
}

int main(){
    init();
    int n, m;
    while(scanf("%d%d", &m, &n) == 2){
        printf("%lld\n", table[m][n]);
    }
    return 0;
}
