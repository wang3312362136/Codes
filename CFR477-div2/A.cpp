#include <cstdio>

const int maxn=100;

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

int t[maxn+10],n,s;

int main()
{
  n=read();
  s=read()+1;
  for(register int i=1; i<=n; ++i)
    {
      int a=read(),b=read();
      t[i]=a*60+b;
    }
  if(t[1]>=s)
    {
      printf("%d %d\n",0,0);
      return 0;
    }
  for(register int i=2; i<=n; ++i)
    {
      if(t[i]-t[i-1]>=2*s)
        {
          printf("%d %d\n",(t[i-1]+s)/60,(t[i-1]+s)%60);
          return 0;
        }
    }
  printf("%d %d\n",(t[n]+s)/60,(t[n]+s)%60);
  return 0;
}
