#include <cstdio>
#include <algorithm>

const int maxn=1000;
const int maxm=4000000;

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

int pre[maxm+10],now[maxn+10],son[maxm+10],tot;
int dfn[maxn+10],low[maxn+10],belong[maxn+10],cnt,cntl;
int stack[maxn+10],top,instack[maxn+10],n,m;

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
      ++cntl;
      int w=0;
      while(w!=u)
        {
          w=stack[top--];
          belong[w]=cntl;
          instack[w]=0;
        }
    }
  return 0;
}

int u[maxn+10],v[maxn+10];

int main()
{
  n=read();
  m=read();
  for(int i=1; i<=m; ++i)
    {
      u[i]=read();
      v[i]=read();
      if(u[i]>v[i])
        {
          std::swap(u[i],v[i]);
        }
    }
  for(int i=1; i<=m; ++i)
    {
      for(int j=1; j<=m; ++j)
        {
          if((u[i]<u[j])&&(v[i]<v[j])&&(v[i]>u[j]))
            {
              ins(i*2,j*2-1);
              ins(j*2-1,i*2);
              ins(i*2-1,j*2);
              ins(j*2,i*2-1);
            }
        }
    }
  for(int i=1; i<=2*m; ++i)
    {
      if(!dfn[i])
        {
          tarjan(i);
        }
    }
  for(int i=1; i<=m; ++i)
    {
      if(belong[2*i-1]==belong[2*i])
        {
          puts("the evil panda is lying again");
          return 0;
        }
    }
  puts("panda is telling the truth...");
  return 0;
}
