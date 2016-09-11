#include <cstdio>

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int N; scanf("%d", &N);
        int A; scanf("%d", &A);
        int ans = A;
        bool flag = false;
        if(A > 1) flag = true;
        for(int i = 1; i < N; ++i){
            scanf("%d", &A);
            ans ^= A;
            if(A > 1) flag = true;
        }
        if(ans == 0){
            if(flag){
                printf("Brother\n");
            }else{
                printf("John\n");
            }
        }else{
            if(flag){
                printf("John\n");
            }else{
                printf("Brother\n");
            }
        }
    }
    return 0;
}
