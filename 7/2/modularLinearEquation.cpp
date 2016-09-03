//扩展欧几里得算法
int Extended_Euclid(int a,int b,int& x,int &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int d=Extended_Euclid(b,a%b,x,y);
    int temp=x;x=y;y=temp-a/b*y;
    return d;
}

//用扩展欧几里得解模线性方程ax=b (mod n)
bool modularLinearEquation(int a,int b,int n)
{
    int x,y,x0,i;
    int d=Extended_Euclid(a,n,x,y);
    if(b%d) 
           return false;
        x0=x*(b/d)%n;
    for(i=1;i<=d;i++)
       printf("%d\n",(x0+i*(n/d))%n);
    return true;
}
