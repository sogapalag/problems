struct Solution;
impl Solution {
    pub fn find_target_sum_ways(nums: Vec<i32>, s: i32) -> i32 {
        Self::dp_method(&nums, s)
    }
    fn dp_method(a: &Vec<i32>, s: i32) -> i32 {
        // note assume 0<n<=20, sum<=2000
        // a_i>0
        // P-N=s, P+N=sum
        // => 2*P = s+sum, s<=sum
        //let n = a.len();
        let sum: i32 = a.iter().sum();
        if s > sum || (s + sum) % 2 != 0 {
            return 0;
        }
        let target = ((s + sum) / 2) as usize;
        let mut dp = vec![0; target + 1];
        dp[0] = 1;
        for e in a {
            let e = *e as usize;
            for t in (0..=target).rev() {
                if t >= e {
                    dp[t] += dp[t - e];
                }
            }
        }
        dp[target]
    }
}
pub fn main() {}
