#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int MAX = 110;

struct Node{
    int sx, sy, ex, ey, color;
};

Node node[MAX];
int xseg[2 * MAX], yseg[2 * MAX];
int color[2 * MAX][2 * MAX];

int main(){
    int H, W, Case = 1;
    while(scanf("%d%d", &H, &W) == 2 && H + W != 0){
        int N; scanf("%d", &N);
        int xcnt = 0, ycnt = 0, mColor = -1;
        for(int i = 0; i < N; ++i){
            scanf("%d%d%d%d%d", &node[i].sx, &node[i].sy, &node[i].ex, &node[i].ey, &node[i].color);
            xseg[xcnt++] = node[i].sx, xseg[xcnt++] = node[i].ex;
            yseg[ycnt++] = node[i].sy, yseg[ycnt++] = node[i].ey;
            if(mColor < node[i].color) mColor = node[i].color;
        }
        map<int, int> xref, yref;
        sort(xseg, xseg + xcnt);
        sort(yseg, yseg + ycnt);
        int temp = xcnt; xcnt = 0; xref[xseg[xcnt]] = xcnt;
        for(int i = 1; i < temp; ++i){
            if(xseg[i] != xseg[xcnt]){
                xseg[++xcnt] = xseg[i];
                xref[xseg[xcnt]] = xcnt;
            }
        }
        temp = ycnt; ycnt = 0; yref[yseg[ycnt]] = ycnt;
        for(int i = 1; i < temp; ++i){
            if(yseg[i] != yseg[ycnt]){
                yseg[++ycnt] = yseg[i];
                yref[yseg[ycnt]] = ycnt;
            }
        }
        memset(color, 0, sizeof(color));
        for(int i = N - 1; i >= 0; --i){
            for(int j = xref[node[i].sx]; j < xref[node[i].ex]; ++j){
                for(int k = yref[node[i].sy]; k < yref[node[i].ey]; ++k){
                    if(color[j][k] == 0) color[j][k] = node[i].color;
                }
            }
        }
        int cnt = 0, area[101] = {0};
        bool flag[101] = {false};
        for(int i = 0; i < xcnt; ++i){
            for(int j = 0; j < ycnt; ++j){
                if(color[i][j] != 0){
                    if(!flag[color[i][j]]){
                        ++cnt;
                        flag[color[i][j]] = true;
                    }
                    int pre = j;
                    for(++j; j < ycnt && color[i][j] == color[i][j - 1]; ++j);
                    --j;
                    area[color[i][j]] += (yseg[j + 1] - yseg[pre]) * (xseg[i + 1] - xseg[i]);
                }
            }
        }
        if(Case > 1) printf("\n");
        printf("Case %d:\n", Case++);
        for(int i = 1; i <= mColor; ++i){
            if(area[i] != 0){
                printf("%d %d\n", i, area[i]);
            }
        }
        if(cnt > 1){
            printf("There are %d colors left on the wall.\n", cnt);
        }else{
            printf("There is %d color left on the wall.\n", cnt);
        }
    }
    return 0;
}
