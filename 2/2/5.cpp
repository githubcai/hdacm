#include <cstdio>

int main(){
    unsigned T;
    scanf("%u", &T);
    while(T-- > 0){
        unsigned N;
        scanf("%u", &N);
        unsigned result = 3 * N * (N - 1) + 2;
        printf("%u\n", result);
    }
    return 0;
}
