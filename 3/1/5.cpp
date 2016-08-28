#include <cstdio>

const int MAX = 31;
long long table[MAX];

void init(){
    table[1] = 1;
    table[2] = 3;
    for(int i = 3; i < MAX; ++i){
        table[i] = table[i - 1] + 2 * table[i - 2];
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
