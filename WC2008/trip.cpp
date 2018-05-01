#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

typedef std::pair<int,int> pii;
typedef std::pair<pii,int> piii;

const int maxk=10;
const int maxn=100;
const int maxm=20000;
const int inf=0x3f3f3f3f;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

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

int a[maxk+2][maxk+2],f[maxk+2][maxk+2][(1<<maxk)+10],n,m,vis[maxk+2][maxk+2],tot;
piii pre[maxk+2][maxk+2][(1<<maxk)+10];
std::queue<pii> q;

inline int spfa(int sta)
{
  while(!q.empty())
    {
      pii u=q.front();
      q.pop();
      for(int i=0; i<4; ++i)
        {
          int nx=u.first+dx[i],ny=u.second+dy[i];
          if((nx<=0)||(nx>n)||(ny<=0)||(ny>m))
            {
              continue;
            }
          if(f[nx][ny][sta]>f[u.first][u.second][sta]+a[nx][ny])
            {
              f[nx][ny][sta]=f[u.first][u.second][sta]+a[nx][ny];
              pre[nx][ny][sta]=std::make_pair(u,sta);
              if(!vis[nx][ny])
                {
                  vis[nx][ny]=1;
                  q.push(std::make_pair(nx,ny));
                }
            }
        }
      vis[u.first][u.second]=0;
    }
  return 0;
}

int search(int x,int y,int sta)
{
  if(f[x][y][sta]==inf)
    {
      return 0;
    }
  vis[x][y]=1;
  piii tmp=pre[x][y][sta];
  search(tmp.first.first,tmp.first.second,tmp.second);
  if((tmp.first.first==x)&&(tmp.first.second==y))
    {
      search(tmp.first.first,tmp.first.second,sta-tmp.second);
    }
  return 0;
}

int main()
{
  n=read();
  m=read();
  memset(f,63,sizeof f);
  for(int i=1; i<=n; ++i)
    {
      for(int j=1; j<=m; ++j)
        {
          a[i][j]=read();
          if(!a[i][j])
            {
              f[i][j][1<<(tot++)]=0;
            }
        }
    }
  for(int sta=1; sta<1<<tot; ++sta)
    {
      for(int i=1; i<=n; ++i)
        {
          for(int j=1; j<=m; ++j)
            {
              for(int s=sta&(sta-1); s; s=sta&(s-1))
                {
                  if(f[i][j][sta]>f[i][j][s]+f[i][j][sta-s]-a[i][j])
                    {
                      f[i][j][sta]=f[i][j][s]+f[i][j][sta-s]-a[i][j];
                      pre[i][j][sta]=std::make_pair(std::make_pair(i,j),s);
                    }
                }
              if(f[i][j][sta]!=inf)
                {
                  q.push(std::make_pair(i,j));
                  vis[i][j]=1;
                }
            }
        }
      spfa(sta);
    }
  int mx=0,my=0;
  for(int i=1; i<=n; ++i)
    {
      for(int j=1; j<=m; ++j)
        {
          if(!a[i][j])
            {
              mx=i;
              my=j;
              break;
            }
        }
    }
  printf("%d\n",f[mx][my][(1<<tot)-1]);
  search(mx,my,(1<<tot)-1);
  for(int i=1; i<=n; ++i)
    {
      for(int j=1; j<=m; ++j)
        {
          if(!a[i][j])
            {
              putchar('x');
            }
          else if(vis[i][j])
            {
              putchar('o');
            }
          else
            {
              putchar('_');
            }
        }
      putchar('\n');
    }
  return 0;
}
