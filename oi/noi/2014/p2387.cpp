#include <bits/stdc++.h>

using namespace std;


// LCT template copy from https://blog.csdn.net/youhavepeople/article/details/75040776
const int N = 200000 + 5;
int mx[N],va[N],fa[N],c[N][2],sta[N],top;
bool rev[N];

bool isroot( int x ){ return c[fa[x]][0]!=x&&c[fa[x]][1]!=x; } // 1-based?
void update( int x ){
	mx[x] = x;
	if( va[mx[c[x][1]]] > va[mx[x]] ) mx[x] = mx[c[x][1]];
	if( va[mx[c[x][0]]] > va[mx[x]] ) mx[x] = mx[c[x][0]];
}
void pushdown( int x ){
	if( rev[x] ){
		swap(c[x][0],c[x][1]);
		rev[c[x][0]] ^= 1; rev[c[x][1]] ^= 1; rev[x] = 0;
	}
}
void rotate( int x ){
	int y = fa[x], z = fa[y], l, r;
	l = (c[y][1]==x); r = l^1;
	if( !isroot(y) ) c[z][y==c[z][1]] = x;
	fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
	c[y][l] = c[x][r]; c[x][r] = y;
	update(y); update(x);
}
void splay( int x ){
	sta[++top] = x;
	for( int i = x; !isroot(i); i = fa[i] ) sta[++top] = fa[i];
	while( top ) pushdown(sta[top--]);
	while( !isroot(x) ){
		int y = fa[x], z = fa[y];
		if( !isroot(y) ){
			if( (c[y][0]==x)^(c[z][0]==y) ) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access( int x ){
	for( int t = 0; x; t = x, x = fa[x] ){
		splay(x); c[x][1] = t; update(x);
	}
}
void move_to_root( int x ){
	access(x); splay(x); rev[x] ^= 1;
}
void link( int x, int y ){
	move_to_root(x); fa[x] = y;
}
void cut( int x, int y ){
	move_to_root(x); access(y); splay(y); fa[x] = c[y][0] = 0;
}
int query( int x, int y ){
	move_to_root(x); access(y); splay(y); return mx[y];
}
// end of LCT

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) : n(_n)
        , p(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

// first if all w0 equal, it's easy to note kruskal work
// so we iter w0-order, maintain MST with relaxing w1.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> es(m);
    for (int i = 0; i < m; i++) {
        int x,y,w0,w1;
        cin >> x >> y >> w0 >> w1;
        es[i] = {x,y,w0,w1};
    }
    sort(es.begin(), es.end(), [&](auto& u, auto& v){
        return get<2>(u) < get<2>(v);
    });
    for (int i = 1; i <= m; i++) {
        va[n+i] = get<3>(es[i-1]);
        mx[n+i] = n+i;
    }
    Dsu d(n+1);
    int res = 1e9;
    for (int i = 1; i <= m; i++) {
        int u,v,w0,w1;
        tie(u,v,w0,w1) = es[i-1];
        if (d.check(u,v)) {
            int e = query(u, v);
            if (va[e] <= w1) continue;
            // remove mx edge
            int x,y,_,__;
            tie(x,y,_,__) = es[e - n - 1];
            cut(x, e);
            cut(y, e);
        } else {
            d.join(u, v);
        }
        // note n+i point as edge i
        link(u, n+i);
        link(v, n+i);
        if (d.check(1, n)) {
            res = min(res, w0 + va[query(1,n)]);
        }
    }
    if (res > 1e8) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
