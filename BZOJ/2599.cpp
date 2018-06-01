#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn=200000;
const int maxk=1000000;
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
int f[maxn+10],size[maxn+10],vis[maxn+10],nowroot,nowsize,n,k;
int ans,bin[maxk+10],deep[maxn+10],cnt[maxn+10];

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
  f[u]=0;
  size[u]=1;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((!vis[v])&&(v!=fa))
        {
          getc(v,u);
          size[u]+=size[v];
          f[u]=std::max(f[u],size[v]);
        }
      j=pre[j];
    }
  f[u]=std::max(f[u],nowsize-size[u]);
  if(f[u]<f[nowroot])
    {
      nowroot=u;
    }
  return 0;
}

int getans(int u,int fa)
{
  if(deep[u]>k)
    {
      return 0;
    }
  ans=std::min(ans,bin[k-deep[u]]+cnt[u]);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa)&&(!vis[v]))
        {
          deep[v]=deep[u]+val[j];
          cnt[v]=cnt[u]+1;
          getans(v,u);
        }
      j=pre[j];
    }
  return 0;
}

int modans(int u,int fa)
{
  if(deep[u]>k)
    {
      return 0;
    }
  bin[deep[u]]=std::min(bin[deep[u]],cnt[u]);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa)&&(!vis[v]))
        {
          modans(v,u);
        }
      j=pre[j];
    }
  return 0;
}

int backans(int u,int fa)
{
  if(deep[u]>k)
    {
      return 0;
    }
  bin[deep[u]]=inf;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa)&&(!vis[v]))
        {
          backans(v,u);
        }
      j=pre[j];
    }
  return 0;
}

inline int calc(int u)
{
  bin[0]=0;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(!vis[v])
        {
          deep[v]=val[j];
          cnt[v]=1;
          getans(v,u);
          modans(v,u);
        }
      j=pre[j];
    }
  j=now[u];
  while(j)
    {
      int v=son[j];
      if(!vis[v])
        {
          backans(v,u);
        }
      j=pre[j];
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
          nowroot=0;
          nowsize=size[v];
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
  k=read();
  for(int i=1; i<n; ++i)
    {
      int a=read()+1,b=read()+1,c=read();
      ins(a,b,c);
      ins(b,a,c);
    }
  ans=inf;
  memset(bin,63,sizeof bin);
  f[0]=inf;
  nowroot=0;
  nowsize=n;
  getc(1,0);
  solve(nowroot);
  if(ans==inf)
    {
      puts("-1");
    }
  else
    {
      printf("%d\n",ans);
    }
  return 0;
}
