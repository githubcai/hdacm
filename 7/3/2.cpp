#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define LL long long
const int maxn=55;
#define mod 200000000000000003LL //不能用const来定义。。，不知道为什么，需要是素数
#define diff 100000000000000000LL //偏移量，使得数都是整数，方便移位乘法
using namespace std;
LL x[maxn], g[maxn][maxn], a[maxn][maxn], b[maxn][maxn];
int n;
LL Mod(LL x)//加法取模，防止超__int64
{
    if(x>=mod)
        return x-mod;
    return x;
}
LL mul(LL a,LL b)//乘法，用移位乘法，同样防止超__int64
{
    LL s;
    for(s=0;b;b>>=1)
    {
        if(b&1)
            s=Mod(s+a);
        a=Mod(a+a);
    }
    return s;
}
void gcd(LL a,LL b,LL d,LL &x,LL &y)//拓展的欧几里德定理，求ax+by=gcd(a,b)的一个解
{
    if(!b){d=a;x=1;y=0;}
    else{gcd(b,a%b,d,y,x);y-=x*(a/b);}
}
LL inv(LL a,LL n)//求逆，用于除法
{
    LL x,y,d;
    gcd(a,n,d,x,y);
    return (x%n+n)%n;
}
void Gauss()//高斯消元
{
    int i,j,k;
    LL v,tmp;
    for(i=0;i<n;i++)
    {
        for(j=i;j<n;j++)
        {
            if(g[j][i])
                break;
        }
        if(i!=j)
        {
            for(k=i;k<=n;k++)
                swap(g[i][k],g[j][k]);
        }
        v=inv(g[i][i],mod);
        for(j=i+1;j<n;j++)
        {
            if(g[j][i])
            {
                tmp=mul(g[j][i],v);//相当于g[j][i]/g[i][i]%mod;
                for(k=i;k<=n;k++)
                {
                    g[j][k]-=mul(tmp,g[i][k]);
                    g[j][k]=(g[j][k]%mod+mod)%mod;
                }
            }
        }
    }
    //求出所以的解，存入x数组中
    for(i=n-1;i>=0;i--)
    {
        tmp=0;
        for(j=i+1;j<n;j++)
        {
            tmp+=mul(x[j],g[i][j]);
            if(tmp>=mod)
                tmp-=mod;
        }
        tmp=g[i][n]-tmp;
        tmp=(tmp%mod+mod)%mod;
        x[i]=mul(tmp,inv(g[i][i],mod));
    }
}
int main()
{
    int T,tt=0;
    int i,j;
    LL tmp;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(g,0,sizeof(g));
        memset(b,0,sizeof(b));
        for(i=0;i<=n;i++)
        {
            for(j=0;j<n;j++)
            {
                scanf("%lld",&a[i][j]);
                a[i][j]+=diff;//偏移diff
                b[i][n]+=mul(a[i][j],a[i][j]);
                if (b[i][n]>=mod)
                    b[i][n]-=mod;
            }
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                tmp=a[i+1][j]-a[i][j];
                tmp=(tmp%mod+mod)%mod;
                g[i][j]=mul(tmp,2);
            }
            g[i][n]=b[i+1][n]-b[i][n];
            g[i][n]=(g[i][n]%mod+mod)%mod;
        }
        Gauss();
        printf("Case %d:\n",++tt);
        printf("%lld",x[0]-diff);//减去先前偏移的值。
        for (i=1;i<n;i++)
            printf(" %lld",x[i]-diff);
        printf("\n");
    }
    return 0;
}
/*
    由题意，列方程组∑(xj-aij)^2=R^2(0<=j<n),共n+1个方程。
    存在未知数R，以及二次方，需要降次。逐个与上方方程做差，得到n元一次方程组，共n个方程。
    剩下套高斯消元的模板就OK了。
    不过这题有几点需要注意：
    1.未知数是xi<=1e17，所以无法直接乘除。又∑ai*xi=an和∑ai*xi=an(mod n)(0<=i<=n,xi<n)的解相同
(乘法和加法取余处理下酒能证明)。所以可以%mod来解决。
    2.由于需要求逆，所以mod为素数2e17+3。又正常乘法会超过__int64，所以需要用移位乘法。
    3.为简单化移位，需要乘数，所以需要添加偏移量diff，根据数学运算可知，只要最后结果减去偏移量即可。
*/
