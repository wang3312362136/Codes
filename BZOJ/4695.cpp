#include <cstdio>
#include <algorithm>

const int maxn=500000;
const int inf=0x3f3f3f3f;

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

int n,a[maxn+10];

namespace smt
{
  struct node
  {
    int mx,mn,smx,smn,nmx,nmn,tmx,tmn,adt;
    long long sum;
  };

  node val[maxn<<2];

  inline int putadt(int x,int l,int r,int adv)
  {
    node* now=&val[x];
    now->mx+=adv;
    now->mn+=adv;
    if(now->smx!=-inf)
      {
        now->smx+=adv;
      }
    if(now->smn!=inf)
      {
        now->smn+=adv;
      }
    now->sum+=1ll*(r-l+1)*adv;
    now->adt+=adv;
    if(now->tmx!=inf)
      {
        now->tmx+=adv;
      }
    if(now->tmx!=-inf)
      {
        now->tmn+=adv;
      }
    return 0;
  }

  inline int puttmx(int x,int cval)
  {
    node* now=&val[x];
    now->sum-=1ll*(now->mx-cval)*now->nmx;
    now->mx=now->tmx=cval;
    if(cval<now->mn)
      {
        now->mn=cval;
      }
    if((now->smn!=inf)&&(cval<now->smn))
      {
        now->smn=cval;
      }
    if((now->tmn!=-inf)&&(now->tmn>cval))
      {
        now->tmn=cval;
      }
    return 0;
  }

  inline int puttmn(int x,int cval)
  {
    node* now=&val[x];
    now->sum+=1ll*(cval-now->mn)*now->nmn;
    now->mn=now->tmn=cval;
    if(cval>now->mx)
      {
        now->mx=cval;
      }
    if((now->smx!=-inf)&&(cval>now->smx))
      {
        now->smx=cval;
      }
    if((now->tmx!=inf)&&(now->tmx<cval))
      {
        now->tmx=cval;
      }
    return 0;
  }

  inline int pushdown(int x,int l,int r)
  {
    node* now=&val[x];
    node* ls=&val[x<<1];
    node* rs=&val[x<<1|1];
    int mid=(l+r)>>1;
    if(now->adt!=0)
      {
        putadt(x<<1,l,mid,now->adt);
        putadt(x<<1|1,mid+1,r,now->adt);
        now->adt=0;
      }
    if(now->tmx!=inf)
      {
        if(ls->mx>now->mx)
          {
            puttmx(x<<1,now->tmx);
          }
        if(rs->mx>now->mx)
          {
            puttmx(x<<1|1,now->tmx);
          }
        now->tmx=inf;
      }
    if(now->tmn!=-inf)
      {
        if(ls->mn<now->mn)
          {
            puttmn(x<<1,now->tmn);
          }
        if(rs->mn<now->mn)
          {
            puttmn(x<<1|1,now->tmn);
          }
        now->tmn=-inf;
      }
    return 0;
  }

  inline int updata(int x)
  {
    node* now=&val[x];
    node* ls=&val[x<<1];
    node* rs=&val[x<<1|1];
    now->mx=std::max(ls->mx,rs->mx);
    now->mn=std::min(ls->mn,rs->mn);
    now->smx=-inf;
    if(ls->mx!=now->mx)
      {
        now->smx=std::max(ls->mx,now->smx);
      }
    if(rs->mx!=now->mx)
      {
        now->smx=std::max(rs->mx,now->smx);
      }
    now->smx=std::max(now->smx,std::max(ls->smx,rs->smx));
    now->smn=inf;
    if(ls->mn!=now->mn)
      {
        now->smn=std::min(ls->mn,now->smn);
      }
    if(rs->mn!=now->mn)
      {
        now->smn=std::min(rs->mn,now->smn);
      }
    now->smn=std::min(now->smn,std::min(ls->smn,rs->smn));
    now->nmx=now->nmn=0;
    if(ls->mx==now->mx)
      {
        now->nmx+=ls->nmx;
      }
    if(rs->mx==now->mx)
      {
        now->nmx+=rs->nmx;
      }
    if(ls->mn==now->mn)
      {
        now->nmn+=ls->nmn;
      }
    if(rs->mn==now->mn)
      {
        now->nmn+=rs->nmn;
      }
    now->sum=ls->sum+rs->sum;
    return 0;
  }

  int build(int x,int l,int r)
  {
    node* now=&val[x];
    if(l==r)
      {
        now->mx=now->mn=now->sum=a[l];
        now->smx=now->tmn=-inf;
        now->smn=now->tmx=inf;
        now->nmx=now->nmn=1;
        now->adt=0;
        return 0;
      }
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    now->tmx=inf;
    now->tmn=-inf;
    updata(x);
    return 0;
  }

  int add(int x,int l,int r,int askl,int askr,int adv)
  {
    if((askl<=l)&&(r<=askr))
      {
        putadt(x,l,r,adv);
        return 0;
      }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    if(askl<=mid)
      {
        add(x<<1,l,mid,askl,askr,adv);
      }
    if(mid<askr)
      {
        add(x<<1|1,mid+1,r,askl,askr,adv);
      }
    updata(x);
    return 0;
  }

  long long getsum(int x,int l,int r,int askl,int askr)
  {
    if((askl<=l)&&(r<=askr))
      {
        return val[x].sum;
      }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    long long res=0;
    if(askl<=mid)
      {
        res+=getsum(x<<1,l,mid,askl,askr);
      }
    if(mid<askr)
      {
        res+=getsum(x<<1|1,mid+1,r,askl,askr);
      }
    return res;
  }

  int getmax(int x,int l,int r,int askl,int askr)
  {
    if((askl<=l)&&(r<=askr))
      {
        return val[x].mx;
      }
    pushdown(x,l,r);
    int mid=(l+r)>>1,res=-inf;
    if(askl<=mid)
      {
        res=std::max(res,getmax(x<<1,l,mid,askl,askr));
      }
    if(mid<askr)
      {
        res=std::max(res,getmax(x<<1|1,mid+1,r,askl,askr));
      }
    return res;
  }

  int getmin(int x,int l,int r,int askl,int askr)
  {
    if((askl<=l)&&(r<=askr))
      {
        return val[x].mn;
      }
    pushdown(x,l,r);
    int mid=(l+r)>>1,res=inf;
    if(askl<=mid)
      {
        res=std::min(res,getmin(x<<1,l,mid,askl,askr));
      }
    if(mid<askr)
      {
        res=std::min(res,getmin(x<<1|1,mid+1,r,askl,askr));
      }
    return res;
  }

  int changemax(int x,int l,int r,int askl,int askr,int cval)
  {
    int mid=(l+r)>>1;
    if((askl<=l)&&(r<=askr))
      {
        if(cval>=val[x].mx)
          {
            return 0;
          }
        else if(cval>val[x].smx)
          {
            puttmx(x,cval);
          }
        else
          {
            pushdown(x,l,r);
            changemax(x<<1,l,mid,askl,askr,cval);
            changemax(x<<1|1,mid+1,r,askl,askr,cval);
            updata(x);
          }
        return 0;
      }
    pushdown(x,l,r);
    if(askl<=mid)
      {
        changemax(x<<1,l,mid,askl,askr,cval);
      }
    if(mid<askr)
      {
        changemax(x<<1|1,mid+1,r,askl,askr,cval);
      }
    updata(x);
    return 0;
  }

  int changemin(int x,int l,int r,int askl,int askr,int cval)
  {
    int mid=(l+r)>>1;
    if((askl<=l)&&(r<=askr))
      {
        if(cval<=val[x].mn)
          {
            return 0;
          }
        else if(cval<val[x].smn)
          {
            puttmn(x,cval);
          }
        else
          {
            pushdown(x,l,r);
            changemin(x<<1,l,mid,askl,askr,cval);
            changemin(x<<1|1,mid+1,r,askl,askr,cval);
            updata(x);
          }
        return 0;
      }
    pushdown(x,l,r);
    if(askl<=mid)
      {
        changemin(x<<1,l,mid,askl,askr,cval);
      }
    if(mid<askr)
      {
        changemin(x<<1|1,mid+1,r,askl,askr,cval);
      }
    updata(x);
    return 0;
  }
}

int main()
{
  n=read();
  for(int i=1; i<=n; ++i)
    {
      a[i]=read();
    }
  smt::build(1,1,n);
  int m=read();
  while(m--)
    {
      int op=read(),l=read(),r=read(),x=0;
      if(op<=3)
        {
          x=read();
        }
      if(op==1)
        {
          smt::add(1,1,n,l,r,x);
        }
      else if(op==2)
        {
          smt::changemin(1,1,n,l,r,x);
        }
      else if(op==3)
        {
          smt::changemax(1,1,n,l,r,x);
        }
      else if(op==4)
        {
          printf("%lld\n",smt::getsum(1,1,n,l,r));
        }
      else if(op==5)
        {
          printf("%d\n",smt::getmax(1,1,n,l,r));
        }
      else
        {
          printf("%d\n",smt::getmin(1,1,n,l,r));
        }
    }
  return 0;
}
