#include <bits/stdc++.h>

using namespace std;


// use 2 or 3 mass center, WA
void solve() {
    cout << fixed << setprecision(10);
    int n,k;
    cin >> n >> k;
    if (k == 1) {
        cout << 0; return;
    }
    vector<pair<int, int>> a(n);
    vector<int> mass(n);
    for (int i = 0; i < n; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        a[i] = {x,y};
        mass[i] = z;
    }
    double res = 1e9;
    // two
    for (int i = 0; i < n; i++) {
        int x,y;
        tie(x,y) = a[i];
        for (int j = i+1; j < n; j++) {
            int u,v;
            tie(u,v) = a[j];
            double mx = mass[i]*x + mass[j]*u;
            double my = mass[i]*y + mass[j]*v;
            mx /= mass[i]+mass[j];
            my /= mass[i]+mass[j];
            vector<double> ts(n);
            for (int i = 0; i < n; i++) {
                double dx = mx - a[i].first;
                double dy = my - a[i].second;
                double dr = dx*dx+dy*dy;
                dr = sqrt(dr);
                ts[i] = mass[i] * dr;
            }
            sort(ts.begin(), ts.end());
            res = min(res, ts[k-1]);
        }
    }
    // 3
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int u = j+1; u < n; u++) {
                double mx = mass[i]*a[i].first + mass[j]*a[j].first + mass[u]*a[u].first;
                double my = mass[i]*a[i].second + mass[j]*a[j].second + mass[u]*a[u].second;
                mx /= mass[i]+mass[j]+mass[u];
                my /= mass[i]+mass[j]+mass[u];
                vector<double> ts(n);
                for (int i = 0; i < n; i++) {
                    double dx = mx - a[i].first;
                    double dy = my - a[i].second;
                    double dr = dx*dx+dy*dy;
                    dr = sqrt(dr);
                    ts[i] = mass[i] * dr;
                }
                sort(ts.begin(), ts.end());
                res = min(res, ts[k-1]);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
