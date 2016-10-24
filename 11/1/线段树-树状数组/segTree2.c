/* 区间增减 */
#include <stdio.h>
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
#define LL long long
#define MAXN 100100

LL lazy[MAXN << 2], sum[MAXN << 2];

void PushUp(int rt){
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void PushDown(int rt, int m){
	if(lazy[rt]){
		lazy[rt << 1] += lazy[rt];
		lazy[rt << 1 | 1] += lazy[rt];
		sum[rt << 1] += lazy[rt] * (m - (m >> 1));
		sum[rt << 1 | 1] += lazy[rt] * (m >> 1);
		lazy[rt] = 0;
	}
}

void build(int l, int r, int rt){
	int m = (l + r) >> 1;
	lazy[rt] = 0;
	if(l == r){
		scanf("%lld", &sum[rt]);
		return;
	}
	build(LSON);
	build(RSON);
	PushUp(rt);
}

void update(int L, int R, int c, int l, int r, int rt){
	int m = (l + r) >> 1;
	if(L <= l && r <= R){
		lazy[rt] += c;
		sum[rt] += (LL)c * (r - l + 1);
		return;
	}
	PushDown(rt, r - l + 1);
	if(L <= m) update(L, R, c, LSON);
	if(m < R) update(L, R, c, RSON);
	PushUp(rt);
}

LL query(int L, int R, int l, int r, int rt){
	int m = (l + r) >> 1;
	LL ret = 0;
	if(L <= l && r <= R){
		return sum[rt];
	}
	PushDown(rt, r - l + 1);
	if(L <= m) ret += query(L, R, LSON);
	if(m < R) ret += query(L, R, RSON);
	return ret;
}

int main(void){
	int n, m, a, b, c;
	char str[5];
	scanf("%d %d", &n, &m);
	build(1, n, 1);
	while(m--){
		scanf("%s", str);
		if(str[0] == 'Q'){
			scanf("%d %d", &a, &b);
			printf("%lld\n", query(a, b, 1, n, 1));
		}else if(str[0] == 'C'){
			scanf("%d %d %d", &a, &b, &c);
			update(a, b, c, 1, n, 1);
		}
	}
	return 0;
}
