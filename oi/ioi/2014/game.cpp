#include <bits/stdc++.h>
#include "game.h"

using namespace std;
int deg[2048];
void initialize(int n) {
    memset(deg, 0, sizeof deg);
}
// one observation: last edge (u,v) must be two components with sz(u)+sz(v) = n
// but this won't help to online query
// below genius & elegant solution
// any u > 0 has one edge to left, total n-1. and u can reach 0. so tree.
// => thus final query needed
int hasEdge(int u, int v) {
    if (u < v) u = v;
    return ++deg[u] == u;
}
