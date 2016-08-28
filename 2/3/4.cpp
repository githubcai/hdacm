#include <cstdio>
#include <cstring>

const int XMAX = 202, YMAX = 100;
int table[XMAX][YMAX], result[YMAX];

void mul(int *pro, int a){
    int c, i;
    for(i = 0, c = 0; i < YMAX; ++i){
        pro[i] = c + pro[i] * a;
        c = pro[i] / 10000;
        pro[i] = pro[i] % 10000;
    }
}

void div(int *mer, int a){
    int mod = 0;
    for(int i = YMAX - 1; i >= 0; --i){
        int temp = mod * 10000 + result[i];
        mod = temp % a;
        result[i] = temp / a;
    }
}

void init(){
    memset(table, 0, sizeof(table));
    table[1][0] = 1;
    for(int i = 2; i < XMAX; ++i){
        memcpy(table[i], table[i - 1], sizeof(table[i]));
        mul(table[i], i);
    }
}

void cal(int m, int n){
    memcpy(result, table[m + n], sizeof(result));
    mul(result, m - n + 1);
    div(result, m + 1);
}

void print(int cnt){
    printf("Test #%d:\n", cnt);
    int left;
    for(left = YMAX - 1; left >= 0; --left){
        if(result[left] != 0) break;
    }
    printf("%d", result[left]);
    for(int i = left - 1; i >= 0; --i){
        printf("%04d", result[i]);
    }
    printf("\n");
}

int main(){
    init();
    int m, n, cnt = 0;
    while(scanf("%d%d", &m, &n) == 2 && (m != 0 || n != 0)){
        ++cnt;
        if(m < n){
            printf("Test #%d:\n", cnt);
            printf("0\n");
            continue;
        }
        cal(m, n);
        print(cnt);
    }
    return 0;
}
