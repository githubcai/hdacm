#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 100005;
int a[MAX], as[MAX], sum[20][MAX], tree[20][MAX];

void build(int c, int l, int r){
    int i, mid = (l + r) >> 1, lm = mid - l + 1, lp = l, rp = mid + 1;
    for(i = l; i <= mid; ++i){
        if(as[i] < as[mid]) --lm;
    }
    for(i = l; i <= r; ++i){
        if(i == l){
            sum[c][i] = 0;
        }else{
            sum[c][i] = sum[c][i - 1];
        }
        if(tree[c][i] == as[mid]){
            if(lm){
                --lm; ++sum[c][i];
                tree[c + 1][lp++] = tree[c][i];
            }else{
                tree[c + 1][rp++] = tree[c][i];
            }
        }else if(tree[c][i] < as[mid]){
            ++sum[c][i];
            tree[c + 1][lp++] = tree[c][i];
        }else{
            tree[c + 1][rp++] = tree[c][i];
        }
    }
    if(l == r) return;
    build(c + 1, l, mid);
    build(c + 1, mid + 1, r);
}

int query(int c, int l, int r, int ql, int qr, int k){
    int s, ss, mid = (l + r) >> 1;
    if(l == r) return tree[c][l];
    if(l == ql){
        s = 0; ss = sum[c][qr];
    }else{
        s = sum[c][ql - 1]; ss = sum[c][qr] - s;
    }
    if(k <= ss){
        return query(c + 1, l, mid, l + s, l + s + ss - 1, k);
    }else{
        return query(c + 1, mid + 1, r, mid - l + 1 + ql - s, mid - l + 1 + qr - s - ss, k - ss);
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, m; scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            tree[0][i] = as[i] = a[i];
        }
        sort(as + 1, as + n + 1);
        build(0, 1, n);
        for(int i = 0; i < m; ++i){
            int s, t, k; scanf("%d%d%d", &s, &t, &k);
            printf("%d\n", query(0, 1, n, s, t, k));
        }
    }
    return 0;
}
