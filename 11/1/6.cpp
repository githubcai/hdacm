#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

float tree[410][4010];

void buildY(int l, int r, int deep, int rt){
    tree[deep][rt] = -1.0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    buildY(l, mid, deep, rt << 1);
    buildY(mid + 1, r, deep, rt << 1 | 1);
}

void build(int l, int r, int rt){
    buildY(0, 1000, rt, 1);
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
}

void updateY(int A, float L, int l, int r, int deep, int rt){
    tree[deep][rt] = max(L, tree[deep][rt]);
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(A <= mid){
        updateY(A, L, l, mid, deep, rt << 1);
    }else{
        updateY(A, L, mid + 1, r, deep, rt << 1 | 1);
    }
    tree[deep][rt] = max(tree[deep][rt << 1], tree[deep][rt << 1 | 1]);
}

void update(int H, int A, float L, int l, int r, int rt){
    updateY(A, L, 0, 1000, rt, 1);
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(H <= mid){
        update(H, A, L, l, mid, rt << 1);
    }else{
        update(H, A, L, mid + 1, r, rt << 1 | 1);
    }
}

float queryY(int A1, int A2, int l, int r, int deep, int rt){
    float ret = -1;
    if(A1 <= l && r <= A2) return tree[deep][rt];
    int mid = (l + r) >> 1;
    if(A1 <= mid) ret = max(ret, queryY(A1, A2, l, mid, deep, rt << 1));
    if(A2 > mid) ret = max(ret, queryY(A1, A2, mid + 1, r, deep, rt << 1 | 1));
    return ret;
}

float query(int H1, int H2, int A1, int A2, int l, int r, int rt){
    float ret = -1;
    if(H1 <= l && r <= H2) return queryY(A1, A2, 0, 1000, rt, 1);
    int mid = (l + r) >> 1;
    if(H1 <= mid) ret = max(ret, query(H1, H2, A1, A2, l, mid, rt << 1));
    if(H2 > mid) ret = max(ret, query(H1, H2, A1, A2, mid + 1, r, rt << 1 | 1));
    return ret;
}

int main(){
    char comm[5];
    int T;
    while(scanf("%d", &T) == 1 && T != 0){
        build(100, 200, 1);
        for(int i = 0; i < T; ++i){
            scanf("%s", comm);
            if(comm[0] == 'I'){
                int H; float A, L;
                scanf("%d%f%f", &H, &A, &L);
                update(H, (int)(A * 10), L, 100, 200, 1);
            }else{
                int H1, H2; float A1, A2;
                scanf("%d%d%f%f", &H1, &H2, &A1, &A2);
                if(H1 > H2){
                    int temp = H1;
                    H1 = H2;
                    H2 = temp;
                }
                if(A1 > A2){
                    float temp = A1;
                    A1 = A2;
                    A2 = temp;
                }
                float ret = query(H1, H2, (int)(A1 * 10) , (int)(A2 * 10), 100, 200, 1);
                if(ret < 0){
                    printf("-1\n");
                }else{
                    printf("%.1f\n", ret);
                }
            }
        }
    }
    return 0;
}
