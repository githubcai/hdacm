#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 1000;
int A[MAX], B[MAX];

bool cmp(int a, int b){
    return a > b;
}

int main(){
    int N, T;
    while(scanf("%d%d", &N, &T) == 2){
        for(int i = 0; i < N; ++i){
            scanf("%d", &A[i]);
        }
        for(int i = 0; i < N; ++i){
            scanf("%d", &B[i]);
        }
        sort(A, A + N);
        sort(B, B + N, cmp);
        int sum = 0;
        for(int i = 0; i < N; ++i){
            int temp = A[i] + B[i] - T;
            if(temp > 0){
                sum += temp;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
