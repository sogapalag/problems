#include <bits/stdc++.h>

using namespace std;
using ld=long double;
#define double ld
const double sq2 = sqrtl(double(2));//pow((double)2, 0.5);
const double sq3 = sqrtl(double(3));//pow((double)3, 0.5);
const double pi = acos(-1.0);

// if < sq2, theta=rot_x.  sin(theta)+cos(theta) = area
//      sin(theta + pi/4) = area/sq2
// else, theta = pi/4, phi = rot_z.  sq2*cos(phi) + sin(phi) = area
//      sin(phi + t) = area/sq3, cos(t)=1/sq3
void solve() {
    double area;
    cin >> area;
    double theta; // sin+cos
    double phi = 0.0;
    if (area <= sq2) {
        theta = asin(area/sq2) - pi/4;
    } else {
        theta = pi/4;
        double t = acos(1/sq3);
        phi = asin(area/sq3) - t;
    }
    
    cerr<<theta<<' '<<phi<<endl;
    //auto f = [&](double x, double y, double z){
    //    complex<double> p(y,z);
    //    p = polar(abs(p), arg(p)+theta);
    //    y = p.real(), z = p.imag();

    //    p = complex<double>(x,y);
    //    p = polar(abs(p), arg(p)+phi);
    //    x = p.real(), y = p.imag();
    //    cout << x << ' ' << y << ' ' << z << '\n';
    //};
    //f(0.5,0,0);
    //f(0,0.5,0);
    //f(0,0,0.5);

    double st = sin(theta), ct = cos(theta);
    double sp = sin(phi), cp = cos(phi);
    double R = 0.5;
    cout << '\n'; /////!!!!!!!!!!!!......... format.....
    cout << R*cp << ' ' << R*sp << ' ' << ld(0) << '\n';
    cout << -R*ct*sp << ' ' << R*ct*cp << ' ' << R*st << '\n';
    cout << R*st*sp << ' ' << -R*st*cp << ' ' << R*ct << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
