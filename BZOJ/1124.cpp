#include <cstdio>
#include <stack>
#include <cstring>

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

int n,to[maxn+10],vis[maxn+10],ru[maxn+10],minans,maxans,q[maxn+10],fake[maxn+10];

int main()
{
  n=read();
  for(int i=1; i<=n; ++i)
    {
      to[i]=read();
      ++ru[to[i]];
    }
  for(int i=1; i<=n; ++i)
    {
      if(!ru[i])
        {
          q[++minans]=i;
          ++maxans;
        }
    }
  for(int i=1; i<=minans; ++i)
    {
      vis[q[i]]=1;
      int x=to[q[i]];
      if(vis[x])
        {
          continue;
        }
      vis[x]=1;
      fake[to[x]]=1;
      --ru[to[x]];
      if(!ru[to[x]])
        {
          q[++minans]=to[x];
        }
    }
  for(int i=1; i<=n; ++i)
    {
      if(!vis[i])
        {
          int len=0,now=i,flag=0;
          while(!vis[now])
            {
              ++len;
              vis[now]=1;
              flag|=fake[now];
              now=to[now];
            }
          if((len!=1)&&(!flag))
            {
              ++maxans;
            }
          minans+=len/2;
        }
    }
  printf("%d %d\n",n-minans,n-maxans);
  return 0;
}
