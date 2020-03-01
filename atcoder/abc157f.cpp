#include <bits/stdc++.h>

using namespace std;

// copied from betrue12
vector<pair<double, double>> crosspoint(double x1, double y1, double r2, double x2, double y2, double r1){
    x1 -= x2;
    y1 -= y2;
    double S = x1*x1 + y1*y1;
    double a = (S + r1*r1 - r2*r2) / 2;
    double D = S*r1*r1-a*a;
    if(D < 0) return {};

    double A1 = a * x1;
    double B1 = y1 * sqrt(D);
    double A2 = a * y1;
    double B2 = x1 * sqrt(D);
    return {
        {(A1+B1)/S+x2, (A2-B2)/S+y2},
        {(A1-B1)/S+x2, (A2+B2)/S+y2}
    };
}
// END

using pnt = pair<double,double>;
void solve() {
    int n,k;
    cin >> n >> k;
    vector<pnt> a(n);
    vector<double> coeff(n);
    for (int i = 0; i < n; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        a[i] = {x,y};
        coeff[i] = z;
    }


    auto dist = [](pnt& p0, pnt& p1){
        double dx = p0.first - p1.first;
        double dy = p0.second - p1.second;
        return sqrt(dx*dx+dy*dy);
    };

    const double EPS = 1e-8;
    // candidates: center or intersected points of pair-circle. TODO proof?
    auto ck = [&](double T){
        auto candi = a;
        for (int i = 0; i < n; i++) {
            double x,y;
            tie(x,y) = a[i];
            double z = T/coeff[i];
            for (int j = 0; j < i; j++) {
                double u,v;
                tie(u,v) = a[j];
                double w = T/coeff[j];
                for (auto& p: crosspoint(x,y,z,u,v,w)) {
                    candi.push_back(p);
                }
            }
        }

        for (auto& p0: candi) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                pnt& p1 = a[i];
                if (dist(p0, p1) <= T/coeff[i] + EPS) cnt++;
            }
            if (cnt >= k) return true;
        }
        return false;
    };

    double lo = 0, hi = 1e9;
    while (hi - lo > EPS) {
        double mid = (hi+lo)/2;
        (ck(mid) ? hi : lo) = mid;
    }
    cout << fixed<<setprecision(10)<<lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
