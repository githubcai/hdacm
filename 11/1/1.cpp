#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 2020;
struct Node{
    int l, r;
    char com;
};

Node node[MAX];
int seg[2 * MAX];
bool color[2 * MAX], flag[2 * MAX];

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        int cnt = 0;
        for(int i = 0; i < N; ++i){
            scanf("%d %d %c\n", &node[i].l, &node[i].r, &node[i].com);
            ++node[i].r;
            seg[cnt++] = node[i].l;
            seg[cnt++] = node[i].r;
        }
        sort(seg, seg + cnt);
        int temp = cnt; cnt = 0;
        for(int i = 1; i < temp; ++i){
            if(seg[i] != seg[cnt]) seg[++cnt] = seg[i];
        }
        memset(color, 0, sizeof(color));
        memset(flag, 0, sizeof(flag));
        for(int i = N - 1; i >= 0; --i){
            for(int j = 0; j <= cnt; ++j){
                if(seg[j] >= node[i].r) break;
                if(seg[j] >= node[i].l && !flag[j]){
                    flag[j] = true;
                    if(node[i].com == 'w') color[j] = true;
                }
            }
        }
        int mLen = -1, pre, left, right;
        for(int i = 0; i <= cnt; ++i){
            if(color[i]){
                pre = i;
                for(++i; i <= cnt && color[i]; ++i);
                int temp = seg[i] - seg[pre];
                if(mLen < temp){
                    mLen = temp;
                    left = seg[pre];
                    right = seg[i] - 1;
                }
            }
        }
        if(mLen == -1){
            printf("Oh, my god\n");
        }else{
            printf("%d %d\n", left, right);
        }
    }
    return 0;
}
