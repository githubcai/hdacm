#include <cstdio>
#include <cstring>

const int MAX = 1005;
int C[MAX][MAX];
bool flag[MAX][MAX];

void update(int x, int y, int v){
    int temp = y;
    while(x < MAX){
        y = temp;
        while(y < MAX){
            C[x][y] += v;
            y += y & (-y);
        }
        x += x & (-x);
    }
}

int getSum(int x, int y){
    int temp = y, ret = 0;
    while(x > 0){
        y = temp;
        while(y > 0){
            ret += C[x][y];
            y -= y & (-y);
        }
        x -= x & (-x);
    }
    return ret;
}

int main(){
    int M, x1, x2, y1, y2;
    char comm[2];
    while(scanf("%d", &M) == 1){
        memset(C, 0, sizeof(C));
        memset(flag, 0, sizeof(flag));
        for(int i = 0; i < M; ++i){
            scanf("%s", comm);
            switch(comm[0]){
            case 'B':
                scanf("%d%d", &x1, &y1);
                ++x1, ++y1;
                if(!flag[x1][y1]){
                    update(x1, y1, 1);
                    flag[x1][y1] = true;
                }
                break;
            case 'D':
                scanf("%d%d", &x1, &y1);
                ++x1, ++y1;
                if(flag[x1][y1]){
                    update(x1, y1, -1);
                    flag[x1][y1] = false;
                }
                break;
            case 'Q':
                scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
                ++x1, ++x2, ++y1, ++y2;
                if(x1 > x2){
                    int temp = x1;
                    x1 = x2;
                    x2 = temp;
                }
                if(y1 > y2){
                    int temp = y1;
                    y1 = y2;
                    y2 = temp;
                }
                int result = getSum(x2, y2) - getSum(x1 - 1, y2) - getSum(x2, y1 - 1) + getSum(x1 - 1, y1 - 1);
                printf("%d\n", result);
                break;
            }
        }
    }
    return 0;
}
