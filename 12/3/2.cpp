/*
#include <cstdio>

int mp[63][5][5] = {
    {
        //1.1
        {1,0,0},
        {1,0,0},
        {1,1,1},
    },
    {
        //1.2
        {1,1,1},
        {0,0,1},
        {0,0,1},
    },
    {
        //1.3
        {0,0,1},
        {0,0,1},
        {1,1,1},
    },
    {
        //1.4
        {1,1,1},
        {1,0,0},
        {1,0,0},
    },
    {
        //2.5
        {1,1,1,1,1},
    },
    {
        //2.6
        {1},
        {1},
        {1},
        {1},
        {1},
    },
    {
        //3.7
        {0,1,0},
        {1,1,1},
        {0,1,0},
    },
    {
        //4.8
        {1,1,1},
        {1,0,1},
    },
    {
        //4.9
        {1,0,1},
        {1,1,1},
    },
    {
        //4.10
        {1,1},
        {1,0},
        {1,1},
    },
    {
        //4.11
        {1,1},
        {0,1},
        {1,1},
    },
    {
        //5.12
        {1,1,1,1},
        {1,0,0,0},
    },
    {
        //5.13
        {1,0},
        {1,0},
        {1,0},
        {1,1},
    },
    {
        //5.14
        {0,0,0,1},
        {1,1,1,1},
    },
    {
        //5.15
        {1,1},
        {0,1},
        {0,1},
        {0,1},
    },
    {
        //5.16
        {1,0,0,0},
        {1,1,1,1},
    },
    {
        //5.17
        {0,1},
        {0,1},
        {0,1},
        {1,1},
    },
    {
        //5.18
        {1,1,1,1},
        {0,0,0,1},
    },
    {
        //5.19
        {1,1},
        {1,0},
        {1,0},
        {1,0},
    },
    {
        //6.20
        {1,0,0},
        {1,1,0},
        {0,1,1},
    },
    {
        //6.21
        {0,0,1},
        {0,1,1},
        {1,1,0},
    },
    {
        //6.22
        {1,1,0},
        {0,1,1},
        {0,0,1},
    },
    {
        //6.23
        {0,1,1},
        {1,1,0},
        {1,0,0},
    },
    {
        //7.24
        {1,1,1,1},
        {0,1,0,0},
    },
    {
        //7.25
        {1,0},
        {1,0},
        {1,1},
        {1,0},
    },
    {
        //7.26
        {0,0,1,0},
        {1,1,1,1},
    },
    {
        //7.27
        {0,1},
        {1,1},
        {0,1},
        {0,1},
    },
    {
        //7.28
        {0,1,0,0},
        {1,1,1,1},
    },
    {
        //7.29
        {0,1},
        {0,1},
        {1,1},
        {0,1},
    },
    {
        //7.30
        {1,1,1,1},
        {0,0,1,0},
    },
    {
        //7.31
        {1,0},
        {1,1},
        {1,0},
        {1,0},
    },
    {
        //8.32
        {0,0,1},
        {1,1,1},
        {1,0,0},
    },
    {
        //8.33
        {1,1,0},
        {0,1,0},
        {0,1,1},
    },
    {
        //8.34
        {1,0,0},
        {1,1,1},
        {0,0,1},
    },
    {
        //8.35
        {0,1,1},
        {0,1,0},
        {1,1,0},
    },
    {
        //9.36
        {0,1,0},
        {0,1,1},
        {1,1,0},
    },
    {
        //9.37
        {0,1,0},
        {1,1,1},
        {0,0,1},
    },
    {
        //9.38
        {0,1,1},
        {1,1,0},
        {0,1,0},
    },
    {
        //9.39
        {1,0,0},
        {1,1,1},
        {0,1,0},
    },
    {
        //9.40
        {1,1,0},
        {0,1,1},
        {0,1,0},
    },
    {
        //9.41
        {0,1,0},
        {1,1,1},
        {1,0,0},
    },
    {
        //9.42
        {0,1,0},
        {1,1,0},
        {0,1,1},
    },
    {
        //9.43
        {0,0,1},
        {1,1,1},
        {0,1,0},
    },
    {
        //10.44
        {0,1,0},
        {0,1,0},
        {1,1,1},
    },
    {
        //10.45
        {1,1,1},
        {0,1,0},
        {0,1,0},
    },
    {
        //10.46
        {0,0,1},
        {1,1,1},
        {0,0,1},
    },
    {
        //10.47
        {1,0,0},
        {1,1,1},
        {1,0,0},
    },
    {
        //11.48
        {0,1,1},
        {1,1,1},
    },
    {
        //11.49
        {1,1},
        {1,1},
        {0,1},
    },
    {
        //11.50
        {1,1,1},
        {1,1,0},
    },
    {
        //11.51
        {1,0},
        {1,1},
        {1,1},
    },
    {
        //11.52
        {1,1,1},
        {0,1,1},
    },
    {
        //11.53
        {1,1},
        {1,1},
        {1,0},
    },
    {
        //11.54
        {1,1,0},
        {1,1,1},
    },
    {
        //11.55
        {0,1},
        {1,1},
        {1,1},
    },
    {
        //12.56
        {0,1,1,1},
        {1,1,0,0},
    },
    {
        //12.57
        {1,0},
        {1,0},
        {1,1},
        {0,1},
    },
    {
        //12.58
        {0,0,1,1},
        {1,1,1,0},
    },
    {
        //12.59
        {1,0},
        {1,1},
        {0,1},
        {0,1},
    },
    {
        //12.60
        {1,1,1,0},
        {0,0,1,1},
    },
    {
        //12.61
        {0,1},
        {1,1},
        {1,0},
        {1,0},
    },
    {
        //12.62
        {1,1,0,0},
        {0,1,1,1},
    },
    {
        //12.63
        {0,1},
        {0,1},
        {1,1},
        {1,0},
    },
};
//a代表每个的行，b代表每个的列，c代表每个属于哪种
int a[]= {3,3,3,3,1,5,3,2,2,3,3,2,4,2,4,2,4,2,4,3,3,3,3,2,4,2,4,2,4,2,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,3,2,3,2,3,2,4,2,4,2,4,2,4};
int b[]= {3,3,3,3,5,1,3,3,3,2,2,4,2,4,2,4,2,4,2,3,3,3,3,4,2,4,2,4,2,4,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,3,2,3,2,4,2,4,2,4,2,4,2};
int c[]= {1,1,1,1,2,2,3,4,4,4,4,5,5,5,5,5,5,5,5,6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,9,9,9,9,9,9,9,9,10,10,10,10,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12};

#define N 63*66*(60+66+14)
#define M 63*66

int ooo,haha;

struct DLX{
    int n,m,C;
    int U[N],D[N],L[N],R[N],Row[N],Col[N];
    int H[N],S[M],cnt,ans[M];
    void init(int _n,int _m){
        n=_n;
        m=_m;
        for(int i=0; i<=m; i++)
        {
            U[i]=D[i]=i;
            L[i]=(i==0?m:i-1);
            R[i]=(i==m?0:i+1);
            S[i]=0;
        }
        C=m;
        for(int i=1; i<=n; i++) H[i]=-1;
    }
    void link(int x,int y){
        C++;
        Row[C]=x;
        Col[C]=y;
        S[y]++;
        U[C]=U[y];
        D[C]=y;
        D[U[y]]=C;
        U[y]=C;
        if(H[x]==-1) H[x]=L[C]=R[C]=C;
        else
        {
            L[C]=L[H[x]];
            R[C]=H[x];
            R[L[H[x]]]=C;
            L[H[x]]=C;
        }
    }
    void del(int x){
        R[L[x]]=R[x];
        L[R[x]]=L[x];
        for(int i=D[x]; i!=x; i=D[i])
        {
            for(int j=R[i]; j!=i; j=R[j])
            {
                U[D[j]]=U[j];
                D[U[j]]=D[j];
                S[Col[j]]--;
            }
        }
    }
    void rec(int x){
        for(int i=U[x]; i!=x; i=U[i])
        {
            for(int j=L[i]; j!=i; j=L[j])
            {
                U[D[j]]=j;
                D[U[j]]=j;
                S[Col[j]]++;
            }
        }
        R[L[x]]=x;
        L[R[x]]=x;
    }
    void dance(int x){
        if(R[0]==0 || R[0]>ooo)
        {
            haha++;
            //cnt=x;
            return ;
        }
        int now=R[0];
        for(int i=R[0]; i!=0 && i<=ooo; i=R[i])
        {
            if(S[i]<S[now]) now=i;
        }
        del(now);
        for(int i=D[now]; i!=now; i=D[i])
        {
            //ans[x]=Row[i];
            for(int j=R[i]; j!=i; j=R[j]) del(Col[j]);
            dance(x+1);
            for(int j=L[i]; j!=i; j=L[j]) rec(Col[j]);
        }
        rec(now);
        return ;
    }
} dlx;

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=-1)
    {
        int cnt=0;
        ooo=60;
        dlx.init(63*60*5,60+12);
        for(int i=0; i<63; i++)
        {
            for(int xx=1; xx+a[i]<=n+1; xx++)
            {
                for(int yy=1; yy+b[i]<=m+1; yy++)
                {
                    cnt++;
                   // if(c[i]<5) printf("%d:",c[i]);
                    for(int x=0; x<a[i]; x++)
                    {
                        for(int y=0; y<b[i]; y++)
                        {
                            if(mp[i][x][y]==1)
                            {
                                int tep=(xx+x-1)*m+(yy+y);
                               // if(c[i]<5)printf("%d ",tep);
                                dlx.link(cnt,tep);
                            }
                        }
                    }
                    //if(c[i]<5)  puts("");
                    dlx.link(cnt,60+c[i]);
                }
            }
        }

        haha=0;
        dlx.dance(0);
        printf("%d\n",haha);
    }
    return 0;
}
*/

#include <cstdio>

int ans[]={0, 0, 0, 2, 368, 1010, 2339};
int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF){
        if(n > m) n = m;
        printf("%d\n", ans[n]);
    }
    return 0;
}
