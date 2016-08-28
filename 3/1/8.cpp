#include <cstdio>
#include <cstring>

const int LMAX = 1000001, MMAX = 31;
char table[LMAX][MMAX];

void init(){
    int temp[5] = {0, 2, 4, 6, 9};
    for(int i = 1; i < 5; ++i){
        for(int j = 1; j < MMAX; ++j){
            table[i][j] = temp[i] % j;
        }
    }

    for(int i = 1; i < MMAX; ++i){
        for(int j = 5; j < LMAX; ++j){
            table[j][i] = (table[j - 1][i] + table[j - 3][i] + table[j - 4][i]) % i;
        }
    }
}

int main(){
    init();
    int L, M;
    while(scanf("%d%d", &L, &M) == 2){
        printf("%d\n", table[L][M]);
    }
    return 0;
}
