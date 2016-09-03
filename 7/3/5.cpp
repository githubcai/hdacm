#include <cstdio>
#include <cstring>

const int MAX = 10001;
int A[100], c1[MAX], c2[MAX];

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        int tNum = 0;
        for(int i = 0; i < N; ++i){
            scanf("%d", &A[i]);
            tNum += A[i];
        }
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        c1[0] = c1[A[0]] = 1;
        for(int i = 1; i < N; ++i){
            for(int j = 0; j <= tNum; ++j){
                for(int k = 0; k + j <= tNum && k <= A[i]; k += A[i]){
                    c2[k + j] += c1[j];
                }
            }
            for(int j = 0; j <= tNum; ++j){
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        for(int i = tNum; i > 0; --i){
            if(c1[i] == 0) continue;
            for(int j = 1; j < i; ++j){
                if(c1[j] == 0) continue;
                c2[i - j] = 1;
            }
        }
        int count = 0;
        for(int i = 1; i <= tNum; ++i){
            if(c1[i] == 0 && c2[i] == 0){
                c2[count++] = i;
            }
        }
        printf("%d\n", count);
        if(count != 0){
            printf("%d", c2[0]);
            for(int i = 1; i < count; ++i){
                printf(" %d", c2[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
