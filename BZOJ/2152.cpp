#include <cstdio>
#include <algorithm>

const int maxn=20000;
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
int n,nowroot,nowsize,size[maxn+10],f[maxn+10],vis[maxn+10];
int cnt[3],ans,deep[maxn+10];

inline int ins(int a,int b,int c)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  val[tot]=c;
  return 0;
}

int gcd(int a,int b)
{
  return b==0?a:gcd(b,a%b);
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
  ++cnt[deep[u]%3];
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

inline int calc(int u,int ud)
{
  deep[u]=ud;
  cnt[0]=cnt[1]=cnt[2]=0;
  getdeep(u,0);
  return cnt[0]*cnt[0]+2*cnt[1]*cnt[2];
}

int solve(int u)
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
  for(int i=1; i<n; ++i)
    {
      int a=read(),b=read(),c=read();
      ins(a,b,c);
      ins(b,a,c);
    }
  f[0]=inf;
  nowsize=n;
  nowroot=0;
  getc(1,0);
  solve(nowroot);
  int t=n*n,g=gcd(t,ans);
  if(ans==0)
    {
      puts("0/1");
    }
  else
    {
      printf("%d/%d\n",ans/g,t/g);
    }
  return 0;
}
