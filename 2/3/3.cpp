#include <cstdio>
#include <cstring>

const int XMAX = 8000;
const int YMAX = 260;

int table[XMAX][YMAX];

void add(int *sum, int *a){
    int c, i;
    for(i = 0, c = 0; i < YMAX; ++i){
        sum[i] = sum[i] + a[i] + c;
        c = sum[i] / 100000000;
        sum[i] = sum[i] % 100000000;
    }
}

void init(){
    memset(table, 0, sizeof(table));
    table[1][0] = table[2][0] = table[3][0] = table[4][0] = 1;
    for(int i = 5; i < XMAX; ++i){
        add(table[i], table[i-1]);
        add(table[i], table[i-2]);
        add(table[i], table[i-3]);
        add(table[i], table[i-4]);
    }
}

void print(int num){
    int left;
    for(left = YMAX - 1; left >= 0; --left){
        if(table[num][left] != 0) break;
    }
    printf("%d", table[num][left--]);
    for(int i = left; i >= 0; --i){
        printf("%08d", table[num][i]);
    }
    printf("\n");
}

int main(){
    init();
    int num;
    while(scanf("%d", &num) == 1){
        print(num);
    }
    return 0;
}
