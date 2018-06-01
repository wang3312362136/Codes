#include <cstdio>

const int maxn=1000000;

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

long long f[maxn+10];
int pre[maxn*2+10],now[maxn+10],son[maxn*2+10],tot,n,size[maxn+10];

inline int ins(int a,int b)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  return 0;
}

long long search(int u,int fa)
{
  long long res=1;
  size[u]=1;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(v!=fa)
        {
          long long pps=search(v,u);
          size[u]+=size[v];
          res+=pps+size[v];
        }
      j=pre[j];
    }
  return res;
}

int dp(int u,int fa)
{
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(v!=fa)
        {
          f[v]=f[u]-size[v]+n-size[v];
          dp(v,u);
        }
      j=pre[j];
    }
  return 0;
}

int main()
{
  n=read();
  for(register int i=1; i<n; ++i)
    {
      int u=read(),v=read();
      ins(u,v);
      ins(v,u);
    }
  f[1]=search(1,0);
  dp(1,0);
  int pos=-1;
  long long val=0;
  for(register int i=1; i<=n; ++i)
    {
      if(f[i]>val)
        {
          val=f[i];
          pos=i;
        }
    }
  printf("%d\n",pos);
  return 0;
}
