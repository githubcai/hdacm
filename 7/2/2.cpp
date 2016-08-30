#include <cstdio>
#include <cstring>

int phi(int x){
    int ret = x;
    for(int i = 2; i * i <= x; ++i){
        if(x % i == 0){
            ret = ret / i * (i - 1);
            while(x % i == 0){
                x /= i;
            }
        }
    }
    if(x > 1){
        ret = ret / x * (x - 1);
    }
    return ret;
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        printf("%d\n", n - phi(n) - 1);
    }
    return 0;
}
