#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
struct Graph {
    int nxt[50005],fst[MAXN],dfn[MAXN],low[MAXN],tot,to[50005];
    int SCCNo[MAXN],SCCsize[MAXN],num,SCCnum;
    bitset<MAXN> inStack;
    int outdegree[MAXN];
    stack<int> st;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
        outdegree[u]++;
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
        if (dfn[u]==low[u]) {
            SCCNo[u]=++SCCnum;
            //printf("%d: %d ", SCCnum, u);
            while(st.top()!=u) {
                SCCNo[st.top()]=SCCnum;
                //printf("%d ", st.top());
                SCCsize[SCCnum]++;
                inStack[st.top()]=0;st.pop();
            }
            //printf("\n");
            SCCsize[SCCnum]++;
            inStack[u]=0;st.pop();
        }
    }

    Graph(){
        memset(nxt,0,sizeof(nxt));
        memset(fst,0,sizeof(fst));
        memset(dfn,0,sizeof(dfn));
        memset(SCCsize, 0, sizeof(SCCsize));
        memset(outdegree, 0, sizeof(outdegree));
        tot=0;
        num=0;
        SCCnum=0;
        inStack=0;
        st=stack<int>();
    }
}g,dag;
int n,m;
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        g.add(x,y);
    }
    for(int i=1;i<=n;i++) {
        if (!g.dfn[i]) {
            g.tarjan(i);
        }
    }
    for(int i=1;i<=n;i++) {
        for(int edge=g.fst[i];edge;edge=g.nxt[edge]) {
            if (g.SCCNo[g.to[edge]]!=g.SCCNo[i]) {
                dag.add(g.SCCNo[i], g.SCCNo[g.to[edge]]);
            }
        }
    }
    //for(int i=1;i<=g.SCCnum;i++) 
    //    for(int edge=dag.fst[i];edge;edge=dag.nxt[edge])
    //        printf("%d->%d\n", i, dag.to[edge]);
    int cnt=0;
    for(int i=1;i<=g.SCCnum;i++) {
        if (dag.outdegree[i]==0) {
            if (cnt) {
                printf("0\n");
                return 0;
            } else {
                cnt=g.SCCsize[i];
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
