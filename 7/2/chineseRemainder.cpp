//chu是除数，yu是余数
//注意只适用于除数两两互质
#include<iostream>  
#include<queue>  
using namespace std;  
int extended_euclid(int a, int b, int &x, int &y) {
    int d;
    if(b == 0) {x = 1; y = 0; return a;}
    d = extended_euclid(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
int chinese_remainder(int b[], int w[], int len) { 
    int i, d, x, y, m, n, ret;
    ret = 0; n = 1; 
    for(i=0; i < len ;i++) n *= w[i];
    for(i=0; i < len ;i++) { 
        m = n / w[i];
        d = extended_euclid(w[i], m, x, y);
        ret = (ret + y*m*b[i]) % n;
    }
    return (n + ret%n) % n;
}
int yu[100],chu[100];
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=0;i<n;i++)
		{
			cin>>chu[i]>>yu[i];
		}
		int ans=chinese_remainder(yu,chu,n);
		printf("%d/n",ans);
	}
}

