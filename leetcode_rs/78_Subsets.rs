struct Solution;
impl Solution {
    pub fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let n = nums.len();
        let p = 1 << n;
        let mut res: Vec<Vec<i32>> = vec![vec![]; p];
        for i in 0..p {
            for j in 0..n {
                if i & (1 << j) != 0 {
                    res[i].push(nums[j])
                }
            }
        }
        return res;
    }
}
pub fn main() {
    let nums = vec![1, 2, 3];
    let res = Solution::subsets(nums);
    println!("{:?}", res);
}

