#include <cstdio>

long long cal(long long n, long long N){
    return n * n + n - 2 * N;
}

int main(){
    int K;
    scanf("%d", &K);
    while(K-- > 0){
        int N;
        scanf("%d", &N);
        long long left = 1, right = 999999;
        while(right - left > 1){
            long long mid = (left + right) / 2;
            long long mr = cal(mid, N);
            if(mr < 0){
                left = mid;
            }else{
                right = mid;
            }
        }
        long long temp = N - left * (left + 1) / 2;
        if(temp == 0){
            temp = (left - 1) % 9 + 1;
        }else{
            temp = (temp - 1) % 9 + 1;
        }
        printf("%lld\n", temp);
    }
    return 0;
}
