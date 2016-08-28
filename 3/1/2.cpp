#include <cstdio>

const int MAX = 49;
long long table[MAX];

void init(){
    table[1] = 1;
    table[2] = 2;
    for(int i = 3; i < MAX; ++i){
        table[i] = table[i - 1] + table[i - 2];
    }
}

int main(){
    init();
    int N, a, b;
    scanf("%d", &N);
    while(N-- > 0){
        scanf("%d%d", &a, &b);
        printf("%lld\n", table[b - a]);
    }
    return 0;
}
