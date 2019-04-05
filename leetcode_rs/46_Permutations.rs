struct Solution;
impl Solution {
    pub fn permute(_nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut nums = _nums.to_vec();
        let mut res: Vec<Vec<i32>> = Vec::new();
        Self::permute_swap_recursive(&mut nums, 0, &mut res);

        return res;
    }
    pub fn permute_swap_recursive(nums: &mut Vec<i32>, begin: usize, res: &mut Vec<Vec<i32>>) {
        if begin == nums.len() {
            res.push(nums.to_vec());
        }
        for i in begin..nums.len() {
            nums.swap(begin, i);
            Self::permute_swap_recursive(nums, begin + 1, res);
            nums.swap(begin, i);
        }
    }
}

fn main() {
    let nums = vec![];
    let res = Solution::permute(nums);
    println!("{:?}", res);
}
