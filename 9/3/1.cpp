#include <cstdio>

int main(){
    int k;
    while(scanf("%d", &k) == 1){
        double result = 0;
        int count = 0;
        while(result < 1){
            ++count;
            result += k / (count * 100.0);
        }
        printf("%d\n", count);
    }
    return 0;
}
