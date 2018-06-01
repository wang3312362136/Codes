#include <cstdio>

const int maxn=3000;
const int mo=1000000007;

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

int f[maxn+10],n,fac[maxn+10],bit[maxn*maxn+10],ifac[maxn+10];

int c(int a,int b)
{
  return 1ll*fac[a]*ifac[b]%mo*ifac[a-b]%mo;
}

int main()
{
  n=read();
  fac[0]=ifac[0]=fac[1]=ifac[1]=1;
  for(int i=2; i<=n; ++i)
    {
      fac[i]=(1ll*fac[i-1]*i)%mo;
      ifac[i]=(1ll*(mo-mo/i)*ifac[mo%i])%mo;
    }
  for(int i=1; i<=n; ++i)
    {
      ifac[i]=1ll*ifac[i-1]*ifac[i]%mo;
    }
  bit[0]=1;
  for(int i=1; i<=n*n; ++i)
    {
      bit[i]=((1ll*bit[i-1])<<1)%mo;
    }
  f[0]=1;
  for(int i=1; i<=n; ++i)
    {
      for(int j=1; j<=i; ++j)
        {
          f[i]=(f[i]+1ll*((j&1)?1:-1)*c(i,j)*bit[j*(i-j)]%mo*f[i-j]%mo)%mo;
        }
    }
  printf("%d\n",(f[n]+mo)%mo);
  return 0;
}
