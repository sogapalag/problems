struct Solution;
impl Solution {
    pub fn move_zeroes(nums: &mut Vec<i32>) {
        Self::write(nums);
    }
    fn write(nums: &mut Vec<i32>) {
        let mut pos: usize = 0;
        for i in 0..nums.len() {
            if nums[i] != 0 {
                nums[pos] = nums[i];
                pos += 1;
            }
        }
        for j in pos..nums.len() {
            nums[j] = 0;
        }
    }
}
pub fn main() {}
