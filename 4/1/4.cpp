#include <cstdio>
#include <cmath>

long long cal(long long N){
    return floor((-1 + sqrt(1 + 8 * N)) / 2.0);
}

int main(){
    int K;
    scanf("%d", &K);
    while(K-- > 0){
        int N;
        scanf("%d", &N);
        long long n = cal(N);
        long long t1 = n * (n + 1) / 2, t2 = N - t1, temp;
        if(t2 == 0){
            temp = (n - 1) % 9 + 1;
        }else{
            temp = (t2 - 1) % 9 + 1;
        }
        printf("%lld\n", temp);
    }
    return 0;
}
