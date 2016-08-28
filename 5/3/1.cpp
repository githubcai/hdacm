#include <cstdio>
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1

const int MAX = 50001;
int SUM[MAX << 2];

void PushUP(int rt){
    SUM[rt] = SUM[rt << 1] + SUM[rt << 1 | 1];
}

void build(int l, int r, int rt){
    int m = (l + r) >> 1;
    if(l == r){
        scanf("%d", &SUM[rt]);
        return;
    }
    build(LSON);
    build(RSON);
    PushUP(rt);
}

void update(int p, int add, int l, int r, int rt){
    int m = (l + r) >> 1;
    if(l == r){
        SUM[rt] = SUM[rt] + add;
        return;
    }
    if(p <= m){
        update(p, add, LSON);
    }else{
        update(p, add, RSON);
    }
    PushUP(rt);
}

int query(int L, int R, int l, int r, int rt){
    int ret = 0, m = (l + r) >> 1;
    if(L <= l && r <= R){
        return SUM[rt];
    }
    if(L <= m) ret += query(L, R, LSON);
    if(R > m) ret += query(L, R, RSON);
    return ret;
}

int main(){
    int T, N, a, b, cas = 0;
    char comm[6];
	scanf("%d", &T);
	while(T-- > 0){
		scanf("%d", &N);
		cas++;
		printf("Case %d:\n", cas);
		build(1, N, 1);
		while(true){
			scanf("%s", comm);
            if(comm[0] == 'E') break;
            scanf("%d%d", &a, &b);
			if(comm[0] == 'Q'){
				printf("%d\n", query(a, b, 1, N, 1));
			}else if(comm[0] == 'A'){
				update(a, b, 1, N, 1);
			}else{
				update(a, -b, 1, N, 1);
		    }
        }
	}
	return 0;
}
