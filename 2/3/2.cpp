#include <cstdio>
#include <cstring>

char R[7], rc[5000];
int n, result[1000], pcnt, num, rlen;

void trans(){
    pcnt = 0;

    int it;
    for(it = 5; it >= 0; --it){
        if(R[it] == '.') break;
        ++pcnt;
    }
    if(it == -1) pcnt = 0;

    int left = 0;
    while(true){
        if(R[left] != '0' && R[left] != '.') break;
        ++left;
    }
    num = 0;
    for(int i = left; i <= 5; ++i){
        if(R[i] == '.') continue;
        num = num * 10 + R[i] - '0';
    }
}

void mul(){
    int c = 0;
    for(int i = 0; i < rlen; ++i){
        result[i] = result[i] * num + c;
        c = result[i] / 10000;
        result[i] %= 10000;
    }
    while(c != 0){
        result[rlen] = c % 10000;
        c= c / 10000;
        ++rlen;
    }
}

void cal(){
    memset(result, 0, sizeof(result));
    result[0] = num;
    int c = result[0] / 10000;
    result[0] = result[0] % 10000;
    if(c == 0){
        rlen = 1;
    }else{
        rlen = 2;
        result[1] = c;
    }
    for(int i = 2; i <= n; ++i){
        mul();
    }
}

void print(){
    int total = n * pcnt, rclen = 0;
    memset(rc, 0, sizeof(rc));
    for(int i = 0; i < rlen; ++i){
        for(int j = 0; j < 4; ++j){
            rc[rclen++] = result[i] % 10;
            result[i] /= 10;
        }
    }

    int left = rclen - 1, right = 0;
    while(true){
        if(rc[right] != 0) break;
        ++right;
    }
    while(true){
        if(rc[left] != 0) break;
        --left;
    }
    if(total <= right){
        for(int i = left; i >= right; --i){
            printf("%d", rc[i]);
        }
        for(int i = right - 1; i >= total; --i){
            printf("0");
        }
        printf("\n");
    }else if(total > left){
        printf(".");
        for(int i = total - 1; i >= right; --i){
            printf("%d", rc[i]);
        }
        printf("\n");
    }else{
        for(int i = left; i >= total; --i){
            printf("%d", rc[i]);
        }
        printf(".");
        for(int i = total - 1; i >= right; --i){
            printf("%d", rc[i]);
        }
        printf("\n");
    }
}

int main(){
    while(scanf("%s%d", R, &n) != EOF){
        if(n == 0){
            printf("1\n");
            continue;
        }
        trans();
        if(num == 0){
            printf("0\n");
            continue;
        }
        cal();
        print();
    }
}
