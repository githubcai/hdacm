#include<cstring>
#include<cstdio>

const int MAX = 32000;
int prime[MAX + 1];

void table(){
    memset(prime,0,sizeof(prime));
    for(int i = 2; i <= MAX; ++i){
        if(prime[i] == 0){
            for(int j = i + i; j <= MAX; j += i){
                 prime[j] = 1;
            }
        }
    }
}

int main(){
    table();
    int n, t, cnt = 0;
    scanf("%d",&t);
    while(t--){
        int sum = 1;
        scanf("%d",&n);
        for(int i = 2; i <= MAX; ++i){
            if(n == 1) break;
            if(prime[i] == 0){
                    int k = 0;
                    while(n % i == 0){
                        ++k;
                        n = n / i;
                    }
                    sum= sum * (2 * k + 1);
            }
        }
        if(n > 1) sum = sum * 3;
        printf("Scenario #%d:\n%d\n\n", ++cnt, (sum + 1) / 2);
    }
    return 0;
}
