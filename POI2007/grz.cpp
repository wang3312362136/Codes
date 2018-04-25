#include <cstdio>
#include <cstring>

const int maxn=1000;
const int dx[]={1,1,1,0,0,-1,-1,-1};
const int dy[]={1,0,-1,1,-1,1,0,-1};

int n,h[maxn+10][maxn+10],vis[maxn+10][maxn+10],hi,lo;

int search_lo(int x,int y)
{
  vis[x][y]=1;
  int flag=1;
  for(register int i=0; i<8; ++i)
    {
      int nx=x+dx[i],ny=y+dy[i];
      if((nx<=0)||(nx>n)||(ny<=0)||(ny>n))
        {
          continue;
        }
      if(h[nx][ny]<h[x][y])
        {
          flag=0;
          break;
        }
      if((h[nx][ny]==h[x][y])&&(vis[nx][ny]==-1))
        {
          flag=0;
          break;
        }
    }
  if(!flag)
    {
      vis[x][y]=-1;
      return 0;
    }
  for(register int i=0; i<8; ++i)
    {
      int nx=x+dx[i],ny=y+dy[i];
      if((nx<=0)||(nx>n)||(ny<=0)||(ny>n))
        {
          continue;
        }
      if((h[nx][ny]==h[x][y])&&(!vis[nx][ny]))
        {
          if(!search_lo(nx,ny))
            {
              vis[x][y]=-1;
              return 0;
            }
        }
    }
  return 1;
}

int search_hi(int x,int y)
{
  vis[x][y]=1;
  int flag=1;
  for(register int i=0; i<8; ++i)
    {
      int nx=x+dx[i],ny=y+dy[i];
      if((nx<=0)||(nx>n)||(ny<=0)||(ny>n))
        {
          continue;
        }
      if(h[nx][ny]>h[x][y])
        {
          flag=0;
          break;
        }
      if((h[nx][ny]==h[x][y])&&(vis[nx][ny]==-1))
        {
          flag=0;
          break;
        }
    }
  if(!flag)
    {
      vis[x][y]=-1;
      return 0;
    }
  for(register int i=0; i<8; ++i)
    {
      int nx=x+dx[i],ny=y+dy[i];
      if((nx<=0)||(nx>n)||(ny<=0)||(ny>n))
        {
          continue;
        }
      if((h[nx][ny]==h[x][y])&&(!vis[nx][ny]))
        {
          if(!search_hi(nx,ny))
            {
              vis[x][y]=-1;
              return 0;
            }
        }
    }
  return 1;
}

int main()
{
  scanf("%d",&n);
  for(register int i=1; i<=n; ++i)
    {
      for(register int j=1; j<=n; ++j)
        {
          scanf("%d",&h[i][j]);
        }
    }
  for(register int i=1; i<=n; ++i)
    {
      for(register int j=1; j<=n; ++j)
        {
          if(!vis[i][j])
            {
              lo+=search_lo(i,j);
            }
        }
    }
  memset(vis,0,sizeof vis);
  for(register int i=1; i<=n; ++i)
    {
      for(register int j=1; j<=n; ++j)
        {
          if(!vis[i][j])
            {
              hi+=search_hi(i,j);
            }
        }
    }
  printf("%d %d\n",hi,lo);
  return 0;
}
