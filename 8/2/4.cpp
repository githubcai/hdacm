#include <cstdio>

int main(){
    int m;
    while(scanf("%d", &m) == 1 && m != 0){
        int k; scanf("%d", &k);
        int ans = k;
        for(int i = 1; i < m; ++i){
            scanf("%d", &k);
            ans ^= k;
        }
        if(ans == 0){
            printf("Grass Win!\n");
        }else{
            printf("Rabbit Win!\n");
        }
    }
    return 0;
}
