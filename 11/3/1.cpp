#include <cstdio>

const int NMAX = 1000001, MMAX = 10001;
int A[NMAX], B[MMAX], next[MMAX] = {0};

void getNext(int M){
    for(int i = 1, j = 0; i < M; ++i){
        while(j > 0 && B[i] != B[j]) j = next[j - 1];
        if(B[i] == B[j]) ++j;
        next[i] = j;
    }
}

int kmp(int N, int M){
    getNext(M);
    for(int i = 0, j = 0; i < N; ++i){
        while(j > 0 && B[j] != A[i]) j = next[j - 1];
        if(A[i] == B[j]) ++j;
        if(j == M) return i - M + 2;
    }
    return -1;
}

int main(){
    int T; scanf("%d", &T);
    while(T--){
        int N, M;
        scanf("%d%d", &N, &M);
        for(int i = 0; i < N; ++i){
            scanf("%d", &A[i]);
        }
        for(int i = 0; i < M; ++i){
            scanf("%d", &B[i]);
        }
        if(N < M){
            printf("-1\n");
        }else{
            printf("%d\n", kmp(N, M));
        }
    }
    return 0;
}
