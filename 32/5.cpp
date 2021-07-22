#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
int f[MAXN][MAXN],n;
typedef pair<int,int> Node;
#define index first
#define value second
Node nodes[MAXN];
int p[MAXN],x[MAXN];
struct Deque {
    int a[MAXN];
    int h,t;
    Deque():h(0),t(-1){}
    bool empty() {return h>t;}
    int front() {return a[h];}
    int back() {return a[t];}
    void push_back(int b) {a[++t]=b;}
    void pop_back() {t--;}
    void pop_front() {h++;}
    void clear() {h=0,t=-1;}
}q;
int ans=0;
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d%d", &nodes[i].index, &nodes[i].value);
    sort(nodes+1,nodes+1+n);
    for(int i=1;i<=n;i++) p[i]=nodes[i].value,x[i]=nodes[i].index;
    for(int i=1;i<=n;i++) f[i][i]=p[i],ans=max(ans,f[i][i]);
    for(int j=1;j<n;j++) {
        int maxfjk=f[j][j],now=j;
        for(int i=j+1;i<=n;i++) {
            for(;x[now]>=2*x[j]-x[i] && now>=1;now--) maxfjk=max(maxfjk, f[j][now]);
            f[i][j]=maxfjk+p[i];
            ans=max(ans,f[i][j]);
        }
    }
    memset(f,0,sizeof f);
    for(int i=1;i<=n;i++) f[i][i]=p[i],ans=max(ans,f[i][i]);
    for(int j=n;j>1;j--) {
        int maxfjk=f[j][j],now=j;
        for(int i=j-1;i>=1;i--) {
            for(;x[now]<=2*x[j]-x[i] && now<=n;now++) maxfjk=max(maxfjk, f[j][now]);
            f[i][j]=maxfjk+p[i];
            ans=max(ans,f[i][j]);
            //printf("f[%d][%d]=%d\n", i,j,f[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
