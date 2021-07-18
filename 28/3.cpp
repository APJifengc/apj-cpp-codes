#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int ans;
struct Graph {
    int fst[MAXN],nxt[MAXN],tot,to[MAXN];
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
    int dfn[MAXN], low[MAXN], num;
    int SCCno[MAXN], SCCnum, SCCw[MAXN];
    int w[MAXN];
    stack<int> st;
    bitset<MAXN> isEnd, SCCisEnd;
    bitset<MAXN> inStack;
    void dfs(int i,int ww) {
    //    printf("dfs %d %d\n", i, ww);
        if (isEnd[i]) ans=max(ans, ww);
        for(int edge=fst[i];edge;edge=nxt[edge]) dfs(to[edge], ww+w[to[edge]]);
    }
    void tarjan(int u) {
        dfn[u]=low[u]=++num;
        st.push(u);
        inStack[u]=1;
        for(int edge=fst[u];edge;edge=nxt[edge]) {
            int v=to[edge];
            if (!dfn[v]) {
                tarjan(v);
                low[u]=min(low[u],low[v]);
            } else if (inStack[v]) {
                low[u]=min(low[u],dfn[v]);
            } 
        }   
        if (low[u]==dfn[u]) {
            SCCno[u]=++SCCnum;
            SCCw[SCCnum]=w[u];
            if (isEnd[u]) SCCisEnd[SCCnum]=1;
    //        printf("%d: %d ", SCCnum, u);
            while(st.top()!=u) {
                SCCno[st.top()]=SCCnum;
                SCCw[SCCnum]+=w[st.top()];
                if (isEnd[st.top()]) SCCisEnd[SCCnum]=1;
    //            printf("%d ", st.top());
                inStack[st.top()]=0;st.pop();
            }
    //        printf("\n");
            inStack[u]=0;st.pop();
        }
    }
    Graph() {
        memset(fst, 0, sizeof(fst));
        memset(dfn, 0, sizeof(dfn));
        memset(SCCw, 0, sizeof(SCCw));
        tot=0;
        num=0;
        SCCnum=0;
    }
}g,dag;
int n,m,s,p;
int main() {
    scanf("%d%d", &n, &m);	
    for(int i=1;i<=m;i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        g.add(x,y);
    }
    for(int i=1;i<=n;i++) scanf("%d", &g.w[i]);
    scanf("%d%d", &s, &p);
    for(int i=1;i<=p;i++) {
        int x;
        scanf("%d", &x);
        g.isEnd[x]=1;
    }
    for(int i=1;i<=n;i++) 
        if (!g.dfn[i]) g.tarjan(i);
    memcpy(dag.w, g.SCCw, sizeof(dag.w));
    dag.isEnd = g.SCCisEnd;
    for(int i=1;i<=n;i++) {
        for(int edge=g.fst[i];edge;edge=g.nxt[edge]) {
            int v=g.to[edge];
            if (g.SCCno[v]!=g.SCCno[i]) dag.add(g.SCCno[i], g.SCCno[v]);
        }
    }
    //for(int i=1;i<=g.SCCnum;i++) 
    //    for(int edge=dag.fst[i];edge;edge=dag.nxt[edge]) 
    //        printf("%d->%d\n", i, dag.to[edge]);
    //for(int i=1;i<=g.SCCnum;i++) printf("%d:%d(%c)\n", i, dag.w[i], dag.isEnd[i]?'Y':'N');
    dag.dfs(g.SCCno[s],g.SCCw[g.SCCno[s]]);
    printf("%d\n", ans);
    return 0;
}
