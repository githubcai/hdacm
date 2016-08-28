#include <cstdio>

const int MAX = 51;
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
    int n;
    while(scanf("%d", &n) == 1){
        printf("%lld\n", table[n]);
    }
    return 0;
}
