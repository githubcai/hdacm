#include <cstdio>
#include <cstring>

const int MAX = 1001;
int f[MAX], sg[MAX];
bool hash[MAX];

void getSG(int n){
    memset(sg, 0, sizeof(sg));
    for(int i = 1; i <= n; ++i){
        memset(hash, 0, sizeof(hash));
        for(int j = 1; f[j] <= i; ++j){
            hash[sg[i - f[j]]] = true;
        }
        for(int j = 0; j <= n; ++j){
            if(!hash[j]){
                sg[i] = j;
                break;
            }
        }
    }
}

int main(){
    int m, n, p;
    f[0] = f[1] = 1;
    for(int i = 2; i <= 16; ++i){
        f[i] = f[i - 1] + f[i - 2];
    }
    getSG(1000);
    while(scanf("%d%d%d", &m, &n, &p) == 3){
        if(m == 0 && n == 0 && p == 0) break;
        if((sg[m] ^ sg[n] ^ sg[p]) == 0){
            printf("Nacci\n");
        }else{
            printf("Fibo\n");
        }
    }
    return 0;
}
