#include <cstdio>
 
const int maxn=250000;
 
namespace segment_tree
{
  int val[maxn<<2];
 
  inline int updata(int x)
  {
    return val[x]=val[x<<1]+val[x<<1|1];
  }
 
  int build(int now,int l,int r)
  {
    if(l==r)
      {
    val[now]=1;
        return 0;
      }
    int mid=(l+r)>>1;
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    updata(now);
    return 0;
  }
 
  int modify(int now,int l,int r,int pos)
  {
    if(l==r)
      {
        val[now]=0;
        return 0;
      }
    int mid=(l+r)>>1;
    if(pos<=mid)
      {
        modify(now<<1,l,mid,pos);
      }
    else
      {
        modify(now<<1|1,mid+1,r,pos);
      }
    updata(now);
    return 0;
  }
 
  int query(int now,int l,int r,int askl,int askr)
  {
    if((askl<=l)&&(r<=askr))
      {
        return val[now];
      }
    int res=0,mid=(l+r)>>1;
    if(askl<=mid)
      {
        res+=query(now<<1,l,mid,askl,askr);
      }
    if(mid<askr)
      {
        res+=query(now<<1|1,mid+1,r,askl,askr);
      }
    return res;
  }
};
 
int n,m,pre[(maxn<<1)+10],now[maxn+10],son[(maxn<<1)+10],tot;
int dfn[maxn+10],cnt,fa[maxn+10],top[maxn+10],w[maxn+10],size[maxn+10];
 
inline int ins(int a,int b)
{
  pre[++tot]=now[a];
  now[a]=tot;
  son[tot]=b;
  return 0;
}
 
int first_dfs(int u,int father)
{
  fa[u]=father;
  size[u]=1;
  w[u]=-1;
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if(v!=father)
        {
          first_dfs(v,u);
          size[u]+=size[v];
          if((w[u]==-1)||(size[v]>size[w[u]]))
            {
              w[u]=v;
           }
        }
      j=pre[j];
    }
  return 0;
}
 
int second_dfs(int u,int topfather)
{
  top[u]=topfather;
  dfn[u]=++cnt;
  if(w[u]!=-1)
    {
      second_dfs(w[u],topfather);
    }
  int j=now[u];
  while(j)
    {
      int v=son[j];
      if((v!=fa[u])&&(v!=w[u]))
        {
          second_dfs(v,v);
        }
      j=pre[j];
    }
  return 0;
}
 
inline int getans(int x)
{
  int ans=0;
  while(x)
    {
      ans+=segment_tree::query(1,1,n,dfn[top[x]],dfn[x]);
      x=fa[top[x]];
    }
  return ans;
}
 
int main()
{
  scanf("%d",&n);
  for(register int i=1; i<n; ++i)
    {
      int a,b;
      scanf("%d%d",&a,&b);
      ins(a,b);
      ins(b,a);
    }
  first_dfs(1,0);
  second_dfs(1,1);
  segment_tree::build(1,1,n);
  segment_tree::modify(1,1,n,1);
  scanf("%d",&m);
  for(register int i=1; i<n+m; ++i)
    {
      char s[10];
      int a,b;
      scanf("%s%d",s,&a);
      if(s[0]=='W')
        {
          printf("%d\n",getans(a));
        }
      else
        {
          scanf("%d",&b);
          if(fa[a]==b)
            {
              segment_tree::modify(1,1,n,dfn[a]);
            }
          else
            {
              segment_tree::modify(1,1,n,dfn[b]);
            }
        }
    }
  return 0;
}
