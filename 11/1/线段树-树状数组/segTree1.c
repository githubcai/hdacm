/* 区间替换 */
#include<stdio.h>
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
#define MAXN 100100
#define LL long long

int lazy[MAXN << 2], sum[MAXN << 2];

/* 由左孩子、右孩子向上更新父结点 */
void PushUp(int rt){
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

/* 向下更新 */
void PushDown(int rt, int m){
	/* 惰性标记 */	
	if(lazy[rt]){
		lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
		sum[rt << 1] = (m - (m >> 1)) * lazy[rt];
		sum[rt << 1 | 1] = ((m >> 1)) * lazy[rt];
		lazy[rt] = 0;
	}
}

/* 建树 */
void build(int l, int r, int rt){
	int m = (l + r) >> 1;
	lazy[rt] = 0;
	if(l == r){
		scanf("%d", &sum[rt]);
		return;
	}
	build(LSON);
	build(RSON);
	PushUp(rt);
}

void update(int L, int R, int c, int l, int r, int rt){
	int m = (r + l) >> 1;
	if(L <= l && r <= R){
		lazy[rt] = c;
		sum[rt] = c * (r - l + 1);
		return;
	}
	PushDown(rt, r - l + 1);
	if(L <= m) update(L, R, c, LSON);
	if(R > m) update(L, R, c, RSON);
	PushUp(rt);
}

LL query(int L, int R, int l, int r, int rt){
	int m = (l + r) >> 1;
	LL ret = 0;
	if(L <=  l && r <= R){
		return sum[rt];
	}
	PushDown(rt, r - l + 1);
	if(L <= m) ret += query(L, R, LSON);
	if(m < R) ret += query(L, R, RSON);
	return ret;
}

int main(void){
	int n, m;
	char str[5];
	while(scanf("%d %d", &n, &m) != EOF){
		build(1, n, 1);
		while(m--){
			int a, b, c;
			scanf("%s", str);
			if(str[0] == 'T'){
				scanf("%d %d %d", &a, &b, &c);
				update(a, b, c, 1, n, 1);
			}else if(str[0] == 'Q'){
				scanf("%d %d", &a, &b);
				printf("%lld\n", query(a, b, 1, n, 1));
			}
		}
	}
	return 0;
}
