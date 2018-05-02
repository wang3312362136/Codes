#include <cstdio>

const int maxn=16;

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

int k,a[(1<<maxn)+10],t,xorsum,ans;

inline int deep(int x)
{
  int res=0;
  while(x)
    {
      ++res;
      x>>=1;
    }
  return res;
}

int main()
{
  t=read();
  while(t--)
    {
      k=read();
      xorsum=ans=0;
      for(register int i=1; i<1<<k; ++i)
        {
          a[i]=read();
          if(((k-deep(i))&1)==0)
            {
              xorsum^=a[i];
            }
        }
      if(k==1)
        {
          if(a[1])
            {
              puts("1");
            }
          else
            {
              puts("0");
            }
          continue;
        }
      if(!xorsum)
        {
          puts("0");
          continue;
        }
      for(register int i=1; i<1<<k; ++i)
        {
          if((((k-deep(i))&1)==0)&&((xorsum^a[i])<=a[i>>1]+a[i]))
            {
              if((k-deep(i))&&((xorsum^a[i])<a[i]))
                {
                  ans+=2;
                }
              else
                {
                  ++ans;
                }
            }
        }
      printf("%d\n",ans);
    }
  return 0;
}
