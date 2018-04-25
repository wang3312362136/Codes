#include <cstdio>
#include <algorithm>
 
const int maxn=100000;
const int inf=0x3f3f3f3f;
 
int read()
{
  int x=0,f=1;
  char ch=getchar();
  while((ch<'0')||(ch>'9'))
    {
      if(ch=='-')
        {
          f=-f;
        }
      ch=getchar();
    }
  while((ch>='0')&&(ch<='9'))
    {
      x=x*10+ch-'0';
      ch=getchar();
    }
  return x*f;
}
 
struct pps
{
  int x,y;
 
  bool operator <(const pps &other) const
  {
    if(x==other.x)
      {
        return y>other.y;
      }
    return x<other.x;
  }
};
 
pps p[maxn+10];
int n,len,f[maxn+10],tot;
 
int main()
{
  n=read();
  for(register int i=1; i<=n; ++i)
    {
      int a=read();
      if(a<=i)
        {
          p[++tot].x=a;
          p[tot].y=i-a;
        }
    }
  if(!tot)
    {
      puts("0");
      return 0;
    }
  std::sort(p+1,p+tot+1);
  f[1]=p[1].y;
  len=1;
  for(register int i=2; i<=tot; ++i)
    {
      int pos=std::upper_bound(f+1,f+len+1,p[i].y)-f;
      f[pos]=p[i].y;
      if(pos>len)
        {
          len=pos;
        }
    }
  printf("%d\n",len);
  return 0;
}
