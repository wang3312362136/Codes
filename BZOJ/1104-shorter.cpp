#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
const int maxn=1000;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int f[maxn*maxn+10],mark[maxn*maxn+10],n,m,h[maxn+10][maxn+10],cnt,ans;
struct point{
  int x,y;
  bool operator <(const point &other)const{return abs(h[x][y])<abs(h[other.x][other.y]);}
}city[maxn*maxn+10],full[maxn*maxn+10];
int find(int x){return f[x]?(f[x]=find(f[x])):x;}
int merge(int x,int y){return (x=find(x))==(y=find(y))?0:f[x]=y,mark[x]&&(mark[y]=1);}
int trans(int x,int y){return (x-1)*m+y;}
int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j){
      scanf("%d",&h[i][j]);
      (h[i][j]>0)&&(city[++cnt].x=i,city[cnt].y=j);
      full[trans(i,j)].x=i,full[trans(i,j)].y=j;
    }
  std::sort(city+1,city+cnt+1),std::sort(full+1,full+n*m+1);
  for(int i=1,now=1,xx,yy,fa;xx=city[i].x,yy=city[i].y,(i<=cnt);++i,fa=find(trans(xx,yy)),ans+=(!mark[fa])&&(mark[fa]=1))
    for(int x,y;(x=full[now].x),(y=full[now].y),((now<=n*m)&&(abs(h[full[now].x][full[now].y])<=abs(h[xx][yy])));++now)
      for(int j=0,nx,ny;nx=x+dx[j],ny=y+dy[j],j<4;++j){
        if((nx<=0)||(nx>n)||(ny<=0)||(ny>m))continue;
        if(abs(h[nx][ny])<=abs(h[xx][yy]))merge(trans(x,y),trans(nx,ny));
      }
  return printf("%d\n",ans),0;
}
