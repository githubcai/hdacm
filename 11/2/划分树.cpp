#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100005
int a[N], as[N];//原数组，排序后数组
int n, m;
int sum[20][N];//记录第i层的1~j划分到左子树的元素个数(包括j)
int tree[20][N];//记录第i层元素序列
void build(int c, int l, int r){
    int i, mid = (l + r) >> 1, lm = mid - l + 1, lp = l, rp = mid + 1;
    for (i = l; i <= mid; i++){
        if (as[i] < as[mid]){
            lm--;//先假设左边的(mid - l + 1)个数都等于as[mid],然后把实际上小于as[mid]的减去
        }
    }
    for (i = l; i <= r; i++){
        if (i == l){
            sum[c][i] = 0;//sum[i]表示[l, i]内有多少个数分到左边，用DP来维护
        }else{
            sum[c][i] = sum[c][i - 1];
        }
        if (tree[c][i] == as[mid]){
            if (lm){
                lm--;
                sum[c][i]++;
                tree[c + 1][lp++] = tree[c][i];
            }else
                tree[c + 1][rp++] = tree[c][i];
        } else if (tree[c][i] < as[mid]){
            sum[c][i]++;
            tree[c + 1][lp++] = tree[c][i];
        } else{
            tree[c + 1][rp++] = tree[c][i];
        }
    }
    if (l == r)return;
    build(c + 1, l, mid);
    build(c + 1, mid + 1, r);
}
int query(int c, int l, int r, int ql, int qr, int k){
    int s;//[l, ql)内将被划分到左子树的元素数目
    int ss;//[ql, qr]内将被划分到左子树的元素数目
    int mid = (l + r) >> 1;
    if (l == r){
        return tree[c][l];
    }
    if (l == ql){//这里要特殊处理！
    s = 0;
    ss = sum[c][qr];
    }else{
        s = sum[c][ql - 1];
        ss = sum[c][qr] - s;
    }//假设要在区间[l,r]中查找第k大元素，t为当前节点，lch，rch为左右孩子，left，mid为节点t左边界和中间点。
    if (k <= ss){//sum[r]-sum[l-1]>=k，查找lch[t],区间对应为[ left+sum[l-1], left+sum[r]-1 ]
        return query(c + 1, l, mid, l + s, l + s + ss - 1, k);
    }else{//sum[r]-sum[l-1]<k,查找rch[t]，区间对应为[ mid+1+l-left-sum[l-1], mid+1+r-left-sum[r] ]
        return query(c + 1, mid + 1, r, mid - l + 1 + ql - s, mid - l + 1 + qr - s - ss,k - ss);
    }
}
int main(){
    int i, j, k;
    while(~scanf("%d%d", &n, &m)){
        for (i = 1; i <= n; i++){
            scanf("%d", &a[i]);
            tree[0][i] = as[i] = a[i];
        }
        sort(as + 1, as + 1 + n);
        build(0, 1, n);
        while(m--){
            scanf("%d%d%d",&i,&j,&k);// i,j分别为区间起始点，k为该区间第k大的数。
            printf("%d\n", query(0, 1, n, i, j, k));
        }
    }
    return 0;
}
