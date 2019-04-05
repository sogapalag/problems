//use std::collections::BitSet;
// BitSet not found, deprecated?
struct Solution;
impl Solution {
    pub fn can_partition(nums: Vec<i32>) -> bool {
        Self::dp_method(&nums)
    }
    // 36ms
    fn dp_method(a: &Vec<i32>) -> bool {
        let sum: i32 = a.iter().sum();
        if sum % 2 != 0 {
            return false;
        }
        let target: usize = (sum / 2) as usize;
        let mut dp = vec![vec![false; target + 1]; a.len()];
        dp[0][0] = true;
        dp[0][a[0] as usize] = true;
        // One can do some constant time-optimization
        // and space-optim use O(target).
        // omitted..
        for k in 1..a.len() {
            dp[k][0] = true;
            for v in 1..=target {
                if a[k] <= v as i32 {
                    dp[k][v] = dp[k - 1][v] || dp[k - 1][v - a[k] as usize];
                }
            }
        }
        dp[a.len() - 1][target]
    }
    //fn bit_method(a: & Vec<i32>) -> bool{
    //    const MAX_NUM:usize = 100;
    //    const MAX_SIZE:usize = 200;
    //    let mut bset = BitSet::with_capacity(MAX_NUM*MAX_SIZE/2+1);
    //    bset.insert(1);
    //    let sum:i32 = a.iter().sum();
    //    if sum % 2 != 0{
    //        return false;
    //    }
    //    let target = (sum/2) as usize;
    //    for e in a.iter() {
    //        bset |= bset << e;
    //    }
    //    bset[target]
    //}
}
pub fn main() {}
