#include <cstdio>

const int MAX = 55;
long long table[MAX];

void init(){
    table[1]= 1;
    table[2]= 2;
    table[3]= 3;
    table[4]= 4;
    for(int i = 5; i < MAX; ++i){
        table[i] = 2 * table[i - 1] - table[i - 2] + table[i - 3] - table[i - 4];
    }
}

int main(){
    init();
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        printf("%lld\n", table[n]);
    }
    return 0;
}
