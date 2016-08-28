#include <cstdio>

int table[41] = {1, 1};

void init(){
    for(int i = 2; i <= 40; ++i){
        table[i] = table[i - 1] * i % 2009;
    }
}

int main(){
    init();
    
    unsigned N;
    while(scanf("%d", &N) == 1){
        if(N > 40){
            printf("0\n");
        }else{
            printf("%d\n", table[N]);
        }
    }
    return 0;
}
