#include <cstdio>

const int maxn=250000;

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

int n,ans,stack[maxn+10],head;

int main()
{
  n=read();
  while(n--)
    {
      int b=read(),a=read();
      while(head&&(stack[head]>a))
        {
          ++ans;
          --head;
        }
      while(head&&(stack[head]==a))
        {
          --head;
        }
      stack[++head]=a;
    }
  printf("%d\n",ans+head);
  return 0;
}
