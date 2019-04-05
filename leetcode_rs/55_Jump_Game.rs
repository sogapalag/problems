struct Solution;
impl Solution {
    pub fn can_jump(nums: Vec<i32>) -> bool {
        use std::cmp::max;
        let mut cj: usize = 0; //max can jump
        for i in 0..nums.len() {
            if i > cj {
                return false;
            }
            cj = max(cj, i + nums[i] as usize);
        }
        return true;
    }
}

fn main() {
    let nums: Vec<i32> = vec![3, 2, 1, 0, 4];
    let res = Solution::can_jump(nums);
    println!("{}", res);
}
