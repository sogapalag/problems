struct Solution;
impl Solution {
    pub fn find_duplicate(nums: Vec<i32>) -> i32 {
        Self::floyd(&nums)
    }
    fn floyd(f: &Vec<i32>) -> i32 {
        // f(i) -> j, i.e. nums[i] = j
        let mut slow: usize = 0;
        let mut fast: usize = 0;
        loop {
            slow = f[slow] as usize;
            fast = f[f[fast] as usize] as usize;
            if slow == fast {
                break;
            }
        }
        fast = 0;
        // find entry
        loop {
            slow = f[slow] as usize;
            fast = f[fast] as usize;
            if slow == fast {
                break slow as i32;
            }
        }
    }
}
pub fn main() {}
