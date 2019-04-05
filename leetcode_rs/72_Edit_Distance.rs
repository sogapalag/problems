struct Solution;
impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        use std::cmp::min;
        let s1 = word1.as_bytes();
        let s2 = word2.as_bytes();
        let m = s1.len();
        let n = s2.len();
        let mut D = vec![vec![0i32; n + 1]; m + 1];
        for i in 1..=m {
            D[i][0] = i as i32;
        }
        for j in 1..=n {
            D[0][j] = j as i32;
        }
        for i in 1..=m {
            for j in 1..=n {
                D[i][j] = min(D[i][j - 1] + 1, D[i - 1][j] + 1);
                let eq = if s1[i - 1] == s2[j - 1] { 0 } else { 1 };
                D[i][j] = min(D[i][j], D[i - 1][j - 1] + eq);
            }
        }
        return D[m][n];
    }
}
pub fn main() {
    let w1 = String::from("horse");
    let w2 = String::from("ros");
    let res = Solution::min_distance(w1, w2);
    println!("{}", res);
}
