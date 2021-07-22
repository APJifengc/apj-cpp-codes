#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 10005, MAXM = 50005;
struct Graph {
    int fst[MAXN], nxt[MAXM<<1], to[MAXM<<1], w[MAXM<<1], tot;
    void add(int u,int v,int ww) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
        w[tot]=ww;
    }
}mst;
int n,m;
int f[MAXN];
struct Edge {
    int u,v,w;
    Edge(int _,int __,int ___):u(_),v(__),w(___){}
};
vector<Edge> edges;
bool cmp(Edge a,Edge b) {
    return a.w>b.w;
}
int find(int x) {
    if (f[x]==x) return x;
    return f[x]=find(f[x]);
}
void unite(int x,int y) {
    x=find(x),y=find(y);
    f[y]=x;
}
bool detect(int x,int y) {
    return find(x)==find(y);
}
void kruskal() {
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=0;i<m;i++) {
        int u=edges[i].u,v=edges[i].v,w=edges[i].w;
        if (!detect(u,v)) {
            unite(u,v);
            mst.add(u,v,w);
            mst.add(v,u,w);
        }
    }
}
int fa[MAXN][20],ma[MAXN][20],Log[MAXN],depth[MAXN];
void dfs(int i,int pre,int edge) {
    depth[i]=depth[pre]+1;
    if (pre==0) {
        fa[i][0]=0;
        ma[i][0]=0x3F3F3F3F;
    } else {
        fa[i][0]=pre;
        ma[i][0]=mst.w[edge];
    }
    forGraph(mst,i,j,edge) if (j!=pre) {
        dfs(j,i,edge);
    }
}
void init() {
    Log[1]=0; for(int i=2;i<=n;i++) Log[i]=Log[i/2]+1;
    for(int j=1;j<=Log[n];j++) {
        for(int i=1;i<=n;i++) {
            fa[i][j]=fa[fa[i][j-1]][j-1];
   //         printf("ma[%d][%d]=min(ma[%d][%d](%d), ma[%d][%d](%d));\n", i,j,i,j-1,ma[i][j-1],
     //               fa[i][j-1],j-1,ma[fa[i][j-1]][j-1]);
            if (fa[i][j]) ma[i][j]=min(ma[i][j-1], ma[fa[i][j-1]][j-1]);
        }
    } 
}
int jump(int x,int d) {
    return x;
}
int lca(int x,int y) {
    int ret = INT_MAX;
    if (depth[x]<depth[y]) swap(x,y);
    int d=depth[x]-depth[y];
    for(int i=0;i<=Log[d];i++) if(d&(1<<i)) {
    //    printf("ret[%d][%d]=min(ret,ma[%d][%d](%d))\n", x, y, x, i, ma[x][i]);
        ret=min(ret,ma[x][i]);
        x=fa[x][i];
    }
    if (x==y) return ret;
    for(int j=Log[n];j>=0;j--) 
        if(fa[x][j] && fa[x][j]!=fa[y][j]) {
            ret=min(ret,ma[x][j]);
            ret=min(ret,ma[y][j]);
    //        printf("ret[%d][%d]=min(ret,ma[%d][%d](%d))\n", x, y, x, j, ma[x][j]);
    //        printf("ret[%d][%d]=min(ret,ma[%d][%d](%d))\n", x, y, x, j, ma[x][j]);
            x=fa[x][j],y=fa[y][j];
        }
    ret=min(ret,ma[x][0]);
    ret=min(ret,ma[y][0]);
    //printf("ret[%d][%d]=min(ret,ma[%d][%d](%d))\n", x, y, x, 0, ma[x][0]);
    //printf("ret[%d][%d]=min(ret,ma[%d][%d](%d))\n", x, y, x, 0, ma[x][0]);
    return ret;
}
int q;
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int x,y,z;
        scanf("%d%d%d", &x, &y, &z);
        edges.push_back(Edge(x,y,z));
    }
    memset(ma,0x3F,sizeof ma);
    sort(edges.begin(), edges.end(), cmp);
    kruskal();
    //for(int i=1;i<=n;i++) forGraph(mst,i,j,edge) printf("%d->%d:%d\n", i, j, mst.w[edge]);
    for(int i=1;i<=n;i++) {
        if (!depth[i]) dfs(i,0,0);
    }
    /*for(int i=1;i<=n;i++) {
      printf("%d: dep%d fat%d ma%d\n", i, depth[i], fa[i][0], ma[i][0]);
      }*/
    init();
    /*printf("fa:\n");
      for(int i=1;i<=n;i++) {
      for(int j=0;j<=Log[n];j++) {
      printf("%d[%d]=%d ", i, j, fa[i][j]);
      }
      printf("\n");
      }
      printf("ma:\n");
      for(int i=1;i<=n;i++) {
      for(int j=0;j<=Log[n];j++) {
      printf("%d[%d]=%d ", i, j, ma[i][j]);
      }
      printf("\n");
      }*/
    scanf("%d", &q);
    for(int i=1;i<=q;i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        if (detect(x,y)) {
            int l = lca(x,y);
            //printf("lca(%d,%d)=%d\n", x, y, l);
            printf("%d\n", l);
        } else printf("-1\n");
    }
    return 0;
}

