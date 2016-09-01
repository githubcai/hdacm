#include <cstdio>
#include <cstring>

const int MAX = 102;
int c1[MAX], c2[MAX];

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        int A, B;
        scanf("%d%d", &A, &B);
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c1));
        for(int i = A; i <= B; ++i){
            c1[i] = 1;
        }
        for(int i = 1; i < N; ++i){
            scanf("%d%d", &A, &B);
            for(int j = 0; j <= M; ++j){
                for(int k = A; k + j <= M && k <= B; k += 1){
                    c2[k + j] += c1[j];
                }
            }
            for(int j = 0; j <= M; ++j){
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        printf("%d\n", c1[M]);
    }
    return 0;
}
