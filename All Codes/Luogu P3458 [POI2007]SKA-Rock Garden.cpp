#include <cstdio>
#include <algorithm>

const int maxn=1000000;
const int inf=0x7f7f7f7f;

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

int x[maxn+10],y[maxn+10],n,lox=inf,loy=inf,hix,hiy,w[maxn+10],ans=inf;
int kind[maxn+10];

inline int judge(int nx,int ny,int lx,int ly,int hx,int hy)
{
  return ((lx<=nx)&&(nx<=hx)&&(ly<=ny)&&(ny<=hy));
}

int check(int lx,int ly,int hx,int hy)
{
  int ww=0,k[maxn+10];
  for(register int i=1; i<=n; ++i)
    {
      if(judge(x[i],y[i],lx,ly,hx,hy))
        {
          k[i]=0;
          continue;
        }
      if(judge(y[i],x[i],lx,ly,hx,hy))
        {
          ww+=w[i];
          k[i]=1;
        }
      else
        {
          return 0;
        }
    }
  if(ww<ans)
    {
      ans=ww;
      for(register int i=1; i<=n; ++i)
        {
          kind[i]=k[i];
        }
    }
  return 0;
}

int main()
{
  n=read();
  for(register int i=1; i<=n; ++i)
    {
      x[i]=read();
      y[i]=read();
      w[i]=read();
    }
  for(register int i=1; i<=n; ++i)
    {
      int nx=x[i],ny=y[i];
      if(nx>ny)
        {
          std::swap(nx,ny);
        }
      lox=std::min(lox,nx);
      hix=std::max(hix,nx);
      loy=std::min(loy,ny);
      hiy=std::max(hiy,ny);
    }
  check(lox,loy,hix,hiy);
  check(lox,loy,hiy,hix);
  check(loy,lox,hix,hiy);
  check(loy,lox,hiy,hix);
  printf("%lld %d\n",2*(1ll*hix-lox+hiy-loy),ans);
  for(register int i=1; i<=n; ++i)
    {
      printf("%d",kind[i]);
    }
  puts("");
  return 0;
}
