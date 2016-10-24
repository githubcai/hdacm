#include <stdio.h>
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
#define MAXN 222222

int MAX[MAXN << 2], MIN[MAXN << 2], SUM[MAXN << 2];

int max(int a, int b){
	return a > b ? a : b;
}

int min(int a, int b){
	return a > b ? b : a;
}

/* 把当前结点的信息更新到父结点 */
void PushUP(int rt){
	MAX[rt] = max(MAX[rt << 1], MAX[rt << 1 | 1]);
	MIN[rt] = min(MIN[rt << 1], MIN[rt << 1 | 1]);
	SUM[rt] = SUM[rt << 1] + SUM[rt << 1 | 1];
}

/* 建立线段树 */
void build(int l, int r, int rt){
	int m = (l + r) >> 1;
	if(l == r){
		scanf("%d", &MAX[rt]);
		MIN[rt] = MAX[rt];
		SUM[rt] = MAX[rt];
		return;
	}
	build(LSON);
	build(RSON);
	PushUP(rt);
}

/* 单点替换 */
void update(int p, int tihuan, int l, int r, int rt){
	int m = (l + r) >> 1;
	if(l == r){
		MAX[rt] = tihuan;
		MIN[rt] = tihuan;
		SUM[rt] = tihuan;
		return;
	}
	if(p <= m){
		update(p, tihuan, LSON);
	}else{
		update(p, tihuan, RSON);
	}
	PushUP(rt);
}

/* 单点增减 */
void update1(int p, int add, int l, int r, int rt){
	int m = (l + r) >> 1;
	if(l == r){
		SUM[rt] = SUM[rt] + add;
		MAX[rt] = MAX[rt] + add;
		MIN[rt] = MIN[rt] + add;
		return;
	}
	if(p <= m){
		update1(p, add, LSON);
	}else{
		update1(p, add, RSON);
	}
	PushUP(rt);
}

/* 区间最大值查询 */
int query(int L, int R, int l, int r, int rt){
	int ret = -1, m = (l + r) >> 1;
	if(L <= l && r <= R){
		return MAX[rt];
	}
	if(L <= m) ret = max(ret, query(L, R, LSON));
	if(R > m) ret = max(ret, query(L, R, RSON));
	return ret;
}

/* 区间最小值查询 */
int query1(int L, int R, int l, int r, int rt){
	int ret = 99999, m = (l + r) >> 1;
	if(L <= l && r <= R){
		return MIN[rt];
	}
	if(L <= m) ret = min(ret, query1(L, R, LSON));
	if(R > m) ret = min(ret, query1(L, R, RSON));
	return ret;
}

/* 区间和查询 */
int queryhe(int L, int R, int l, int r, int rt){
	int ret = 0, m = (l + r) >> 1;
	if(L <= l && r <= R){
		return SUM[rt];
	}
	if(L <= m) ret += queryhe(L, R, LSON);
	if(R > m) ret += queryhe(L, R, RSON);
	return ret;
}

int main(void){
	int n, m;
	while(scanf("%d %d", &n, &m) != EOF){
		build(1, n, 1);
		while(m--){
			char op[2];
			int a, b;
			scanf("%s%d%d", op, &a, &b);
			if(op[0] == 'Q'){		//区间求最大
				printf("%d\n", query(a, b, 1, n, 1));
			}else if(op[0] == 'M'){		//区间求最小
				printf("%d\n", query1(a, b, 1, n, 1));
			}else if(op[0] == 'U'){ //单点替换
				update(a, b, 1, n, 1);
			}else if(op[0] == 'H'){  //区间求和
				printf("%d\n", queryhe(a, b, 1, n, 1));
			}else if(op[0] == 'S'){ //单点增加
				update1(a, b, 1, n, 1);
			}else if(op[0] == 'E'){ //单点减少
				update1(a, -b, 1, n, 1);
			}
		}
	}
	return 0;
}
