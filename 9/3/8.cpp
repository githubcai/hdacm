#include <cstdio>
#include <cstring>

const int MAX = 1000005;
int f1[MAX], f2[MAX];

int main(){
    int a, b, c, d;
    while(scanf("%d%d%d%d", &a, &b, &c, &d) == 4){
        if((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)){
            printf("0\n");
            continue;
        }
        memset(f1, 0, sizeof(f1));
        memset(f2, 0, sizeof(f2));
        for(int i = 1; i <= 100; ++i){
            for(int j = 1; j <= 100; ++j){
                int temp = a * i * i + b * j * j;
                if(temp >= 0){
                    ++f1[temp];
                }else{
                    ++f2[-temp];
                }
            }
        }
        int sum = 0;
        for(int i = 1; i <= 100; ++i){
            for(int j = 1; j <= 100; ++j){
                int temp = c * i * i + d * j * j;
                if(temp > 0){
                    sum += f2[temp];
                }else{
                    sum += f1[-temp];
                }
            }
        }
        printf("%d\n", sum * 16);
    }
    return 0;
}
