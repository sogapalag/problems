const int N = 1e5;

int p[N], r[N];
int init(){
    F0R(i, N){
        p[i] = i;
        r[i] = 1;
    }
}
int find(int x){
    return p[x]==x? x: p[x] = find(p[x]);
}
int join(int x, int y){
    x = find(x);
    y = find(y);
    if (r[x] < r[y])
        swap(x, y);
    p[y] = x;
    r[x] += r[y];
}
bool check(int x, int y){
    return find(x) == find(y);
}
