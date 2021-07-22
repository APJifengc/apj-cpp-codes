#include <bits/stdc++.h>
using namespace std;
const int MAXN = 205;
int n,m,sx,sy,k;
char maps[MAXN][MAXN];
int f[MAXN][MAXN][MAXN];
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
    scanf("%d%d%d%d%d", &n, &m, &sx, &sy, &k);
    for(int i=1;i<=n;i++) scanf("%s", maps[i]+1);
    memset(f,0x80,sizeof(f));
    f[0][sx][sy]=0;
    for(int i=1;i<=k;i++) {
        int s,t,d;
        scanf("%d%d%d", &s, &t, &d);
        int len=t-s+1;
        if (d==1) { // up
            for(int y=1;y<=m;y++) {
                q.clear();
                for(int x=n;x>=1;x--) {
                    if (maps[x][y]=='x') {q.clear();continue;}
                    while(!q.empty() && q.front() > x+len) q.pop_front();
                    while(!q.empty() && f[i-1][q.back()][y]+q.back() <= f[i-1][x][y]+x) q.pop_back();
                    q.push_back(x);
                    f[i][x][y]=f[i-1][q.front()][y]+q.front()-x;
                    //printf("f[%d][%d][%d]=%d\n", i,x,y,f[i][x][y]);
                }
            }
        } else if (d==2) { // down
            for(int y=1;y<=m;y++) {
                q.clear();
                for(int x=1;x<=n;x++) {
                    if (maps[x][y]=='x') {q.clear();continue;}
                    while(!q.empty() && q.front() < x-len) q.pop_front();
                    while(!q.empty() && f[i-1][q.back()][y]-q.back() <= f[i-1][x][y]-x) q.pop_back();
                    q.push_back(x);
                    f[i][x][y]=f[i-1][q.front()][y]+x-q.front();
                    //printf("f[%d][%d][%d]=%d\n", i,x,y,f[i][x][y]);
                }
            }
        } else if (d==3) { // left
            for(int x=1;x<=n;x++) {
                q.clear();
                for(int y=m;y>=1;y--) {
                    if (maps[x][y]=='x') {q.clear();continue;}
                    while(!q.empty() && q.front() > y+len) q.pop_front();
                    while(!q.empty() && f[i-1][x][q.back()]+q.back() <= f[i-1][x][y]+y) q.pop_back();
                    q.push_back(y);
                    f[i][x][y]=f[i-1][x][q.front()]+q.front()-y;
                    //printf("f[%d][%d][%d]=%d\n", i,x,y,f[i][x][y]);
                }
            }
        } else { // right
            for(int x=1;x<=n;x++) {
                q.clear();
                for(int y=1;y<=m;y++) {
                    if (maps[x][y]=='x') {q.clear();continue;}
                    while(!q.empty() && q.front() < y-len) q.pop_front();
                    while(!q.empty() && f[i-1][x][q.back()]-q.back() <= f[i-1][x][y]-y) q.pop_back();
                    q.push_back(y);
                    f[i][x][y]=f[i-1][x][q.front()]+y-q.front();
                    //printf("f[%d][%d][%d]=%d\n", i,x,y,f[i][x][y]);
                }
            }
        }
    }
    int ans=INT_MIN;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            ans=max(ans, f[k][i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
