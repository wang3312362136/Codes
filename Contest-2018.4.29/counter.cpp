#include <cstdio>

const int maxn=200000;

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

int n,p[maxn+10];
long long ans;

namespace ta
{
  int c[maxn+10];

  int lowbit(int x)
  {
    return x&(-x);
  }

  int add(int pos)
  {
    while(pos<=n)
      {
        ++c[pos];
        pos+=lowbit(pos);
      }
    return 0;
  }

  int sum(int pos)
  {
    int res=0;
    while(pos)
      {
        res+=c[pos];
        pos-=lowbit(pos);
      }
    return res;
  }
}

int main()
{
  n=read();
  for(register int i=1; i<=n; ++i)
    {
      p[i]=read();
    }
  for(register int i=1; i<=n; ++i)
    {
      int ll=ta::sum(p[i]),lb=i-1-ll,rl=p[i]-1-ll,rb=n-i-rl;
      ans+=1ll*ll*rb-2ll*lb*rl;
      if(rl>=2)
        {
          ans+=1ll*rl*(rl-1)/2;
        }
      if(lb>=2)
        {
          ans+=1ll*lb*(lb-1)/2;
        }
      ta::add(p[i]);
    }
  printf("%lld\n",ans);
  return 0;
}
