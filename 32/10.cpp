#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
int n,l,c[MAXN],p[MAXN];
double f[MAXN];
inline double a(int i) { return p[i]+i; }
inline double b(int i) { return p[i]+i+l+1; }
inline double X(int i) { return b(i); }
inline double Y(int i) { return f[i]+b(i)*b(i); }
inline double slope(int i,int j) { return (Y(i)-Y(j))/(X(i)-X(j)); }
struct Deque {
    int a[MAXN<<2];
    int h,t;
    Deque():h(1),t(1){memset(a,0,sizeof a);}
    bool empty() {return h>t;}
    int front() {return a[h];}
    int front2() {return a[h+1];}
    int back() {return a[t];}
    int back2() {return a[t-1];}
    void push_back(int b) {a[++t]=b;}
    void pop_back() {t--;}
    void pop_front() {h++;}
    void clear() {h=1,t=1;}
    int size() {return t-h+1;}
}q;
int main() {
    scanf("%d%d", &n, &l);
    for(int i=1;i<=n;i++) scanf("%d", &c[i]);
    for(int i=1;i<=n;i++) p[i]=p[i-1]+c[i];
    for(int i=1;i<=n;i++) {
        while(q.size()>1 && slope(q.front2(),q.front())<=2*a(i)) q.pop_front();
        int j=q.front();
        f[i]=f[j]+pow(a(i)-b(j),2);
        while(q.size()>1 && slope(i, q.back2())<=slope(q.back2(), q.back())) q.pop_back();
        q.push_back(i);
    }
    printf("%lld\n", (long long)f[n]);
    return 0;
}
