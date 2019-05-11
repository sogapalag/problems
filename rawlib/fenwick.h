// fenwick tree, aka, Binary indexed tree.
// key trick least sig bits LSB(i) = (i&-i)
// each idx responsible [idx - LSB(i) + 1, idx]
// 1-based

const int SZ = 100000 + 5;
int fen[SZ+1];
// memset(fen, 0, sizeof fen);

// add val in p
void upd(int p, int val){
    for(; p <= SZ; p += (p&-p))
        fen[p] += val;
}

// sum in [1, p]
int query(int p){
    int tmp = 0;
    for (; p > 0; p -= (p&-p))
        tmp += fen[p];
    return tmp;
}
// sum [l, r]
int ranqy(int l, int r){
    return query(r) - query(l-1);
}
