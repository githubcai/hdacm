#include <cstdio>
#include <cstring>

int fact[8] = {1, 1, 2, 6, 24, 120, 720, 5040}, result[8];
bool flag[8];

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        --M;
        int index;
        for(index = 7; index >= 0; --index){
            if(M >= fact[index]) break;
        }
        int save = N - index;
        memset(flag, 0, sizeof(flag));
        int a, b = M, cnt = 0;
        while(index >= 0){
            a = b / fact[index];
            b = b % fact[index];
            int temp = 0, i;
            for(i = 0; temp != a + 1; ++i){
                if(!flag[i]) ++temp;
            }
            flag[--i] = true;
            result[cnt++] = i;
            --index;
        }
        bool isFirst = true;
        for(int i = 1; i < save; ++i){
            if(isFirst){
                isFirst = false;
            }else{
                printf(" ");
            }
            printf("%d", i);
        }
        for(int i = 0; i < cnt; ++i){
            if(isFirst){
                isFirst = false;
            }else{
                printf(" ");
            }
            printf("%d", save + result[i]);
        }
        printf("\n");
    }
    return 0;
}
