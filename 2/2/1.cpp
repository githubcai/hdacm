#include <cstdio>
#include <cmath>

const int MAX = 21;

int table[MAX] = {0, 1};

void init(){
    for(int i = 2; i < MAX; ++i){
        table[i] = table[i - 1] + table[i - 2];
    }
}

int main(){
    init();

    int n;
    double A = -0.5 * log10(5), B = log10((1 + sqrt(5)) / 2.0);
    while(scanf("%d", &n) == 1){
        if(n < MAX){
            printf("%d\n", table[n]);
            continue;
        }
        double temp = A + n * B;
        temp = temp - floor(temp + 1e-9);
        temp = pow(10, temp);
        printf("%d\n", int(temp * 1000));
    }
    return 0;
}
