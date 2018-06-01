#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn=10000;
const int maxp=100;
const int maxv=1000000;
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
int vis[maxn+10],f[maxn+10],size[maxn+10],n,p,bin[maxv+10];
int q[maxn+10],ans[maxn+10],nowroot,nowsize,cnt,tmp[maxn+10],flag,deep[maxn+10];

int ins(int a,int b,int c)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  val[tot]=c;
  return 0;
}

int getc(int u,int fa)
{
  size[u]=1;
  f[u]=0;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa)&&(!vis[v]))
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

int getdeep(int u,int fa)
{
  if(deep[u]>maxv)
    {
      return 0;
    }
  tmp[++cnt]=deep[u];
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa)&&(!vis[v]))
        {
          deep[v]=deep[u]+val[j];
          getdeep(v,u);
        }
      j=pre[j];
    }
  return 0;
}

int calc(int u,int ud,int op)
{
  deep[u]=ud;
  cnt=0;
  getdeep(u,0);
  for(int i=1; i<=cnt; ++i)
    {
      ++bin[tmp[i]];
    }
  for(int k=1; k<=p; ++k)
    {
      int nq=q[k],res=0;
      for(int i=1; i<=cnt; ++i)
        {
          if(nq>=tmp[i])
            {
              res+=bin[nq-tmp[i]];
              if(nq==(tmp[i]<<1))
                {
                  ++res;
                }
            }
        }
      ans[k]+=op*(res>>1);
    }
  for(int i=1; i<=cnt; ++i)
    {
      --bin[tmp[i]];
    }
  return 0;
}

int solve(int u)
{
  vis[u]=1;
  calc(u,0,1);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(!vis[v])
        {
          calc(v,val[j],-1);
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
  p=read();
  for(int i=1; i<n; ++i)
    {
      int a=read(),b=read(),c=read();
      ins(a,b,c);
      ins(b,a,c);
    }
  f[0]=inf;
  for(int i=1; i<=p; ++i)
    {
      q[i]=read();
    }
  flag=0;
  nowsize=n;
  nowroot=0;
  getc(1,0);
  solve(nowroot);
  for(int i=1; i<=p; ++i)
    {
      if((q[i]==0)||(ans[i]>0))
        {
          puts("Yes");
        }
      else
        {
          puts("No");
        }
    }
  return 0;
}
