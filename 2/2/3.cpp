#include <cstdio>
#include <cstring>

const int MAX = 65;
int P[3][MAX], N;

bool judge(int n, int si, int mi, int ei, int s, int m, int e){
    if(n == 0) return true;
    if(P[si][s] != n && P[ei][e] != n) return false;
    
    if(P[si][s] == n){
        return judge(--n, si, ei, mi, ++s, e, m);
    }else{
        return judge(--n, mi, si, ei, m, s, ++e);
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%d", &N);
        memset(P, 0, sizeof(P));
        for(int i = 0; i < 3; ++i){
            int temp;
            scanf("%d", &temp);
            for(int j = 0; j < temp; ++j){
                scanf("%d", &P[i][j]);
            }
        }
        if(judge(N, 0, 1, 2, 0, 0, 0)){
            printf("true\n");
        }else{
            printf("false\n");
        }
    }
    return 0;
}
