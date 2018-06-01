#include <cstdio>
#include <algorithm>

const int maxn=100000;
const int maxh=1000001;
const long long linf=0x3f3f3f3f3f3f3f3fll;

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

struct node
{
  int sum;
  long long t;
  node* ls;
  node* rs;
};

int n,nk,cnt;
node* root[maxn+10];
node anode[maxh*6];

inline int updata(node* x)
{
  x->sum=x->ls->sum+x->rs->sum;
  x->t=x->ls->t+x->rs->t;
  return 0;
}

int build(node* now,int l,int r)
{
  if(l==r)
    {
      now->sum=0;
      return 0;
    }
  int mid=(l+r)>>1;
  build(now->ls=&anode[++cnt],l,mid);
  build(now->rs=&anode[++cnt],mid+1,r);
  updata(now);
  return 0;
}

node* modify(node* now,int l,int r,int pos)
{
  if(l==r)
    {
      node* x=&anode[++cnt];
      x->sum=now->sum+1;
      x->t=now->t+l;
      return x;
    }
  int mid=(l+r)>>1;
  node* x=&anode[++cnt];
  if(pos<=mid)
    {
      x->ls=modify(now->ls,l,mid,pos);
      x->rs=now->rs;
    }
  else
    {
      x->ls=now->ls;
      x->rs=modify(now->rs,mid+1,r,pos);
    }
  updata(x);
  return x;
}

int query(node* a,node* b,int l,int r,int k)
{
  if(l==r)
    {
      return l;
    }
  int mid=(l+r)>>1,s=b->ls->sum-a->ls->sum;
  if(s>=k)
    {
      return query(a->ls,b->ls,l,mid,k);
    }
  else
    {
      return query(a->rs,b->rs,mid+1,r,k-s);
    }
}

long long getsum(node* a,node* b,int l,int r,int askl,int askr)
{
  if((askl<=l)&&(r<=askr))
    {
      return b->t-a->t;
    }
  int mid=(l+r)>>1;
  long long res=0;
  if(askl<=mid)
    {
      res+=getsum(a->ls,b->ls,l,mid,askl,askr);
    }
  if(mid<askr)
    {
      res+=getsum(a->rs,b->rs,mid+1,r,askl,askr);
    }
  return res;
}

int getnum(node* a,node* b,int l,int r,int askl,int askr)
{
  if((askl<=l)&&(r<=askr))
    {
      return b->sum-a->sum;
    }
  int mid=(l+r)>>1,res=0;
  if(askl<=mid)
    {
      res+=getnum(a->ls,b->ls,l,mid,askl,askr);
    }
  if(mid<askr)
    {
      res+=getnum(a->rs,b->rs,mid+1,r,askl,askr);
    }
  return res;
}

int main()
{
  n=read();
  nk=read();
  build(root[0]=&anode[++cnt],0,maxh);
  for(register int i=1; i<=n; ++i)
    {
      root[i]=modify(root[i-1],0,maxh,read());
    }
  long long ans=linf;
  for(register int i=1; i<=n-nk+1; ++i)
    {
      int m=query(root[i-1],root[i+nk-1],0,maxh,(nk+1)>>1);
      if(m==0)
        {
          ans=std::min(ans,getsum(root[i-1],root[i+nk-1],0,maxh,1,maxh)-1ll*getnum(root[i-1],root[i+nk-1],0,maxh,m+1,maxh)*m);
        }
      else
        {
          ans=std::min(ans,getsum(root[i-1],root[i+nk-1],0,maxh,m+1,maxh)-1ll*getnum(root[i-1],root[i+nk-1],0,maxh,m+1,maxh)*m+1ll*getnum(root[i-1],root[i+nk-1],0,maxh,0,m-1)*m-getsum(root[i-1],root[i+nk-1],0,maxh,0,m-1));
        }
    }
  printf("%lld\n",ans);
  return 0;
}
