//extern crate serde;

struct Solution;
impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> u64 {
        return Self::binomial(m + n - 2, n - 1);
    }
    pub fn binomial(n: i32, k: i32) -> u64 {
        use std::cmp::min;
        (1..=min(k, n - k)).fold(1u64, |acc, i| (acc * (n - i + 1) as u64) / i as u64)
    }
}

fn main() {
    //use serde::ser::Serialize;
    let (m, n) = (19, 1);
    let res = Solution::unique_paths(m, n);
    //let out = res.serialize();
    //println!("{:?}", out);
    print!("{}", res);
}
