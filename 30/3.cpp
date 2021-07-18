#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305;
int n,m;
double p,q;
vector<int> r[MAXN];
double a[MAXN][MAXN];
double l[11000];
void dfs(int i, double w, int step) {
    if (step<0) return;
    l[i]+=w*p/q;
    for(int j : r[i]) {
        dfs(j, w*((1.0-p/q)/(double)r[i].size()), step-1);
    }
}
int main() {
    scanf("%d%d%lf%lf",&n, &m, &p, &q);
    for (int i=1; i<=m; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        r[x].push_back(y);
        r[y].push_back(x);
    }
    for(int i=1;i<=n+1;i++) a[1][i]++;
    for(int i=2;i<=n;i++) {
        a[i][i]++;
        for(int j : r[i]) a[i][j]+=((p-q)/q/r[j].size()); 
    }
    /*for(int aa=1;aa<=n;aa++) {
        for(int bb=1;bb<=n+1;bb++) {
            printf("% .2lf ", a[aa][bb]);
        }
        puts("");
    }puts("");*/
    for(int i=1;i<=n;i++) {
        int r=i;
        for(int j=i+1;j<=n;j++) {
            if (fabs(a[j][i]>fabs(a[r][i]))) r=j;
        }
        swap(a[i],a[r]);
        for(int j=1;j<=n;j++) {
            double mul = a[j][i]/a[i][i];
            if (i!=j) for(int k=1;k<=n+1;k++) a[j][k]-=mul*a[i][k];
        }
        /*for(int aa=1;aa<=n;aa++) {
            for(int bb=1;bb<=n+1;bb++) {
                printf("% .2lf ", a[aa][bb]);
            }
            puts("");
        }puts("");*/
    }
    for(int i=1;i<=n;i++) printf("%.9lf\n", a[i][n+1]/a[i][i]);
    //dfs(1, 1, 10);
    //for(int i=1;i<=n;i++) printf("%.2lf\n", l[i]);
    return 0;
}
