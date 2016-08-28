#include <cstdio>
#include <cstring>

const int MAX = 36;
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
    int n, cnt = 0;
    while(scanf("%d", &n) == 1 && n != -1){
        ++cnt;
        printf("%d %d %lld\n", cnt, n, 2 * table[n][n]);
    }
    return 0;
}
