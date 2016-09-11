#include <cstdio>

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        int ans, A;
        scanf("%d", &A);
        ans = A;
        bool flag = false;
        if(A > 1) flag = true;
        for(int i = 1; i < n; ++i){
            scanf("%d", &A);
            ans ^= A;
            if(A > 1) flag = true;
        }
        if(ans == 0){
            if(flag){
                printf("No\n");
            }else{
                printf("Yes\n");
            }
        }else{
            if(flag){
                printf("Yes\n");
            }else{
                printf("No\n");
            }
        }
    }
    return 0;
}
