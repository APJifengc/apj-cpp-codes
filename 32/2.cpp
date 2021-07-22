#include <bits/stdc++.h>
using namespace std;
const int MAXT = 2005;
int t,w,maxp,ap[MAXT],bp[MAXT],as[MAXT],bs[MAXT];
int f[MAXT][MAXT];
typedef pair<int,int> Node;
#define v first
#define index second
struct Deque {
    Node a[MAXT];
    int h,t;
    Deque():h(0),t(-1){}
    bool empty() {return h>t;}
    Node front() {return a[h];}
    Node back() {return a[t];}
    void push_back(Node b) {a[++t]=b;}
    void pop_back() {t--;}
    void pop_front() {h++;}
    void clear() {h=0,t=-1;}
}q1,q2;
int main() {
    scanf("%d%d%d", &t, &maxp, &w);	
    for(int i=1;i<=t;i++) scanf("%d%d%d%d", &ap[i], &bp[i], &as[i], &bs[i]);
    memset(f,128,sizeof(f));
    for(int i=1;i<=t;i++) {
        q1.clear(); q2.clear();
        for(int j=0;j<=as[i];j++) {
            f[i][j]=-ap[i]*j;
        }
        for(int j=0;j<=maxp;j++) {
            f[i][j] = max(f[i][j], f[i-1][j]);
        }
        if (i-w-1>=0) {
            for(int j=0;j<=maxp;j++) {
                while(!q1.empty() && q1.front().index < j-as[i]) q1.pop_front();
                if (!q1.empty()) f[i][j] = max(f[i][j], q1.front().v-j*ap[i]);
                int v=f[i-w-1][j]+j*ap[i];
                while(!q1.empty() && q1.back().v <= v) q1.pop_back();
                q1.push_back(make_pair(v, j));
            }
            for(int j=maxp;j>=0;j--) {
                while(!q2.empty() && q2.front().index > j+bs[i]) q2.pop_front();
                if (!q2.empty()) f[i][j] = max(f[i][j], q2.front().v-j*bp[i]);
                int v=f[i-w-1][j]+j*bp[i];
                while(!q2.empty() && q2.back().v <= v) q2.pop_back();
                q2.push_back(make_pair(v, j));
            }
        }
    }
    /*for(int i=1;i<=t;i++) {
        for(int j=0;j<=maxp;j++) printf("% 2d ", f[i][j]);
        puts("");
    }*/
    int ans=INT_MIN;
    for(int i=0;i<=maxp;i++) ans=max(ans, f[t][i]);
    printf("%d\n", ans);
    return 0;
}
