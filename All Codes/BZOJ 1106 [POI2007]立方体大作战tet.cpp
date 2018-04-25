#include <cstdio>

const int maxn=100000;

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

int n,a,ans,pre[maxn+10];

namespace tree_array
{
  int c[maxn+10];

  inline int lowbit(int x)
  {
    return x&(-x);
  }

  inline int add(int pos,int x)
  {
    while(pos<=n)
      {
        c[pos]+=x;
        pos+=lowbit(pos);
      }
    return 0;
  }

  inline int sum(int pos)
  {
    int res=0;
    while(pos)
      {
        res+=c[pos];
        pos-=lowbit(pos);
      }
    return res;
  }
}

int main()
{
  n=read()<<1;
  for(register int i=1; i<=n; ++i)
    {
      a=read();
      if(!pre[a])
        {
          pre[a]=i;
          tree_array::add(i,1);
        }
      else
        {
          ans+=tree_array::sum(i)-tree_array::sum(pre[a]-1)-1;
          tree_array::add(pre[a],-1);
        }
    }
  printf("%d\n",ans);
  return 0;
}
