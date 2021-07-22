#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 40005;
int n,m,k;
struct Graph {
    int fst[MAXN], nxt[MAXN<<1], to[MAXN<<1], w[MAXN<<1], tot;
    void add(int u,int v,int ww) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
        w[tot]=ww;
    }
}g,ask;
struct BinaryIndexTree {
    int a[MAXN<<1];
#define lowbit(x) (x&(-x))
    int query(int i) {
        int res=0;
        while(i) {
            res+=a[i];
            i-=lowbit(i);
        }
        return res;
    }
    void add(int i,int d) {
        while(i<=2*n) {
            a[i]+=d;
            i+=lowbit(i);
        }
    }
}bit;
int startPos[MAXN],endPos[MAXN],depth[MAXN],dfsNum;
int f[MAXN][20], Log[MAXN];
void dfs(int i,int pre,int e) {
    if(i!=1) f[i][0]=pre;
    depth[i]=depth[pre]+1;
    startPos[i]=++dfsNum;
    bit.add(dfsNum, g.w[e]);
    forGraph(g,i,j,edge) if(j!=pre) dfs(j,i,edge);
    endPos[i]=++dfsNum;
    bit.add(dfsNum, -g.w[e]);
}
int fa[MAXN],asks[MAXN][2],ans[MAXN];
bitset<MAXN> vis;
int find(int x) {
    if (fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void unite(int x,int y) {
    x=find(x),y=find(y);
    if (x!=y) fa[x]=y;
}
void lca(int i) {
    fa[i]=i;
    vis[i]=1;
    forGraph(g,i,j,edge) {
        if (!vis[j]) {
            lca(j);
            unite(j,i);
        }
    }
    forGraph(ask,i,j,edge) {
        if (vis[j]) ans[ask.w[edge]]=find(j);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int u,v,w;char op[2];
        scanf("%d%d%d%s", &u, &v, &w, op);
        g.add(u,v,w);
        g.add(v,u,w);
    }
    dfs(1,1,0);
    scanf("%d", &k);
    for(int i=1;i<=k;i++) {
        scanf("%d%d", &asks[i][0], &asks[i][1]);
        ask.add(asks[i][0],asks[i][1],i);
        ask.add(asks[i][1],asks[i][0],i);
    }
    lca(1);
    for(int i=1;i<=k;i++) printf("%d\n", bit.query(startPos[asks[i][0]])+bit.query(startPos[asks[i][1]])-2*bit.query(startPos[ans[i]]));
    return 0;
}
