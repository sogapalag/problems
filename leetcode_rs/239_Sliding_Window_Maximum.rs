use std::collections::VecDeque;
struct Solution;
impl Solution {
    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let n = nums.len();
        let k = k as usize;
        let mut res: Vec<i32> = Vec::with_capacity(n - k + 1);
        let mut q = VecDeque::new();
        for i in 0..n {
            while let Some(&id) = q.front() {
                if id + k <= i {
                    q.pop_front();
                } else {
                    break;
                }
            }
            while let Some(&id) = q.back() {
                if nums[id] <= nums[i] {
                    q.pop_back();
                } else {
                    break;
                }
            }
            q.push_back(i);
            if i >= k - 1 {
                if let Some(&id) = q.front() {
                    res.push(nums[id]);
                }
            }
        }
        res
    }
}
pub fn main() {}
