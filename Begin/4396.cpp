#include <cstdio>
#include <algorithm>

const int maxn=100000;
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
    int mn,mx,adt;
    long long sum;
  };

  node val[maxn<<2];

  inline int putadt(int x,int l,int r,int v)
  {
    node* now=&val[x];
    now->sum+=1ll*(r-l+1)*v;
    now->mn+=v;
    now->mx+=v;
    now->adt+=v;
    return 0;
  }

  inline int pushdown(int x,int l,int r)
  {
    int mid=(l+r)>>1;
    if(val[x].adt)
      {
        putadt(x<<1,l,mid,val[x].adt);
        putadt(x<<1|1,mid+1,r,val[x].adt);
        val[x].adt=0;
      }
    return 0;
  }

  inline int updata(int x)
  {
    node* now=&val[x];
    node* ls=&val[x<<1];
    node* rs=&val[x<<1|1];
    now->sum=ls->sum+rs->sum;
    now->mn=std::min(ls->mn,rs->mn);
    now->mx=std::max(ls->mx,rs->mx);
    return 0;
  }

  int build(int x,int l,int r)
  {
    node* now=&val[x];
    if(l==r)
      {
        now->sum=now->mx=now->mn=a[l];
        now->adt=0;
        return 0;
      }
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
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

  int div(int x,int l,int r,int askl,int askr,int dv)
  {
    node* now=&val[x];
    int mid=(l+r)>>1;
    if((askl<=l)&&(r<=askr))
      {
        int mnd=now->mn/dv-now->mn;
        if((now->mn<0)&&(now->mn%dv))
          {
            --mnd;
          }
        int mxd=now->mx/dv-now->mx;
        if((now->mx<0)&&(now->mx%dv))
          {
            --mxd;
          }
        if(mnd==mxd)
          {
            putadt(x,l,r,mnd);
          }
        else
          {
            pushdown(x,l,r);
            div(x<<1,l,mid,askl,askr,dv);
            div(x<<1|1,mid+1,r,askl,askr,dv);
            updata(x);
          }
        return 0;
      }
    pushdown(x,l,r);
    if(askl<=mid)
      {
        div(x<<1,l,mid,askl,askr,dv);
      }
    if(mid<askr)
      {
        div(x<<1|1,mid+1,r,askl,askr,dv);
      }
    updata(x);
    return 0;
  }
}

int main()
{
  n=read();
  int m=read();
  for(int i=1; i<=n; ++i)
    {
      a[i]=read();
    }
  smt::build(1,1,n);
  while(m--)
    {
      int op=read(),aa=read(),b=read(),c;
      if(op==1)
        {
          c=read();
          smt::add(1,1,n,aa,b,c);
        }
      else if(op==2)
        {
          c=read();
          smt::div(1,1,n,aa,b,c);
        }
      else if(op==3)
        {
          printf("%d\n",smt::getmin(1,1,n,aa,b));
        }
      else
        {
          printf("%lld\n",smt::getsum(1,1,n,aa,b));
        }
    }
  return 0;
}
