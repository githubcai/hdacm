#include <cstdio>

unsigned count(unsigned x){
    int cnt = 1;
    while(x != 1){
        if(x % 2 == 1){
            x = 3 * x + 1;
        }else{
            x = x / 2;
        }
        ++cnt;
    }
    return cnt;
}

int main(){
    unsigned n, m, k;
    while(scanf("%u%u", &n, &m) == 2){
        unsigned tn, tm;
        if(n <= m){
            tn = n;
            tm = m;
        }else{
            tn = m;
            tm = n;
        }
        k = 0;
        for(unsigned i = tn; i <= tm; ++i){
            unsigned temp = count(i);
            if(k < temp) k = temp;
        }
        printf("%u %u %u\n", n, m, k);
    }
    return 0;
}
