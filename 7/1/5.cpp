#include <cstdio>
#include <cmath>

int gcd(int a, int b){
    int r = a % b;
    while(r != 0){
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int main(){
    int L;
    while(scanf("%d", &L) == 1 && L != 0){
        int sx, sy, px, py;
        scanf("%d%d%d%d", &sx, &sy, &px, &py);
        if(fabs(px) > L || fabs(py) > L){
            printf("Out Of Range\n");
            continue;
        }else if(fabs(px - sx) == 1 || fabs(py - sy) == 1){
            printf("Yes\n");
            continue;
        }else if(px == sx || py == sy){
            printf("No\n");
            continue;
        }
        int a = (int)fabs(px - sx), b = (int)fabs(py - sy);
        if(gcd(a, b) == 1){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
