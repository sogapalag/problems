struct Solution;
impl Solution {
    pub fn min_path_sum(mut grid: Vec<Vec<i32>>) -> i32 {
        use std::cmp::min;
        if grid.is_empty() || grid[0].is_empty() {
            return 0;
        }
        let m = grid.len();
        let n = grid[0].len();
        for i in 1..m {
            grid[i][0] += grid[i - 1][0];
        }
        for j in 1..n {
            grid[0][j] += grid[0][j - 1];
        }
        for h in 2..(m + n - 1) {
            for i in 1..min(m, h) {
                let j = h - i;
                if j < n {
                    grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]);
                }
            }
        }
        return grid[m - 1][n - 1];
    }
}

pub fn main() {
    let v = vec![vec![1, 3, 1], vec![1, 5, 1], vec![4, 2, 1]];
    let res = Solution::min_path_sum(v);
    println!("{}", res);
}
