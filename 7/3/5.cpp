#include <cstdio>
#include <cstring>

const int MAX = 10001;
int A[100];
bool c1[MAX];

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        int tNum = 0, count = N;
        for(int i = 0; i < N; ++i){
            scanf("%d", &A[i]);
            tNum += A[i];
        }
        memset(c1, 0, sizeof(c1));
        for(int i = A[0]; i <= tNum; i += A[0]){
            c1[i] = true;
            --count;
        }
        for(int i = 1; i < N; ++i){
            for(int j = 0; j <= tNum; ++j){
                for(int k = A[i]; k + j <= tNum; ++j){
                    if(!c1[k + j]){
                        c1[k + j] = true;
                        --count;
                    }
                }
            }
        }
        printf("%d\n", count);
        int i;
        for(i = 1; i <= tNum; ++i){
            if(!c1[i]){
                printf("%d", i);
                break;
            }
        }
        for(++i; i <= tNum; ++i){
            if(!c1[i]) printf(" %d", i);
        }
        printf("\n");
    }
    return 0;
}
