#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005, LOG = 20;
int pre[MAXN], a[MAXN], st[MAXN][LOG], Log[MAXN], n, k, l, r;
void init() {
    Log[1]=0; for(int i=2;i<=n;i++) Log[i]=Log[i/2]+1;
    for(int i=1;i<=n;i++) st[i][0]=i;
    for(int j=1;j<=Log[n];j++) {
        for(int i=1;i+(1<<j)-1<=n;i++) {
            int a=st[i][j-1],b=st[i+(1<<(j-1))][j-1];
            st[i][j]=pre[a]>pre[b]?a:b;
        }
    }
}
int RMQ(int l,int r) {
    int len=Log[r-l+1];
    int a=st[l][len],b=st[r-(1<<len)+1][len];
    return pre[a]>pre[b]?a:b;
}
struct Answer {
    int o,l,r,t;
    Answer(int o,int l,int r):o(o),l(l),r(r) {
        t=RMQ(l,r);
        //printf("%d~(%d~%d)->%d~%d->%d\n", o, l, r, o, t, getValue());
    }
    int getValue() const { return pre[t]-pre[o-1]; }
    friend bool operator<(const Answer &a, const Answer &b) {
        return ((a.getValue()) < (b.getValue()));
    }
};
priority_queue<Answer> q;
long long ans=0;
int main() {
    scanf("%d%d%d%d", &n, &k, &l, &r);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
    //for(int i=1;i<=n;i++) printf("% 4d ", i); puts("");
    //for(int i=1;i<=n;i++) printf("% 4d ", pre[i]); puts("");
    init();
    for(int i=1;i+l-1<=n;i++) q.push(Answer(i,i+l-1,min(i+r-1, n)));
    for(int i=1;i<=k;i++) {
        Answer t = q.top(); q.pop();
        //printf("%d~%d:%d\n", t.o,t.t,t.getValue());
        ans+=t.getValue();
        if (t.t!=t.l) q.push(Answer(t.o,t.l,t.t-1));
        if (t.t!=t.r) q.push(Answer(t.o,t.t+1,t.r));
    }
    printf("%lld\n", ans);
    return 0;
}
