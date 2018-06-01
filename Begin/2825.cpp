#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int maxn=200000;
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

int pre[maxn*2+10],now[maxn+10],son[maxn*2+10],tot,val[maxn*2+10];
int ms[maxn+10],size[maxn+10],f[maxn+10],g[maxn+10],vis[maxn+10];
int n,t,m,nowsize,nowroot,deep[maxn+10],len,ans,mxl;
int color[maxn+10],tmp[maxn+10],p[maxn+10];
std::vector<int> bin[maxn+10];

inline int ins(int a,int b,int c)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  val[tot]=c;
  return 0;
}

int getc(int u,int fa)
{
  ms[u]=0;
  size[u]=1;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((!vis[v])&&(v!=fa))
        {
          getc(v,u);
          size[u]+=size[v];
          ms[u]=std::max(ms[u],size[v]);
        }
      j=pre[j];
    }
  ms[u]=std::max(ms[u],nowsize-size[u]);
  if(ms[u]<ms[nowroot])
    {
      nowroot=u;
    }
  return 0;
}

int getblack(int u,int fa)
{
  len+=color[u];
  mxl=std::max(mxl,len);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((!vis[v])&&(v!=fa))
        {
          getblack(v,u);
        }
      j=pre[j];
    }
  len-=color[u];
  return 0;
}

int getf(int u,int fa)
{
  len+=color[u];
  f[len]=std::max(f[len],mxl);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa)&&(!vis[v]))
        {
          mxl+=val[j];
          getf(v,u);
          mxl-=val[j];
        }
      j=pre[j];
    }
  len-=color[u];
  return 0;
}

inline int calc(int u)
{
  int mxg=0;
  for(int i=0; i<=nowsize; ++i)
    {
      bin[i].clear();
    }
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(!vis[v])
        {
          len=mxl=0;
          getblack(v,u);
          bin[mxl].push_back(v);
          p[v]=val[j];
        }
      j=pre[j];
    }
  for(int i=0; i<=nowsize; ++i)
    {
      int sv=bin[i].size();
      for(int j=0; j<sv; ++j)
        {
          mxl=p[bin[i][j]];
          len=color[u];
          getf(bin[i][j],u);
          for(int k=1; k<=i+color[u]; ++k)
            {
              if(k-color[u]<=t)
                {
                  ans=std::max(ans,f[k]+std::max(g[t-k+color[u]],mxg));
                }
              f[k]=std::max(f[k],f[k-1]);
            }
          for(int k=1; k<=i+color[u]; ++k)
            {
              g[k]=std::max(g[k],f[k]);
              mxg=std::max(mxg,g[k]);
              f[k]=0;
            }
          if(t+color[u]>=0)
            {
              ans=std::max(ans,f[0]+std::max(g[t+color[u]],mxg));
            }
          g[0]=std::max(g[0],f[0]);
          f[0]=0;
        }
    }
  for(int i=0; i<=nowsize; ++i)
    {
      g[i]=0;
    }
  return 0;
}

int solve(int u)
{
  vis[u]=1;
  calc(u);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(!vis[v])
        {
          nowsize=size[v];
          nowroot=0;
          getc(v,0);
          solve(nowroot);
        }
      j=pre[j];
    }
  return 0;
}

int main()
{
  n=read();
  t=read();
  m=read();
  for(int i=1; i<=m; ++i)
    {
      color[read()]=1;
    }
  for(int i=1; i<n; ++i)
    {
      int a=read(),b=read(),c=read();
      ins(a,b,c);
      ins(b,a,c);
    }
  ms[0]=inf;
  nowroot=0;
  nowsize=n;
  getc(1,0);
  solve(nowroot);
  printf("%d\n",ans);
  return 0;
}
