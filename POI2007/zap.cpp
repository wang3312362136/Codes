#include <cstdio>
#include <algorithm>
 
const int maxn=50000;
 
int mu[maxn+10],p[maxn+10],prime[maxn+10];
int sum[maxn+10],t,a,b,d,tot;
 
int getmu()
{
  mu[1]=1;
  for(register int i=2; i<=maxn; ++i)
    {
      if(!p[i])
        {
          prime[++tot]=i;
          mu[i]=-1;
        }
      for(register int j=1; (j<=tot)&&(i*prime[j]<=maxn); ++j)
        {
          p[i*prime[j]]=1;
          if(i%prime[j]==0)
            {
              mu[i*prime[j]]=0;
              break;
            }
          mu[i*prime[j]]=-mu[i];
        }
    }
  for(register int i=1; i<=maxn; ++i)
    {
      sum[i]=sum[i-1]+mu[i];
    }
  return 0;
}
 
int main()
{
  getmu();
  scanf("%d",&t);
  while(t--)
    {
      scanf("%d%d%d",&a,&b,&d);
      a/=d;
      b/=d;
      long long ans=0;
      int x=std::min(a,b),pos;
      for(register int i=1; i<=x; i=pos+1)
        {
          pos=std::min(a/(a/i),b/(b/i));
          ans+=1ll*(sum[pos]-sum[i-1])*(a/i)*(b/i);
        }
      printf("%lld\n",ans);
    }
  return 0;
}
