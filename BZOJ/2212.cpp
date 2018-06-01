#include <cstdio>
#include <algorithm>

const int maxn=400000;
const int maxd=4000000;

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
  node* son[2];
  int sum;
};

node* root[maxn+10];
node tnode[maxd+10];
int ls[maxn+10],rs[maxn+10],tot,n,cnt,val[maxn+10],num,fa[maxn+10];
long long ans,na,nb;

inline int updata(node* now)
{
  now->sum=0;
  if(now->son[0]!=NULL)
    {
      now->sum+=now->son[0]->sum;
    }
  if(now->son[1]!=NULL)
    {
      now->sum+=now->son[1]->sum;
    }
  return 0;
}

node* build(node* now,int l,int r,int v)
{
  if(l==r)
    {
      now->son[0]=now->son[1]=NULL;
      now->sum=1;
      return 0;
    }
  int mid=(l+r)>>1;
  if(v<=mid)
    {
      build(now->son[0]=&tnode[++cnt],l,mid,v);
      now->son[1]=NULL;
    }
  else
    {
      now->son[0]=NULL;
      build(now->son[1]=&tnode[++cnt],mid+1,r,v);
    }
  updata(now);
  return 0;
}

node* merge(node* a,node* b,int l,int r)
{
  if(a==NULL)
    {
      return b;
    }
  if(b==NULL)
    {
      return a;
    }
  int mid=(l+r)>>1;
  if((a->son[1]!=NULL)&&(b->son[0]!=NULL))
    {
      na+=1ll*a->son[1]->sum*b->son[0]->sum;
    }
  if((a->son[0]!=NULL)&&(b->son[1]!=NULL))
    {
      nb+=1ll*a->son[0]->sum*b->son[1]->sum;
    }
  a->son[0]=merge(a->son[0],b->son[0],l,mid);
  a->son[1]=merge(a->son[1],b->son[1],mid+1,r);
  updata(a);
  return a;
}

inline int ins(int a,int b)
{
  if(ls[a]!=0)
    {
      rs[a]=b;
    }
  else
    {
      ls[a]=b;
    }
  fa[b]=a;
  return 0;
}

int search(int u)
{
  if(ls[u]!=0)
    {
      search(ls[u]);
      search(rs[u]);
      na=nb=0;
      root[u]=merge(root[ls[u]],root[rs[u]],1,n);
      ans+=std::min(na,nb);
    }
  return 0;
}

int main()
{
  n=read();
  int w=0,now=0;
  while(w<n)
    {
      val[++num]=read();
      if(num>1)
        {
          while(rs[now])
            {
              now=fa[now];
            }
          ins(now,num);
        }
      if(val[num])
        {
          ++w;
        }
      else
        {
          now=num;
        }
    }
  for(int i=1; i<=num; ++i)
    {
      if(val[i])
        {
          build(root[i]=&tnode[++cnt],1,n,val[i]);
        }
    }
  search(1);
  printf("%lld\n",ans);
  return 0;
}
