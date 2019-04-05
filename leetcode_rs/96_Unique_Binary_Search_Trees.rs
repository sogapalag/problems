struct Solution;
impl Solution {
    pub fn num_trees(n: i32) -> i32 {
        let n = n as usize;
        let mut score = vec![0; n + 1];
        score[0] = 1;
        for i in 1..=n {
            for j in 0..i {
                score[i] += score[j] * score[i - j - 1];
            }
        }
        score[n]
    }
}
pub fn main() {}
