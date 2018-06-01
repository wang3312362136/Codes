#include <cstdio>
#include <queue>
#include <cstring>

const int maxn=20000;
const int maxm=400000;
const int maxk=21;
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

int n,m,k,pre[maxm+10],now[maxn+10],son[maxm+10],tot,val[maxm+10];
int dist[maxk+2][maxn+10],f[(1<<maxk)+10][maxk+2],vis[maxn+10],t;
int from[maxk+2];
std::queue<int> q;

inline int ins(int a,int b,int c)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  val[tot]=c;
  return 0;
}

inline int spfa(int s)
{
  int* d=dist[s];
  d[s]=0;
  q.push(s);
  vis[s]=1;
  while(!q.empty())
    {
      int u=q.front(),j=now[u];
      q.pop();
      while(j)
        {
          int v=son[j];
          if(d[v]>d[u]+val[j])
            {
              d[v]=d[u]+val[j];
              if(!vis[v])
                {
                  vis[v]=1;
                  q.push(v);
                }
            }
          j=pre[j];
        }
      vis[u]=0;
    }
  return 0;
}

int main()
{
  n=read();
  m=read();
  k=read();
  while(m--)
    {
      int a=read(),b=read(),c=read();
      ins(a,b,c);
      ins(b,a,c);
    }
  t=read();
  for(int i=1; i<=t; ++i)
    {
      int a=read(),b=read();
      from[b]|=1<<(a-1);
    }
  for(int i=2; i<=k+1; ++i)
    {
      from[i]|=1;
    }
  memset(dist,63,sizeof dist);
  memset(f,63,sizeof f);
  for(int i=1; i<=k+1; ++i)
    {
      spfa(i);
      f[1<<(i-1)][i]=0;
    }
  for(int sta=1; sta<1<<(k+1); ++sta)
    {
      int flag=0;
      for(int i=2; i<=k+1; ++i)
        {
          if((((1<<(i-1))&sta)==(1<<(i-1)))&&((sta^from[i])!=(sta-from[i])))
            {
              flag=1;
              break;
            }
        }
      if(flag)
        {
          continue;
        }
      for(int i=1; i<=k+1; ++i)
        {
          if(sta&(1<<(i-1)))
            {
              int s=sta^(1<<(i-1));
              flag=0;
              for(int j=2; j<=k+1; ++j)
                {
                  if((((1<<(j-1))&s)==(1<<(j-1)))&&((s^from[j])!=(s-from[j])))
                    {
                      flag=1;
                      break;
                    }
                }
              if(flag)
                {
                  continue;
                }
              for(int j=1; j<=k+1; ++j)
                {
                  if(s&(1<<(j-1)))
                    {
                      f[sta][i]=std::min(f[sta][i],f[s][j]+dist[j][i]);
                    }
                }
            }
        }
    }
  int ans=inf;
  for(int i=1; i<=k+1; ++i)
    {
      ans=std::min(ans,f[(1<<(k+1))-1][i]+dist[i][n]);
    }
  printf("%d\n",ans);
  return 0;
}
