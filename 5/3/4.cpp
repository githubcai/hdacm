#include <cstdio>
#include <cstring>

const int MAX = 10001, NMAX = 3000000;
int C[MAX], num[NMAX];

void update(int x, int add){
    while(x <= 10000){
        C[x] += add;
        x += x & (-x);
    }
}

long long getSum(int x){
    long long ret = 0;
    while(x > 0){
        ret += C[x];
        x -= x & (-x);
    }
    return ret;
}

int main(){
    int n;
    long long ans;
    while(scanf("%d", &n) == 1){
        memset(C, 0, sizeof(C));
        ans = 0;
        for(int i = 0; i < n; ++i){
            int a;
            scanf("%d", &num[i]);
            update(num[i], 1);
            ans += getSum(num[i] - 1);
        }

        int m;
        scanf("%d", &m);
        while(m-- > 0){
		    char ch[2];
		    scanf("%s", ch);
		    switch(ch[0]){
		        case 'Q':{
			        printf("%lld\n", ans);
			        break;
		        }
		        case 'R':{
			        int s, e;
			        scanf("%d%d", &s, &e);
			        int v = num[s];
			        for(int i = s + 1; i <= e; ++i){
			            num[i - 1] = num[i];
			            if(v < num[i]){
                            --ans;
                        }else if(v > num[i]){
                            ++ans;
                        }
			        }
			        num[e] = v;
			        break;
		        }
		    }
        }
    }
    return 0;
}
