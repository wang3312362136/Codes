#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn=1000;
const int maxd=100000;

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

int n,d[maxn+10],p[maxn+10][maxn+10],ans[maxn+10];
int bignum[maxd+10],hi,tot,cnt,sum;

inline int times(int v)
{
  int r=0;
  for(int i=1; i<=hi; ++i)
    {
      bignum[i]=bignum[i]*v+r;
      r=bignum[i]/10;
      bignum[i]%=10;
    }
  while(r)
    {
      bignum[++hi]=r%10;
      r/=10;
    }
  return 0;
}

int main()
{
  n=read();
  if(n==1)
    {
      int x=read();
      if(x<=0)
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
      else if(d[i]==-1)
        {
          tot=-1;
        }
      else
        {
          if(tot!=-1)
            {
              tot+=d[i];
            }
          sum+=d[i]-1;
          ++cnt;
        }
    }
  if((tot!=-1)&&(tot!=2*n-2))
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
  for(int i=2; i<=n-2; ++i)
    {
      ans[i]=p[n-2][i]-p[n-2-sum][i];
    }
  for(int i=1; i<=n; ++i)
    {
      if(d[i]==-1)
        {
          continue;
        }
      for(int j=2; j<=d[i]-1; ++j)
        {
          ans[j]-=p[d[i]-1][j];
        }
    }
  hi=1;
  bignum[1]=1;
  for(int i=2; i<=n; ++i)
    {
      for(int j=1; j<=ans[i]; ++j)
        {
          times(i);
        }
    }
  for(int i=1; i<=n-2-sum; ++i)
    {
      times(n-cnt);
    }
  for(int i=hi; i; --i)
    {
      printf("%d",bignum[i]);
    }
  puts("");
  return 0;
}
