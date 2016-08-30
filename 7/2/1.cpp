#include <cstdio>
#include <cstring>

const int MAX = 3000001;
int prime[MAX], phi[MAX];
bool isPrime[MAX];

void getPhi(){
    memset(prime, 0, sizeof(prime));
    memset(isPrime, 0, sizeof(isPrime));
    memset(phi, 0, sizeof(phi));
    int cnt = 0;
    for(int i = 2; i < MAX; ++i){
        if(!isPrime[i]){
            prime[cnt++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; j < cnt && i * prime[j] < MAX; ++j){
            isPrime[i * prime[j]] = true;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j]; 
            }else{
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

int main(){
    int a, b;
    getPhi();
    while(scanf("%d%d", &a, &b) == 2){
        long long sum = 0;
        for(int i = a; i <= b; ++i){
            sum += phi[i];
        }
        printf("%lld\n", sum);
    }
    return 0;
}
