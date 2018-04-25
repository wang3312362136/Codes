#include <cstdio>
 
int n;
long long ans;
 
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
 
int main()
{
  n=read();
  for(register int i=1; i<=n; ++i)
    {
      ans-=read();
      ans+=read();
    }
  for(register int i=1; i<=n; ++i)
    {
      ans+=read();
      ans-=read();
    }
  printf("%lld\n",ans);
  return 0;
}
