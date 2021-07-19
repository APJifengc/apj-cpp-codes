#include <bits/stdc++.h>
#define forGraph(u,v,i) for(int i=fst[u],v=to[i];i;i=nxt[i],v=to[i])
using namespace std;
const int MAXM = 1005, MAXN = 1005;
int fst[MAXN],to[MAXM],nxt[MAXM],tot;
int dfn[MAXN],low[MAXN],num;
int c[MAXN],cnum,csize[MAXN],ccnt[MAXN],root;
bitset<MAXN> cutpoint;
void add(int u,int v) {
    to[++tot]=v;
    nxt[tot]=fst[u];
    fst[u]=tot;
}
void tarjan(int u) {
    dfn[u]=low[u]=++num;
    int flag=0;
    forGraph(u,v,edge) {
        if (!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u], low[v]);
            if (dfn[u]<=low[v]) {
                flag++;
                if (flag>1 || u!=root) {
                    //printf("cutpoint %d\n", u);
                    cutpoint[u]=1;
                }
            }
        } else low[u]=min(low[u], dfn[v]);
    }
}
bitset<MAXN> cutVis;
void dfs(int x) {
    //printf("%d ", x);
    c[x]=cnum;
    csize[cnum]++;
    forGraph(x,v,edge) {
        if (c[v]) continue;
        if (cutpoint[v]) {
            if (!cutVis[v]) {
                ccnt[cnum]++;
                cutVis[v]=1;
            }
        }
        else dfs(v);
    }
}
void init() {
#define s(x) memset(x, 0, sizeof(x));
    s(fst);s(to);s(nxt);s(dfn);s(low);s(c);s(csize);s(ccnt);
    tot=0;num=0;cnum=0;cutpoint=0;
}
int n,m;
int main() {
    int cas=0;
    while(~scanf("%d", &m)) {
        n=0;
        if (m==0) return 0;
        cas++;
        init();
        for(int i=1;i<=m;i++) {
            int x,y;
            scanf("%d%d", &x, &y);
            add(x,y);
            add(y,x);
            n=max(n,x);
            n=max(n,y);
        }
        for(int i=1;i<=n;i++) {
            if(!dfn[i]) {
                root=i;
                tarjan(i);
            }
        }
        for(int i=1;i<=n;i++) {
            if(!c[i] && !cutpoint[i]) {
                cnum++;
                cutVis=0;
                //printf("%d: ", cnum);
                dfs(i);
                //printf("\n");
            }
        }
        unsigned long long ans=1;
        int cnt=0;
        for(int i=1;i<=cnum;i++) {
            if (ccnt[i]==0) {
                cnt+=2;
                ans*=csize[i]*(csize[i]-1)/2;
            } else if (ccnt[i]==1) {
                cnt++;
                ans*=csize[i];
            }
        }
        printf("Case %d: %d %llu\n",cas, cnt, ans);
    }
    return 0;
}
