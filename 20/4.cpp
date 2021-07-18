#include <bits/stdc++.h>
#define LL long long 
using namespace std;
struct Node {
	LL v;
	int index;
	Node(LL a, int b):v(a),index(b){}
	Node():index(-1){}
};
const int MAXA = 1005;
LL v[MAXA][MAXA];
int a,b,n;
deque<Node> qmax, qmin;
LL maxs[MAXA][MAXA],mins[MAXA][MAXA];
int main() {
	scanf("%d%d%d\n", &a, &b, &n);
	for(int i=1;i<=a;i++) {
		for(int j=1;j<=b;j++) {
			scanf("%lld", &v[i][j]);
		}
	}
	for(int i=1;i<=a;i++) {
		qmax.clear();
		qmin.clear();
		for(int j=1;j<=b;j++) {
			while(!qmax.empty() && qmax.back().v <= v[i][j]) qmax.pop_back();
			while(!qmin.empty() && qmin.back().v >= v[i][j]) qmin.pop_back();
			qmax.push_back(Node(v[i][j], j));
			qmin.push_back(Node(v[i][j], j));
			while(!qmax.empty() && qmax.front().index <= j-n) qmax.pop_front();
			while(!qmin.empty() && qmin.front().index <= j-n) qmin.pop_front();
			if (j>=n) {
				maxs[j-n+1][i]=qmax.front().v;
				mins[j-n+1][i]=qmin.front().v;
			}
		}
	}
	LL ans=INT_MAX;
	for(int i=1;i<=b-n+1;i++) {
		qmax.clear();
		qmin.clear();
		for(int j=1;j<=a;j++) {
			while(!qmax.empty() && qmax.back().v <= maxs[i][j]) qmax.pop_back();
			while(!qmin.empty() && qmin.back().v >= mins[i][j]) qmin.pop_back();
			qmax.push_back(Node(maxs[i][j], j));
			qmin.push_back(Node(mins[i][j], j));
			while(!qmax.empty() && qmax.front().index <= j-n) qmax.pop_front();
			while(!qmin.empty() && qmin.front().index <= j-n) qmin.pop_front();
			if (j>=n) ans=min(ans, qmax.front().v-qmin.front().v);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
