#include <cstdio>

const int MAX = 21;
long long table[MAX];

void init(){
    table[1] = 3;
    table[2] = 7;
    for(int i = 3; i < MAX; ++i){
        table[i] = 2 * table[i - 1] + table[i - 2];
    }
}

int main(){
    init();
    int C, n;
    scanf("%d", &C);
    while(C-- > 0){
        scanf("%d", &n);
        printf("%lld\n", table[n]);
    }
    return 0;
}
