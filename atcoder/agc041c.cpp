#include <bits/stdc++.h>

using namespace std;

char three[3][3] = {
    {'a','a','.'},
    {'.','.','b'},
    {'.','.','b'},
};

char four[4][4] = {
    {'a','a', 'b', 'c'},
    {'e','e', 'b', 'c'},
    {'d','f', 'g', 'g'},
    {'d','f', 'h', 'h'}
};

string five[5] = {
    "aabee",
    ".cbff",
    "dch..",
    "d.h.z",
    "ffxxz"
};

string six[6] = {
    "aab.ee",
    ".cb.ff",
    "dcgg..",
    "dehh..",
    "fe...z",
    "f..xxz"
};

string seven[7] = {
    "aab..ee",
    ".cb..ff",
    ".cggk..",
    "d.hhk..",
    "de.jj..",
    "fe....z",
    "f...xxz"
};

const int N = 1024; 
char a[N][N];

void p3(int x) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a[x+i][x+j] = three[i][j];
        }
    }
}
void p4(int x) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a[x+i][x+j] = four[i][j];
        }
    }
}
void p5(int x) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            a[x+i][x+j] = five[i][j];
        }
    }
}
void p6(int x) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            a[x+i][x+j] = six[i][j];
        }
    }
}
void p7(int x) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            a[x+i][x+j] = seven[i][j];
        }
    }
}

// could be elegant cases, 3x or 4x+{4,5,6,7}.
// https://artofproblemsolving.com/community/c6h1625929p10191585
void solve() {
    int n; cin >> n;
    if (n==2) {
        cout << -1; return;
    }

    memset(a, '.', sizeof a);
    if (n%5==0) {
        for (int i = 0; i < n; i+=5) {
            p5(i);
        }
    } else if (n%3 == 0) {
        for (int i = 0; i < n; i+=3) {
            p3(i);
        }
    } else if (n%2==0){
        int i = 0;
        while (n-i > 6) {
            p4(i); i+=4;
        }
        assert(n-i==4||n-i==6);
        if (n-i==4) {
            p4(i);
        }else p6(i);
    } else {
        int i = 0;
        p7(i); i+=7;
        while (n-i > 6) {
            p4(i); i+=4;
        }
        if (n-i>0) {
            if (n-i==4) p4(i);
            else p6(i);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
