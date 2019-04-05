struct Solution;
impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        // fibonacci f(n) with f(1)=1, f(2)=2
        match n {
            1 => 1,
            2 => 2,
            k => (2..k).fold((1, 2), |acc, __| (acc.1, acc.0 + acc.1)).1,
        }
    }
}

pub fn main() {
    let res = Solution::climb_stairs(5);
    println!("{}", res);
}
