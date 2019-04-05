// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}
use std::cell::RefCell;
use std::rc::Rc;
struct Solution;
impl Solution {
    pub fn level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<i32>> {
        let mut res: Vec<Vec<i32>> = vec![];
        Self::_dfs(&mut res, root, 0);
        res
    }
    fn _dfs(res: &mut Vec<Vec<i32>>, root: Option<Rc<RefCell<TreeNode>>>, level: usize) {
        if let Some(node) = root {
            if level == res.len() {
                res.push(vec![node.borrow().val]);
            } else {
                res[level].push(node.borrow().val);
            }
            Self::_dfs(res, node.borrow().left.clone(), level + 1);
            Self::_dfs(res, node.borrow().right.clone(), level + 1);
        }
    }
}
pub fn main() {}
