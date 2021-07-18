#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 5005, MAXM = 20005;
struct Graph {
    int nxt[MAXM],to[MAXM],fst[MAXN],tot;
    void add(int u,int v) {
        //printf("%d->%d\n",u,v);
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
    Graph() {
        memset(fst, 0, sizeof(fst));
        memset(nxt, 0, sizeof(nxt));
        tot=1;
    }
}g,dag;
int n,m;
int dfn[MAXN],low[MAXN],num;
bitset<MAXM> bridge;
stack<int> st;
int c[MAXN], cnum, degree[MAXN];
bitset<MAXN> hasEdge[MAXN];
void tarjan(int u,int inEdge) {
    dfn[u]=low[u]=++num;
    forGraph(g,u,v,edge) {
        if (!dfn[v]) {
            tarjan(v, edge);
            low[u]=min(low[u],low[v]);
            if (low[v]>dfn[u]) {
                bridge[edge]=1;
                bridge[edge^1]=1;
            }
        } else if (edge != (inEdge^1)) {
            low[u]=min(low[u],dfn[v]);
        }
    }
}
void dfs(int u) {
    c[u]=cnum;
    forGraph(g,u,v,edge) {
        if (bridge[edge]) continue;
        if (!c[v]) dfs(v);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        g.add(x,y);
        g.add(y,x);
    }
    for(int i=1;i<=n;i++) {
        if (!dfn[i]) {
            tarjan(i,0);
        }
    }
    for(int i=1;i<=n;i++) {
        if (!c[i]) {
            cnum++;
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++) {
        forGraph(g,i,v,edge) {
            if (c[i]!=c[v]) {
                if (!hasEdge[c[i]][c[v]]) {
                    //printf("%d %d\n", c[i], c[v]);
                    degree[c[v]]++;
                    hasEdge[c[i]][c[v]]=1;
                }
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=cnum;i++) {
        //printf("%d:%d\n", i, degree[i]);
        if (degree[i]==1) {
            cnt++;
        }
    }
    printf("%d\n", (cnt+1)/2);
    return 0;
}
