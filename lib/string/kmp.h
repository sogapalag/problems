#include <bits/stdc++.h>
using namespace std;


// SNIPPETS_START kmp
const int N = 1005, P = 55;
int lc, ls;
char c[N], s[P];
int bac_s[P][26];

void kmp_pre(int l, char p[], int bac[][26]){
    int b[P]; b[0]=-1;// kmp backup table
    int j = -1;
    for (int i=0; i < l;){
        while (j >= 0 && p[i] != p[j])
            j = b[j];
        i++; j++;
        b[i] = j;
    }

    // bac[i][x]: when before matched length i, next coming char x
    // matched length
    for (int i=0; i<=l; i++){
        for (char x = 'a'; x <= 'z'; x++){
            int j = i;
            while (j >= 0 && x != p[j])
                j = b[j];
            bac[i][x - 'a'] = ++j;
        }
    }
}
// SNIPPETS_END
