struct Solution;
impl Solution {
    pub fn sort_colors(nums: &mut Vec<i32>) {
        let mut i: usize = 0;
        let mut j: usize = 0;
        for k in 0..nums.len() {
            let v = nums[k];
            nums[k] = 2;
            if v < 2 {
                nums[j] = 1;
                j += 1;
            }
            if v < 1 {
                nums[i] = 0;
                i += 1;
            }
        }
    }
}
pub fn main() {
    let nums: &mut Vec<i32> = &mut vec![2, 2, 0, 0, 1, 2, 1];
    Solution::sort_colors(nums);
    println!("{:?}", nums);
}
