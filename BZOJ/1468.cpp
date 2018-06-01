#include <cstdio>
#include <algorithm>

const int maxn=40000;
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
int vis[maxn+10],f[maxn+10],nowsize,nowroot,size[maxn+10],ans,n,m,k,tmp[maxn+10],cnt,deep[maxn+10];

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
  f[u]=0;
  size[u]=1;
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

int calc(int u,int ud)
{
  deep[u]=ud;
  cnt=0;
  getdeep(u,0);
  std::sort(tmp+1,tmp+cnt+1);
  int res=0,l=0,r=cnt;
  while(l<r)
    {
      ++l;
      while((tmp[r]+tmp[l]>k)&&(l<r))
        {
          --r;
        }
      res+=r-l;
    }
  return res;
}

int search(int u)
{
  vis[u]=1;
  ans+=calc(u,0);
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(!vis[v])
        {
          ans-=calc(v,val[j]);
          nowsize=size[v];
          nowroot=0;
          getc(v,0);
          search(nowroot);
        }
      j=pre[j];
    }
  return 0;
}

int main()
{
  n=read();
  for(int i=1; i<n; ++i)
    {
      int a=read(),b=read(),c=read();
      ins(a,b,c);
      ins(b,a,c);
    }
  k=read();
  f[0]=inf;
  nowsize=n;
  getc(1,0);
  search(nowroot);
  printf("%d\n",ans);
  return 0;
}
