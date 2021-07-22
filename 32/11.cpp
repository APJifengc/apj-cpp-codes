#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 50005;
typedef pair<int,int> Node;
int w[MAXN],l[MAXN],n;
Node nodes[MAXN];
bool cmp(const Node &a,const Node &b) { return a.first==b.first?a.second>b.second:a.first>b.first; }
int q[MAXN],head=1,tail=1,f[MAXN];
inline long double slope(int k,int j) { return (long double)(f[k]-f[j])/(long double)(w[k+1]-w[j+1]); }
signed main() {
    scanf("%lld", &n);
    for(int i=1;i<=n;i++) scanf("%lld%lld", &nodes[i].first, &nodes[i].second);
    sort(nodes+1,nodes+1+n,cmp);
    int node_cnt=n;n=0;
    for(int i=1;i<=node_cnt;i++) {
        if (nodes[i].second > l[n]) {
            l[++n]=nodes[i].second;
            w[n]=nodes[i].first;
        }
    }
    //for(int i=1;i<=n;i++) printf("%lld:%lld %lld\n", i, w[i], l[i]);
    for(int i=1;i<=n;i++) {
        while(head<tail && slope(q[head], q[head+1]) >= (long double)-l[i]) head++;
        int j=q[head];f[i]=f[j]+w[j+1]*l[i];
        while(head<tail && slope(q[tail-1], i)>=slope(q[tail],q[tail-1])) tail--;
        q[++tail]=i;
    }
    printf("%lld\n", f[n]);
	return 0;
}
