struct Solution;
impl Solution {
    pub fn num_islands(mut grid: Vec<Vec<char>>) -> i32 {
        Self::dfs_call(&mut grid)
    }
    fn dfs_call(grid: &mut Vec<Vec<char>>) -> i32 {
        let mut res = 0;
        for i in 0..grid.len() {
            for j in 0..grid[0].len() {
                if grid[i][j] == '1' {
                    Self::_dfs(grid, i, j);
                    res += 1;
                }
            }
        }
        res
    }
    fn _dfs(grid: &mut Vec<Vec<char>>, i: usize, j: usize) {
        if i == grid.len() || j == grid[0].len() || grid[i][j] == '0' {
            return;
        }
        grid[i][j] = '0';
        if i != 0 {
            Self::_dfs(grid, i - 1, j);
        }
        if j != 0 {
            Self::_dfs(grid, i, j - 1);
        }
        Self::_dfs(grid, i + 1, j);
        Self::_dfs(grid, i, j + 1);
    }
}
pub fn main() {}
