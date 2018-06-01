#include <cstdio>

const int maxn=200000;

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

int d[maxn+10],s[maxn+10],c[maxn+10],pos[maxn+10],v[maxn+10],n;
double ans;

int main()
{
  n=read();
  for(int i=1; i<=n; ++i)
    {
      d[read()]=i;
    }
  for(int i=1; i<=n; ++i)
    {
      pos[i]=d[read()];
    }
  for(int i=1; i<=n; ++i)
    {
      d[pos[i]]=i;
    }
  v[2]=1;
  c[2]=1;
  c[3]=-1;
  for(int i=2; i<=n; ++i)
    {
      if(pos[i-1]>pos[i])
        {
          v[i]=1;
          ++c[i];
          --c[i+1];
        }
    }
  for(int i=2; i<=n; ++i)
    {
      s[i]=s[i-1]+v[i];
    }
  for(int i=2; i<=n; ++i)
    {
      if((d[i-1]<d[i])&&(s[d[i]]-s[d[i-1]]))
        {
          ++c[d[i-1]+1];
          --c[d[i]+1];
        }
    }
  int t=0;
  ans=1;
  for(int i=2; i<=n; ++i)
    {
      t+=c[i];
      if(t)
        {
          ans+=v[i];
        }
      else
        {
          ans+=0.5;
        }
    }
  printf("%.3lf\n%.3lf\n%.3lf\n",ans-0.001,ans,ans+0.001);
  return 0;
}
