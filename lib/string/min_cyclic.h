#include <bits/stdc++.h>

using namespace std;

int min_cyclic(const string& s) {
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (s[(i+k)%n] == s[(j+k)%n]) k++;
        else if (s[(i+k)%n] > s[(j+k)%n]) i += k+1, k=0;
        else j += k+1, k=0;
        if (i == j) j++;
    }
    return min(i,j);
}
