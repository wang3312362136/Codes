#include <cstdio>
#include <queue>
#include <cstring>

const int maxn=20000;
const int maxd=5;
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

int pre[maxn*2+10],now[maxn+10],son[maxn+10],tot,val[maxn*2+10],d,n,m;
int f[maxn+10][(1<<(maxd<<1))+10],g[(1<<maxd)+10],vis[maxn+10];
std::queue<int> q;

inline int ins(int a,int b,int c)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  val[tot]=c;
  return 0;
}

inline int spfa(int sta)
{
  while(!q.empty())
    {
      int u=q.front(),j=now[u];
      q.pop();
      while(j)
        {
          int v=son[j];
          if(f[v][sta]>f[u][sta]+val[j])
            {
              f[v][sta]=f[u][sta]+val[j];
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
  d=read();
  while(m--)
    {
      int u=read(),v=read(),w=read();
      ins(u,v,w);
      ins(v,u,w);
    }
  memset(f,63,sizeof f);
  for(int i=1; i<=d; ++i)
    {
      f[i][1<<(i-1)]=0;
      f[n-i+1][1<<(i-1+d)]=0;
    }
  for(int sta=1; sta<1<<(d<<1); ++sta)
    {
      for(int i=1; i<=n; ++i)
        {
          for(int s=sta&(sta-1); s; s=sta&(s-1))
            {
              if(f[i][sta]>f[i][s]+f[i][sta^s])
                {
                  f[i][sta]=f[i][s]+f[i][sta^s];
                }
            }
          if(f[i][sta]!=inf)
            {
              q.push(i);
              vis[i]=1;
            }
        }
      spfa(sta);
    }
  memset(g,63,sizeof g);
  for(int sta=1; sta<1<<d; ++sta)
    {
      for(int i=1; i<=n; ++i)
        {
          g[sta]=std::min(g[sta],f[i][sta+(sta<<d)]);
        }
    }
  for(int sta=1; sta<1<<d; ++sta)
    {
      for(int s=sta&(sta-1); s; s=sta&(s-1))
        {
          g[sta]=std::min(g[sta],g[s]+g[sta^s]);
        }
    }
  if(g[(1<<d)-1]==inf)
    {
      puts("-1");
      return 0;
    }
  printf("%d\n",g[(1<<d)-1]);
  return 0;
}
