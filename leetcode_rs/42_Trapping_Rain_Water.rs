struct Solution;
impl Solution {
    pub fn trap(height: Vec<i32>) -> i32 {
        if height.is_empty() {
            return 0;
        }
        let (mut left_idx, mut right_idx) = (0, height.len() - 1);
        let mut res = 0;
        let (mut max_left, mut max_right) = (0, 0);

        while left_idx <= right_idx {
            if height[left_idx] <= height[right_idx] {
                if height[left_idx] >= max_left {
                    max_left = height[left_idx];
                } else {
                    res += max_left - height[left_idx];
                }
                left_idx += 1;
            } else {
                if height[right_idx] >= max_right {
                    max_right = height[right_idx];
                } else {
                    res += max_right - height[right_idx];
                }
                right_idx -= 1;
            }
        }
        res
    }
}

fn main() {
    //let v = vec![0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1];
    //let v: Vec<i32> = [].to_vec();
    let v = vec![3];

    let res = Solution::trap(v);
    println!("{}", res);
}
