#include <cstdio>

const int maxn=100000;

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

int n,m;

namespace dsu
{
  int fa[maxn+10],mark[maxn+10];

  int find(int x)
  {
    return fa[x]?fa[x]=find(fa[x]):x;
  }

  int merge(int x,int y)
  {
    x=find(x);
    y=find(y);
    if(x==y)
      {
        return 1;
      }
    fa[x]=y;
    if(mark[x])
      {
        mark[y]=1;
      }
    return 0;
  }
}

int main()
{
  n=read();
  m=read();
  while(m--)
    {
      int a=read(),b=read();
      if(dsu::merge(a,b))
        {
          dsu::mark[dsu::find(a)]=1;
        }
    }
  for(int i=1; i<=n; ++i)
    {
      if(!dsu::mark[dsu::find(i)])
        {
          puts("NIE");
          return 0;
        }
    }
  puts("TAK");
  return 0;
}
