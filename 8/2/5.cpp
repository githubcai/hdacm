#include <cstdio>

int main(){
    int N, M;
    while(scanf("%d%d", &M, &N) == 2){
        int mod = M % (N + 1);
        if(mod == 0){
            printf("none\n");
        }else{
            if(M <= N){
                printf("%d", mod);
                for(int i = mod + 1; i <= N; ++i){
                    printf(" %d", i);
                }
                printf("\n");
            }else{
                printf("%d\n", mod);
            }
        }
    }
    return 0;
}
