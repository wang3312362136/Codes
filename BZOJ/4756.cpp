#include <cstdio>
#include <algorithm>

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

struct node
{
  node* son[2];
  int sum;
};

int n,p[maxn+10],cnt_node,tmp[maxn+10],ans[maxn+10];
int pre[maxn+10],now[maxn+10],son[maxn+10],tot;
node tnode[maxd+10];
node* root[maxn+10];

int updata(node* now)
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
      now->sum=1;
      now->son[0]=now->son[1]=NULL;
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
      now->son[0]=NULL;
      build(now->son[1]=&tnode[++cnt_node],mid+1,r,v);
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
  a->son[0]=merge(a->son[0],b->son[0],l,mid);
  a->son[1]=merge(a->son[1],b->son[1],mid+1,r);
  updata(a);
  return a;
}

int getsum(node* now,int l,int r,int askl,int askr)
{
  if((askl<=l)&&(r<=askr))
    {
      return now->sum;
    }
  int mid=(l+r)>>1,res=0;
  if((askl<=mid)&&(now->son[0]!=NULL))
    {
      res+=getsum(now->son[0],l,mid,askl,askr);
    }
  if((mid<askr)&&(now->son[1]!=NULL))
    {
      res+=getsum(now->son[1],mid+1,r,askl,askr);
    }
  return res;
}

inline int ins(int a,int b)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  return 0;
}

int dfs(int u)
{
  int j=now[u];
  while(j)
    {
      int v=son[j];
      dfs(v);
      root[u]=merge(root[u],root[v],1,n);
      j=pre[j];
    }
  ans[u]=getsum(root[u],1,n,p[u]+1,n);
  return 0;
}

int main()
{
  n=read();
  for(int i=1; i<=n; ++i)
    {
      p[i]=tmp[i]=read();
    }
  std::sort(tmp+1,tmp+n+1);
  for(int i=1; i<=n; ++i)
    {
      p[i]=std::lower_bound(tmp+1,tmp+n+1,p[i])-tmp;
    }
  for(int i=1; i<=n; ++i)
    {
      build(root[i]=&tnode[++cnt_node],1,n,p[i]);
    }
  for(int i=2; i<=n; ++i)
    {
      int a=read();
      ins(a,i);
    }
  dfs(1);
  for(int i=1; i<=n; ++i)
    {
      printf("%d\n",ans[i]);
    }
  return 0;
}
