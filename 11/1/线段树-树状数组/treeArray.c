/* 求2的x次方 */
int lowbit(int x){
	return x & (-x);
}

/* 一维 */
void update(int x, int add){
	while(x <= MAXN){
		c[x] += add;
		x += lowbit(x);
	}
}

int getSum(int x){
	int ret = 0;
	while(x > 0){
		ret += c[x];
		x -= lowbit(x);
	}
	return ret;
}

/* 二维 */
void update(int x, int y, int data){
	int i, j;
	for(i = x; i <= MAXN; i += lowbit(i)){
		for(j = y; j <= MAXN; j += lowbit(j)){
			c[i][j] += data;
		}
	}
}

int getSum(int x, int y){
	int ret = 0, i, j;
	for(i = x; i > 0; i -= lowbit(i)){
		for(j = y; j > 0; j -= lowbit(j)){
			ret += c[i][j];
		}
	}
	return ret;
}
