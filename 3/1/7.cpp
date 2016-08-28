#include <cstdio>

const int MAX = 51;
long long table[MAX];

void init(){
    table[1] = 3;
    table[2] = 6;
    table[3] = 6;
    for(int i = 4; i < MAX; ++i){
        table[i] = table[i - 1] + 2 * table[i - 2];
    }
}

int main(){
    init();
    int n;
    while(scanf("%d", &n) == 1){
        printf("%lld\n", table[n]);
    }
    return 0;
}
