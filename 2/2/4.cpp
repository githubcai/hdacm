#include <cstdio>

unsigned gdc(unsigned x, unsigned y){
    unsigned r;
    r = x % y;
    while(r != 0){
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

int main(){
    unsigned T;
    scanf("%u", &T);
    while(T-- > 0){
        unsigned x, y;
        scanf("%u%u", &x, &y);
        if(gdc(x, y) == 1){
            printf("NO\n");
        }else{
            printf("YES\n");
        }
    }
}
