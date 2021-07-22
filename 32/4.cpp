#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 100005;
int f[MAXN],n,k,e[MAXN],pre[MAXN];
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
signed main() {
    scanf("%lld%lld", &n, &k);
    for(int i=1;i<=n;i++) scanf("%lld", &e[i]);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+e[i];
    for(int i=1;i<=n+1;i++) {
        while(!q.empty() && q.front() < i-k-1) q.pop_front();
        while(!q.empty() && f[q.back()]-pre[q.back()] <= f[i-1]-pre[i-1]) q.pop_back();
        q.push_back(i-1);
        f[i]=f[q.front()]-pre[q.front()]+pre[i-1];
        //printf("f[%lld]=%lld\n", i, f[i]);
    }
    printf("%lld\n", f[n+1]);
    return 0;
}
