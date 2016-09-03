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
//用扩展欧几里得算法解线性方程ax+by=c;
bool linearEquation(int a,int b,int c,int& x,int &y)
{
    int d=Extended_Euclid(a,b,x,y);
    if(c%d) return false;

    int k=c/d;
    x*=k;y*=k;//求的只是其中一个解
    return true
