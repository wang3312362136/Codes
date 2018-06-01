#include <cstdio>
#include <cstring>
#include <algorithm>

#define sqr(x) (1ll*(x)*(x))

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

int x[maxn+10],y[maxn+10],t,n,p[maxn*4+10];
long long a[maxn*4+10];

inline long long length(int i,int j)
{
  return sqr(x[i]-x[j])+sqr(y[i]-y[j]);
}

inline long long cp(int o,int i,int j)
{
  int xi=x[i]-x[o],yi=y[i]-y[o],xj=x[j]-x[o],yj=y[j]-y[o];
  return 1ll*xj*yi-1ll*yj*xi;
}

int main()
{
  t=read();
  while(t--)
    {
      n=read();
      memset(a,0,sizeof a);
      for(int i=1; i<=n; ++i)
        {
          x[i]=read();
          y[i]=read();
        }
      for(int i=1; i<n; ++i)
        {
          a[i*2]=a[i*2+n*2]=length(i,i+1);
        }
      a[n*2]=a[n*4]=length(n,1);
      a[1]=a[n*2+1]=cp(1,n,2);
      for(int i=2; i<n; ++i)
        {
          a[i*2-1]=a[i*2-1+n*2]=cp(i,i-1,i+1);
        }
      a[n*2-1]=a[n*4-1]=cp(n,n-1,1);
      a[0]=a[n*4+1]=inf;
      int id=1,rmax=1,ans=0;
      p[1]=1;
      for(int i=2; i<=n*4; ++i)
        {
          if(i<=rmax)
            {
              p[i]=std::min(p[id*2-i],rmax-i);
            }
          else
            {
              p[i]=1;
            }
          while(a[i+p[i]]==a[i-p[i]])
            {
              ++p[i];
            }
          if(rmax<i+p[i]-1)
            {
              rmax=i+p[i]-1;
              id=i;
            }
          if(p[i]>=n)
            {
              ++ans;
            }
        }
      printf("%d\n",ans/2);
    }
  return 0;
}
