#include <cstdio>
#include <cstring>

const int XMAX = 100100, YMAX = 13;

int pies[XMAX][YMAX];

int max(int x, int y, int z){
    int temp = (x > y ? x : y);
    return temp > z ? temp : z;
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        memset(pies, 0, sizeof(pies));
        int x, T, mT = -1;
        for(int i = 0; i < n; ++i){
            scanf("%d%d", &x, &T);
            pies[T][x + 1] += 1;
            if(mT < T) mT = T;
        }

        for(int i = mT - 1; i >= 0; --i){
            for(int j = 1; j < 12; ++j){
                pies[i][j] += max(pies[i + 1][j - 1], pies[i + 1][j], pies[i + 1][j + 1]);
            }
        }
        printf("%d\n", pies[0][6]);
    }
    return 0;
}
