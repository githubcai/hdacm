#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX= 1000;
int num[MAX];

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        for(int i = 1; i <= N; ++i){
            num[i - 1] = i;
        }
        for(int i = 1; i < M; ++i){
            next_permutation(num, num + N);
        }
        printf("%d", num[0]);
        for(int i = 1; i < N; ++i){
            printf(" %d", num[i]);
        }
        printf("\n");
    }
    return 0;
}
