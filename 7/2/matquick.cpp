#define Matr 10 //矩阵大小,注意能小就小

struct mat//矩阵结构体，a表示内容，size大小 矩阵从0开始
{
    ll a[Matr][Matr],size;
    mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

mat multi(const mat &m1,const mat &m2,int mod)//两个相等矩阵的乘法，对于稀疏矩阵，有0处不用运算的优化 
{
    mat ans = mat();
    ans.size=m1.size;
    for(int i=0;i<m1.size;i++)
        for(int j=0;j<m2.size;j++)
            if(m1.a[i][j])//稀疏矩阵优化 
                for(int k=0;k<=m1.size;k++)
                    ans.a[i][k]=(ans.a[i][k]+m1.a[i][j]*m2.a[j][k])%mod;

    return ans;
}

mat quickmulti(mat m,int n,int mod)//二分快速幂 
{
    mat ans = mat();
    for(int i=0;i<m.size;i++)ans.a[i][i]=1;
    ans.size=m.size;
    while(n)
    {
        if(n&1)ans=multi(m,ans,mod);
        m=multi(m,m,mod);
        n>>=1;
    }
    return ans;
}
/*
ans^=n ->
mat ans=mat();
ans.size=Size;
初始化ans矩阵
ans=quickmulti(ans,n,mod);
*/


  

