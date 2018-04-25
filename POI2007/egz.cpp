#include <cstdio>
#include <vector>
#include <algorithm>
 
const int maxn=100000;
const int inf=0x3f3f3f3f;
 
typedef std::vector<int> vi;
typedef std::vector<int>::iterator viit;
 
int n,m,p,k,l[maxn+10],r[maxn+10],nowans,f[maxn+10];
vi gl[maxn+10],gr[maxn+10];
 
int main()
{
  scanf("%d%d%d%d",&n,&m,&k,&p);
  while(k--)
    {
      int a,b,c;
      scanf("%d%d%d",&a,&b,&c);
      if(c)
        {
          gl[a+1].push_back(b);
        }
      else
        {
          gr[a].push_back(b);
        }
    }
  gl[1].push_back(inf);
  gr[n].push_back(inf);
  for(register int i=1; i<=n; ++i)
    {
      std::sort(gl[i].begin(),gl[i].end());
      std::sort(gr[i].begin(),gr[i].end());
    }
  for(register int i=1; i<=n; ++i)
    {
      for(viit it=gl[i].begin(); it!=gl[i].end(); ++it)
        {
          if(!nowans)
            {
              f[++nowans]=-(*it);
            }
          else
            {
              int now=std::upper_bound(f+1,f+nowans+1,-(*it))-f;
              f[now]=-(*it);
              if(now>nowans)
                {
                  nowans=now;
                }
            }
        }
      l[i]=i-nowans;
    }
  nowans=0;
  for(register int i=n; i; --i)
    {
      for(viit it=gr[i].begin(); it!=gr[i].end(); ++it)
        {
          if(!nowans)
            {
              f[++nowans]=-(*it);
            }
          else
            {
              int now=std::upper_bound(f+1,f+nowans+1,-(*it))-f;
              f[now]=-(*it);
              if(now>nowans)
                {
                  nowans=now;
                }
            }
        }
      r[i]=n-i+1-nowans;
    }
  int now=1,ans=0,cnt=0;
  for(register int i=1; i<=n; ++i)
    {
      if(l[i]+r[i]==0)
        {
          ++cnt;
        }
      while((now<=n)&&(l[i]+r[now]>p))
        {
          ++now;
        }
      ans=std::max(ans,i-now+1);
    }
  printf("%d\n",ans-cnt);
  return 0;
}
