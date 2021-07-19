#include <bitset>
#include <math.h>
#include <cstdio>
#include <cstring>
#define forGraph(u,v,i) for(int i=fst[u],v=to[i];i;i=nxt[i],v=to[i])
#define int long long
using namespace std;
const int MAXM = 100005, MAXN = 100005;
int fst[MAXN],to[MAXM],nxt[MAXM],tot;
int dfn[MAXN],low[MAXN],num;
int c[MAXN],cnum,csize,ccnt,root,deg;
bitset<MAXN> cutpoint, cutVis;
void add(int u,int v) {
    to[++tot]=v;
    nxt[tot]=fst[u];
    fst[u]=tot;
}
void tarjan(int u,int fa) {
    dfn[u]=low[u]=++num;
    forGraph(u,v,edge) {
        if (!dfn[v]) {
            tarjan(v,u);
            low[u]=min(low[u], low[v]);
            if (dfn[u]<=low[v]) {
                if (u==root) deg++;
                else cutpoint[u]=1;
            }
        } else if (v!=fa) low[u]=min(low[u], dfn[v]);
    }
}
void dfs(int x) {
    //printf("%d ", x);
    c[x]=cnum;
    if (cutpoint[x]) return;
    csize++;
    forGraph(x,v,edge) {
        if (cutpoint[v] && c[v]!=cnum) ccnt++,c[v]=cnum;
        if (!c[v]) dfs(v);
    }
}
int n,m;
void init() {
#define s(x) memset(x, 0, sizeof(x));
    s(fst);s(to);s(nxt);s(dfn);s(low);s(c);
    tot=0;num=0;cnum=0;cutpoint=0;root=0;cutVis=0;n=0;
}
signed main() {
    int cas=0;
    while(~scanf("%lld", &m)) {
        if (m==0) return 0;
        cas++;
        init();
        for(int i=1;i<=m;i++) {
            int x,y;
            scanf("%lld%lld", &x, &y);
            add(x,y);
            add(y,x);
            n=max(n,x);
            n=max(n,y);
        }
        for(int i=1;i<=n;i++) {
            if(!dfn[i]) tarjan(root=i,i);
            if(deg>=2) cutpoint[root]=1;
            deg=0;
        }
        long long ans=1;
        int cnt=0;
        for(int i=1;i<=n;i++) {
            if(!c[i] && !cutpoint[i]) {
                csize=ccnt=0;
                cnum++;
                //printf("%d: ", cnum);
                dfs(i);
                //printf("\n");
                if (ccnt==0) {
                    cnt+=2;
                    ans*=csize*(csize-1)/2;
                } else if (ccnt==1) {
                    cnt++;
                    ans*=csize;
                }
            }
        }
        printf("Case %lld: %lld %lld\n",cas, cnt, ans);
    }
    return 0;
}
