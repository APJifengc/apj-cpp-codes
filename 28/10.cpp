#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
#define LL long long
using namespace std;
const int MAXN = 500005, P = 1000000007;
int n;
LL x[MAXN],r[MAXN];
struct Graph {
    int nxt[MAXN*4],to[MAXN*4],fst[MAXN],tot;
    int lst[MAXN],rst[MAXN];
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
    Graph() {
        memset(nxt,0,sizeof(nxt));
        memset(fst,0,sizeof(fst));
        memset(lst,0,sizeof(lst));
        memset(rst,0,sizeof(rst));
        tot=0;
    }
}g,dag;
int s[MAXN];
struct SegmentTree {
    int l,r,index;
    SegmentTree *lc,*rc;
    SegmentTree(int l_,int r_):l(l_),r(r_) {
        if (l==r) {
            index=l;
            g.lst[index]=l;
            g.rst[index]=r;
            s[index]=1;
            return;
        }
        index=++n;
        g.lst[index]=l;
        g.rst[index]=r;
        int mid=(l+r)>>1;
        lc = new SegmentTree(l,mid);
        rc = new SegmentTree(mid+1,r);
        g.add(index, lc->index);
        g.add(index, rc->index);
        //printf("%d->%d,%d\n", index, lc->index, rc->index);
    }
    void addEdges(int i,int ll,int rr) {
        if (ll>r || rr<l) return;
        if (ll<=l&&rr>=r) {
            if (l!=r || l!=i) g.add(i,index);
            return;
        }
        int mid=(l+r)>>1;
        if (ll<=mid) lc->addEdges(i,ll,rr);
        if (rr>mid) rc->addEdges(i,ll,rr);
    }
};
int sccCnt, sccSize[MAXN], sccNo[MAXN];
stack<int> st;
int dfn[MAXN],low[MAXN],num;
bitset<MAXN> inStack;
int ans[MAXN];
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
    if (dfn[u]==low[u]) {
        int lest=g.lst[u],rest=g.rst[u];
        sccNo[u]=++sccCnt;
        //printf("%d: %d ", sccCnt, u);
        sccSize[sccCnt]++;
        while(st.top()!=u) {
            sccNo[st.top()]=sccCnt;
            sccSize[sccCnt]++;
            lest=min(lest,g.lst[st.top()]);
            rest=max(rest,g.rst[st.top()]);
            //printf("%d ", st.top());
            inStack[st.top()]=0;st.pop();
        }
        //puts("");
        inStack[u]=0;st.pop();
        dag.lst[sccCnt]=lest;
        dag.rst[sccCnt]=rest;
    }
}
int indegree[MAXN];
bitset<MAXN> vis;
int cnt;
void dfs(int i) {
    vis[i]=1;
    cnt+=sccSize[i];
    forGraph(dag,i,j,edge) {
        if (!vis[j]) dfs(j);
    }
}
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%lld%lld", &x[i], &r[i]);
    int orin = n;
    SegmentTree tree = SegmentTree(1,n);
    for(int i=1;i<=orin;i++) {
        //printf("%d->(%d~%d)\n", i, lower_bound(x+1,x+orin+1,x[i]-r[i])-x, upper_bound(x+1,x+orin+1,x[i]+r[i])-x-1);
        tree.addEdges(i, lower_bound(x+1,x+orin+1,x[i]-r[i])-x, upper_bound(x+1,x+orin+1,x[i]+r[i])-x-1);
    }
    //for(int i=1;i<=n;i++) {
    //    forGraph(g,i,v,edge) {
    //        printf("%d->%d\n", i, v);
    //    }
    //}
    for(int i=1;i<=n;i++) {
        if (!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++) {
        forGraph(g,i,j,edge) {
            if (sccNo[i]!=sccNo[j]) {
                dag.add(sccNo[j],sccNo[i]);
                indegree[sccNo[i]]++;
            }
        }
    }
    //for(int i=1;i<=sccCnt;i++) {
    //    printf("%d: range %d~%d\n", i, dag.lst[i], dag.rst[i]);
    //}

    queue<int> q;
    for(int i=1;i<=sccCnt;i++) if (!indegree[i]) q.push(i);
    while(!q.empty()) {
        int f=q.front();q.pop();
        forGraph(dag,f,v,edge) {
            dag.lst[v]=min(dag.lst[v],dag.lst[f]);
            dag.rst[v]=max(dag.rst[v],dag.rst[f]);
            indegree[v]--;
            if (indegree[v]==0) q.push(v);
        }
    }
    //for(int i=1;i<=sccCnt;i++) printf("%d: now ranged %d~%d\n", i, dag.lst[i], dag.rst[i]);
    long long out=0;
    for(int i=1;i<=orin;i++) out=(out+(LL)i*(dag.rst[sccNo[i]]-dag.lst[sccNo[i]]+1))%P;
    printf("%lld\n", out);
    return 0;
}
