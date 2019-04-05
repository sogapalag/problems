struct Solution;
use std::cmp;
impl Solution {
    pub fn max_coins(nums: Vec<i32>) -> i32 {
        // remove 0s
        let mut x: Vec<i32> = Vec::with_capacity(nums.len() + 2);
        x.push(1);
        for e in nums {
            if e > 0 {
                x.push(e);
            }
        }
        x.push(1);
        //
        let n = x.len();
        let mut dp = vec![vec![0; n]; n];
        for k in 2..n {
            for left in 0..n - k {
                let right = left + k;
                for i in left + 1..right {
                    dp[left][right] = cmp::max(
                        dp[left][right],
                        x[left] * x[i] * x[right] + dp[left][i] + dp[i][right],
                    );
                }
            }
        }
        dp[0][n - 1]
    }
}
pub fn main() {}
