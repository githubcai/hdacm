#include <cstdio>

const int MAX = 41;
int table[MAX];

void init(){
    table[1] = 1;
    table[2] = 2;
    for(int i = 3; i < MAX; ++i){
        table[i] = table[i - 1] + table[i - 2];
    }
}

int main(){
    init();
    int N;
    scanf("%d", &N);
    while(N-- > 0){
        int M;
        scanf("%d", &M);
        printf("%d\n", table[M - 1]);
    }
    return 0;
}
