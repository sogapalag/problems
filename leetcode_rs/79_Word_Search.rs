struct Solution;
impl Solution {
    pub fn exist(mut board: Vec<Vec<char>>, word: String) -> bool {
        let s: Vec<char> = word.chars().collect();
        for i in 0..board.len() {
            for j in 0..board[0].len() {
                if Self::_dfs(&mut board, &s, i, j, 0) {
                    return true;
                }
            }
        }
        false
    }
    fn _dfs(board: &mut Vec<Vec<char>>, s: &Vec<char>, i: usize, j: usize, crt: usize) -> bool {
        if crt == s.len() {
            return true;
        }
        if i >= board.len() || j >= board[0].len() {
            return false;
        }
        if board[i][j] != s[crt] {
            return false;
        }
        board[i][j] = (board[i][j] as u8 ^ 128) as char;
        let valid = if i != 0 {
            Self::_dfs(board, s, i - 1, j, crt + 1)
        } else {
            false
        } || if j != 0 {
            Self::_dfs(board, s, i, j - 1, crt + 1)
        } else {
            false
        } || Self::_dfs(board, s, i + 1, j, crt + 1)
            || Self::_dfs(board, s, i, j + 1, crt + 1);
        board[i][j] = (board[i][j] as u8 ^ 128) as char;
        valid
    }
}
pub fn main() {
    let board: Vec<Vec<char>> = vec![
        vec!['A', 'B', 'C', 'E'],
        vec!['S', 'F', 'C', 'S'],
        vec!['A', 'D', 'E', 'E'],
    ];
    let word = String::from("ABCCED");
    let res = Solution::exist(board, word);
    println!("{}", res);
}
