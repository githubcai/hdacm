#include <cstdio>

const int MAX = 200001;
char A[MAX];
int next[MAX];

int getNext(int lenA){
    int sum = 1;
    next[0] = 0;
    for(int i = 1, j = 0; i < lenA; ++i){
        while(j > 0 && A[i] != A[j]) j = next[j - 1];
        if(A[i] == A[j]) ++j;
        next[i] = j;
        if(j > 0){
            sum = (sum + 2) % 10007;
        }else{
            sum = (sum + 1) % 10007;
        }
    }
    return sum;
}

int main(){
    int T; scanf("%d", &T);
    while(T--){
        int N; scanf("%d", &N);
        scanf("%s", A);
        printf("%d\n", getNext(N));
    }
    return 0;
}
