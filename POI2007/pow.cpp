#include <cstdio>
#include <cmath>
#include <algorithm>
 
const int maxn=1000;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
 
int n,m,h[maxn+10][maxn+10],cnt,ans;
 
struct point
{
  int x,y;
 
  bool operator <(const point &other) const
  {
    return abs(h[x][y])<abs(h[other.x][other.y]);
  }
};
 
point city[maxn*maxn+10],full[maxn*maxn+10];
 
namespace dsu
{
  int fa[maxn*maxn+10],mark[maxn*maxn+10];
 
  int find(int x)
  {
    return fa[x]?(fa[x]=find(fa[x])):x;
  }
 
  inline int merge(int x,int y)
  {
    x=find(x);
    y=find(y);
    if(x==y)
      {
        return 0;
      }
    fa[x]=y;
    if(mark[x])
      {
        mark[y]=1;
      }
    return 0;
  }
}
 
inline int trans(int x,int y)
{
  return (x-1)*m+y;
}
 
int main()
{
  scanf("%d%d",&n,&m);
  for(register int i=1; i<=n; ++i)
    {
      for(register int j=1; j<=m; ++j)
        {
          scanf("%d",&h[i][j]);
          if(h[i][j]>0)
            {
              city[++cnt].x=i;
              city[cnt].y=j;
            }
          full[trans(i,j)].x=i;
          full[trans(i,j)].y=j;
        }
    }
  std::sort(city+1,city+cnt+1);
  std::sort(full+1,full+n*m+1);
  int now=1;
  for(register int i=1; i<=cnt; ++i)
    {
      int xx=city[i].x,yy=city[i].y;
      while((now<=n*m)&&(abs(h[full[now].x][full[now].y])<=abs(h[xx][yy])))
        {
          int x=full[now].x,y=full[now].y;
          for(register int j=0; j<4; ++j)
            {
              int nx=x+dx[j],ny=y+dy[j];
              if((nx<=0)||(nx>n)||(ny<=0)||(ny>m))
                {
                  continue;
                }
              if(abs(h[nx][ny])<=abs(h[xx][yy]))
                {
                  dsu::merge(trans(x,y),trans(nx,ny));
                }
            }
          ++now;
        }
      int fa=dsu::find(trans(xx,yy));
      if(!dsu::mark[fa])
        {
          dsu::mark[fa]=1;
          ++ans;
        }
    }
  printf("%d\n",ans);
  return 0;
}
