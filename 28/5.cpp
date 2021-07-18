#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
struct Graph {
    int nxt[MAXN],fst[MAXN],to[MAXN],tot;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
    Graph(){
        memset(nxt, 0, sizeof(nxt));
        tot=0;
    }
}g,dag;
int n,dfn[MAXN],low[MAXN],num,SCCno[MAXN],SCCnum,SCCsize[MAXN];
stack<int> st;bitset<MAXN> inStack;
void tarjan(int u) {
    dfn[u]=low[u]=++num;
    st.push(u);inStack[u]=1;
    forGraph(g,u,v,edge) {
        if (!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if (inStack[v]) {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (low[u]==dfn[u]) {
        SCCno[u]=++SCCnum;
        SCCsize[SCCnum]=1;
        while(st.top()!=u) {
            SCCno[st.top()]=SCCnum;
            SCCsize[SCCnum]++;
            inStack[st.top()]=0;st.pop();
        }
        inStack[u]=0;st.pop();
    }
}
int indegree[MAXN],ans[MAXN];
int main() {
	scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        int x;
        scanf("%d", &x);
        g.add(i,x);
    }
    for(int i=1;i<=n;i++) 
        if (!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++) 
        forGraph(g,i,v,edge) 
            if (SCCno[i]!=SCCno[v]) {
                dag.add(SCCno[v],SCCno[i]);
                indegree[SCCno[i]]++;
    //            printf("%d->%d\n", SCCno[v], SCCno[i]);
            }	
    queue<int> q;
    for(int i=1;i<=SCCnum;i++) 
        if (indegree[i]==0) {
            q.push(i);
            ans[i]=SCCsize[i];
        }
    while(!q.empty()) {
        int u=q.front();q.pop();
        forGraph(dag,u,v,edge) {
            ans[v]=ans[u]+SCCsize[v];
            indegree[v]--;
            if (indegree[v]==0)
                q.push(v);
        }
    }
    for(int i=1;i<=n;i++) printf("%d\n", ans[SCCno[i]]);
    //for(int i=1;i<=SCCnum;i++) printf("%d:%d\n", i, SCCsize[i]);
    return 0;
}
