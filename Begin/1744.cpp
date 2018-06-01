#include <cstdio>
#include <algorithm>

const int maxn=16000;
const int maxm=40000;

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

int dfn[maxn+10],low[maxn+10],n,m,belong[maxn+10],cnt,cntl;
int pre[maxm+10],now[maxn+10],son[maxm+10],tot;
int stack[maxn+10],top,instack[maxn+10],opp[maxn+10];

inline int ins(int a,int b)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  return 0;
}

int tarjan(int u)
{
  dfn[u]=low[u]=++cnt;
  stack[++top]=u;
  instack[u]=1;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(dfn[v]==0)
        {
          tarjan(v);
          low[u]=std::min(low[u],low[v]);
        }
      else if(instack[v])
        {
          low[u]=std::min(low[u],dfn[v]);
        }
      j=pre[j];
    }
  if(dfn[u]==low[u])
    {
      int w=0;
      ++cntl;
      while(w!=u)
        {
          w=stack[top--];
          belong[w]=cntl;
          instack[w]=0;
        }
    }
  return 0;
}

int main()
{
  n=read();
  m=read();
  for(int i=1; i<=n; ++i)
    {
      opp[i<<1]=(i<<1)-1;
      opp[(i<<1)-1]=i<<1;
    }
  while(m--)
    {
      int a=read(),b=read();
      ins(a,opp[b]);
      ins(b,opp[a]);
    }
  for(int i=1; i<=n<<1; ++i)
    {
      if(dfn[i]==0)
        {
          tarjan(i);
        }
    }
  for(int i=1; i<=n; ++i)
    {
      if(belong[i<<1]==belong[(i<<1)-1])
        {
          puts("NIE");
          return 0;
        }
    }
  puts("YES");
  return 0;
}
