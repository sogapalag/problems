struct Solution;
impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        use std::cmp::min;
        (1..min(m, n)).fold(1u64, |acc, i| (acc * (n + m - i - 1) as u64) / i as u64) as i32
    }
}

fn main() {
    let (m, n) = (51, 9);
    let res = Solution::unique_paths(m, n);
    print!("{}", res);
}
