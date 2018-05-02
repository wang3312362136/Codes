#include <cstdio>
#include <algorithm>

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

int n,a,b,s[maxn+10],tot;

int main()
{
  n=read();
  a=read();
  b=read();
  for(register int i=1; i<=n; ++i)
    {
      s[i]=read();
      tot+=s[i];
    }
  std::sort(s+2,s+n+1);
  double flow=1.0*s[1]*a/tot;
  if(flow>=b)
    {
      printf("%d\n",0);
      return 0;
    }
  for(register int i=n; i>=2; --i)
    {
      tot-=s[i];
      flow=1.0*s[1]*a/tot;
      if(flow>=b)
        {
          printf("%d\n",n+1-i);
          break;
        }
    }
  return 0;
}
