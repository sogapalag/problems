#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    int i = 0, j = n-1;
    string t;
    while (i+1 < j-1) {
        int cnt[3] = {};
        // adj-differ, i.e. the four has a match
        cnt[s[i]-'a']++;
        cnt[s[i+1]-'a']++;
        cnt[s[j-1]-'a']++;
        cnt[s[j]-'a']++;
        for (int x:{0,1,2})if(cnt[x]>=2){
            t.push_back(char('a'+x));
            break;
        }
        i += 2;
        j -= 2;
    }
    auto rt = t;
    reverse(rt.begin(), rt.end());
    if (i<=j) {
        t.push_back(s[i]);
    }
    t += rt;
    cout << t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
