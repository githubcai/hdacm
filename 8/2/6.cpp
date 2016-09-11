#include <cstdio>

int main(){
    int C; scanf("%d", &C);
    while(C-- > 0){
        int n, m;
        scanf("%d%d", &n, &m);
        if(n % (m + 1) == 0){
            printf("Rabbit\n");
        }else{
            printf("Grass\n");
        }
    }
    return 0;
}
