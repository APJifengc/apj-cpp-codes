#include <bitset>
#include <cstdio>
#include <cstring>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 10005;
int n,q;
struct Graph {
    int fst[MAXN],nxt[MAXN<<1],to[MAXN<<1],tot;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
}g;
int f[MAXN][15],Log[MAXN],depth[MAXN];
void dfs(int i, int pre) {
    depth[i]=depth[pre]+1;
    f[i][0]=pre;
    forGraph(g,i,j,edge) if(j!=pre) dfs(j,i);
}
void init() {
    Log[1]=0;for(int i=2;i<=n;i++) Log[i]=Log[i/2]+1;
    for(int j=1;j<=Log[n];j++) 
        for(int i=1;i<=n;i++) 
            f[i][j]=f[f[i][j-1]][j-1];
}
int lca(int x,int y) {
    if(depth[x]<depth[y]) swap(x,y);
    int d=depth[x]-depth[y];
    for(int j=0;j<=Log[d];j++) if(d&(1<<j)) x=f[x][j];
    if (x==y) return x;
    for(int j=Log[depth[y]];j>=0;j--) if(f[x][j]!=f[y][j]) x=f[x][j],y=f[y][j];
    return f[x][0];
}
int T;
bitset<MAXN> inD;
int main() {
    scanf("%d", &T);
    while(T--) {
        memset(g.fst, 0, sizeof g.fst);
        g.tot=0;
        inD=0;
        memset(f, 0, sizeof f);
        memset(depth, 0, sizeof depth);
        scanf("%d", &n);
        for(int i=1;i<n;i++) {
            int x,y;
            scanf("%d%d", &x, &y);
            g.add(x,y);
            g.add(y,x);
            inD[y]=1;
        }
        int root=0;
        for(int i=1;i<=n;i++) if(!inD[i]) root=i;
        dfs(root,0);
        init();
        int a,b;
        scanf("%d%d", &a, &b);
        printf("%d\n", lca(a,b));
    }
    return 0;
}
