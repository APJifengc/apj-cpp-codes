#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
int n,m,a[MAXN],pre[MAXN],ans=INT_MIN;
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
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
    for(int i=1;i<=n;i++) {
        while(!q.empty() && q.front() < i-m) q.pop_front();
        ans=max(ans, pre[i]-pre[q.front()]);
        while(!q.empty() && pre[q.back()]>=pre[i]) q.pop_back();
        q.push_back(i);
    }
    printf("%d\n", ans);
    return 0;
}
