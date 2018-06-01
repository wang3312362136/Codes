#include <cstdio>

const int maxn=100000;
const int maxd=2000000;

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

namespace dsu
{
  int fa[maxn+10];

  int find(int x)
  {
    return fa[x]?fa[x]=find(fa[x]):x;
  }

  inline int check(int x,int y)
  {
    return find(x)==find(y);
  }

  inline int merge(int x,int y)
  {
    x=find(x);
    y=find(y);
    if(x!=y)
      {
        fa[x]=y;
      }
    return 0;
  }
}

struct node
{
  node* son[2];
  int sum;
};

node tnode[maxd];
node* root[maxn+10];
int cnt_node,n,m,q,val[maxn+10],id[maxn+10];

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

int build(node* now,int l,int r,int v)
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
      build(now->son[0]=&tnode[++cnt_node],l,mid,v);
      now->son[1]=NULL;
    }
  else
    {
      build(now->son[1]=&tnode[++cnt_node],mid+1,r,v);
      now->son[0]=NULL;
    }
  updata(now);
  return 0;
}

node* merge(node* a,node* b)
{
  if(a==NULL)
    {
      return b;
    }
  if(b==NULL)
    {
      return a;
    }
  a->son[0]=merge(a->son[0],b->son[0]);
  a->son[1]=merge(a->son[1],b->son[1]);
  updata(a);
  return a;
}

int getkth(node* now,int l,int r,int k)
{
  if(l==r)
    {
      return l;
    }
  int mid=(l+r)>>1,v;
  if(now->son[0]==NULL)
    {
      v=0;
    }
  else
    {
      v=now->son[0]->sum;
    }
  if(k<=v)
    {
      return getkth(now->son[0],l,mid,k);
    }
  else
    {
      return getkth(now->son[1],mid+1,r,k-v);
    }
}

int main()
{
  n=read();
  m=read();
  for(int i=1; i<=n; ++i)
    {
      val[i]=read();
      id[val[i]]=i;
    }
  for(int i=1; i<=n; ++i)
    {
      build(root[i]=&tnode[++cnt_node],1,n,val[i]);
    }
  while(m--)
    {
      int a=read(),b=read();
      if(!dsu::check(a,b))
        {
          int x=dsu::find(a),y=dsu::find(b);
          dsu::merge(a,b);
          root[y]=merge(root[x],root[y]);
        }
    }
  q=read();
  while(q--)
    {
      char s[10];
      scanf("%s",s);
      int a=read(),b=read();
      if(s[0]=='Q')
        {
          int x=dsu::find(a);
          if(root[x]->sum<b)
            {
              puts("-1");
            }
          else
            {
              printf("%d\n",id[getkth(root[x],1,n,b)]);
            }
        }
      else
        {
          if(!dsu::check(a,b))
            {
              int x=dsu::find(a),y=dsu::find(b);
              dsu::merge(a,b);
              root[y]=merge(root[x],root[y]);
            }
        }
    }
  return 0;
}
