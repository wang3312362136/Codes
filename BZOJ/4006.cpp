#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

const int maxn=1000;
const int maxm=6000;
const int maxp=10;
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

int pre[maxm+10],now[maxn+10],son[maxm+10],tot,val[maxm+10];
int f[maxn+10][(1<<maxp)+10],g[(1<<maxp)+10],bin[(1<<maxp)+10],n,m,p;
int vis[maxn+10],stand[maxp+2],tc;
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
  p=read();
  while(m--)
    {
      int u=read(),v=read(),w=read();
      ins(u,v,w);
      ins(v,u,w);
    }
  memset(f,63,sizeof f);
  for(int i=1; i<=p; ++i)
    {
      int c=read(),d=read();
      if(!stand[c])
        {
          stand[c]=++tc;
        }
      c=stand[c];
      f[d][1<<(i-1)]=0;
      bin[1<<(c-1)]|=1<<(i-1);
    }
  for(int sta=1; sta<1<<tc; ++sta)
    {
      bin[sta]=bin[sta&(sta-1)]|bin[sta&(-sta)];
    }
  for(int sta=1; sta<1<<p; ++sta)
    {
      for(int i=1; i<=n; ++i)
        {
          for(int s=sta&(sta-1); s; s=sta&(s-1))
            {
              f[i][sta]=std::min(f[i][sta],f[i][s]+f[i][sta^s]);
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
  for(int sta=1; sta<1<<tc; ++sta)
    {
      for(int j=1; j<=n; ++j)
        {
          g[bin[sta]]=std::min(g[bin[sta]],f[j][bin[sta]]);
        }
    }
  for(int sta=1; sta<1<<p; ++sta)
    {
      for(int s=sta&(sta-1); s; s=sta&(s-1))
        {
          g[sta]=std::min(g[sta],g[s]+g[sta^s]);
        }
    }
  printf("%d\n",g[(1<<p)-1]);
  return 0;
}
