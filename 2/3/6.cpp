#include <cstdio>
#include <cstring>

const int XMAX = 101, YMAX = 18;
int table[XMAX][YMAX];

void mul(int *pro, int a){
    for(int i = 0, c = 0; i < YMAX; ++i){
        pro[i] = pro[i] * a + c;
        c = pro[i] / 10000;
        pro[i] %= 10000;
    }
}

void div(int *mer, int a){
    for(int i = YMAX - 1, mod = 0; i >= 0; --i){
        int temp = mod * 10000 + mer[i];
        mer[i] = temp / a;
        mod = temp % a;
    }
}

void init(){
    memset(table, 0, sizeof(table));
    table[1][0] = 1;
    for(int i = 2; i < XMAX; ++i){
        memcpy(table[i], table[i - 1], sizeof(table[i]));
        int temp = i - 1;
        mul(table[i], (2 * temp + 1) * (2 * temp + 2));
        div(table[i], (temp + 2) * (temp + 1));
    }
}

void print(int n){
    int left;
    for(left = YMAX - 1; left >= 0; --left){
        if(table[n][left] != 0) break;
    }
    printf("%d", table[n][left]);
    for(int i = left - 1; i >= 0; --i){
        printf("%04d", table[n][i]);
    }
    printf("\n");
}

int main(){
    init();
    int n;
    while(scanf("%d", &n) == 1 && n != -1){
        print(n);
    }
    return 0;
}
