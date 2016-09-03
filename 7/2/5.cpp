#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long 
const LL maxn=1001;
LL e[maxn],t;
LL gcd(LL a,LL b)//求最大公约数
{
    return b==0?a:gcd(b,a%b);
}
LL euler_phi(LL n)//求单个欧拉函数
{
    LL m=(LL)sqrt(n+0.5);
    LL i,ans=n;
    for(i=2;i<=m;i++)
        if(n%i==0)
        {
            ans=ans/i*(i-1);
            while(n%i==0)n/=i;
        }
    if(n>1)ans=ans/n*(n-1);
    return ans;
}
void find(LL n)//找出所有因子
{
    LL m=(LL)sqrt(n+0.5);
    for(LL i=1;i<m;i++)
        if(n%i==0){e[t++]=i;e[t++]=n/i;}
    if(m*m==n)e[t++]=m;
}
LL pow_mod(LL a,LL b,LL mod)//快速幂
{
    LL s=1;
    while(b)
    {
        if(b&1)
            s=(s*a)%mod;
        a=(a*a)%mod;
        b=b>>1;
    }
    return s;
}
int main()
{
    LL a,x,y;
    while(cin>>x>>y>>a)
    {
        LL m,phi,i;
        if(y==0){cout<<"1"<<endl;continue;}
        m=a/gcd(y/(x-1),a);
        if(gcd(m,x)!=1){cout<<"Impossible!"<<endl;continue;}//不互质，则x^k%m必定是gcd(m,x)的倍数
        phi=euler_phi(m);
        t=0;
        find(phi);
        sort(e,e+t);
        for(i=0;i<t;i++)
        {
            if(pow_mod(x,e[i],m)==1)
            {
                cout<<e[i]<<endl;
                break;
            }
        }
    }
    return 0;
}
/*
    euler_phi(i)，欧拉函数，表示求不大于i且与i互质的正整数个数。

    本题递推公式化简下可得到通项公式：ak=a0+Y/(X-1)*(X^k-1);后半部分是等比数列的和。
    现在求ak%a0=0,即Y/(X-1)*(X^k-1)%a0==0,令m=a0/gcd(Y/(X-1),a0),则可推到求最小的k使得
(X^k-1)%m==0,即X^k==1(mod m).
    根据欧拉定理得X^euler_phi(m)==1(mod m).(X与m互质)
    又由抽屉原理可知，X^k的余数必定是根据euler_phi(m)的某个因子为循环节循环的。
所以求出最小的因子k使得X^k%m==1,即为答案
*/

