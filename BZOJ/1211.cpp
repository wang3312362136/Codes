#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn=150;

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

int n,d[maxn+10],p[maxn+10][maxn+10],ans[maxn+10],tot;

int main()
{
  n=read();
  if(n==1)
    {
      int x=read();
      if(x==0)
        {
          puts("1");
        }
      else
        {
          puts("0");
        }
      return 0;
    }
  for(int i=1; i<=n; ++i)
    {
      d[i]=read();
      if(!d[i])
        {
          puts("0");
          return 0;
        }
      tot+=d[i];
    }
  if(tot!=2*n-2)
    {
      puts("0");
      return 0;
    }
  for(int i=2; i<=n; ++i)
    {
      int v=i;
      for(int j=2; j<=sqrt(i); ++j)
        {
          while(v%j==0)
            {
              v/=j;
              ++p[i][j];
            }
          if(v==1)
            {
              break;
            }
        }
      if(v!=1)
        {
          ++p[i][v];
        }
    }
  for(int i=2; i<=n; ++i)
    {
      for(int j=2; j<=i; ++j)
        {
          p[i][j]+=p[i-1][j];
        }
    }
  for(int j=2; j<=n-2; ++j)
    {
      ans[j]=p[n-2][j];
    }
  for(int i=1; i<=n; ++i)
    {
      for(int j=2; j<=d[i]-1; ++j)
        {
          ans[j]-=p[d[i]-1][j];
        }
    }
  long long r=1;
  for(int i=2; i<=n; ++i)
    {
      if(ans[i])
        {
          for(int j=1; j<=ans[i]; ++j)
            {
              r*=i;
            }
        }
    }
  printf("%lld\n",r);
  return 0;
}
