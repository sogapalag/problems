//Definition for a binary tree node.
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
    pub fn is_valid_bst(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        let v_inord = Self::inorder_traversal(root);
        Self::is_sorted(&v_inord)
    }
    pub fn is_sorted(v: &Vec<i32>) -> bool {
        if v.len() < 2 {
            return true;
        }
        for i in 0..v.len() - 1 {
            if v[i] >= v[i + 1] {
                return false;
            }
        }
        true
    }
    pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut res: Vec<i32> = Vec::new();
        let mut stack = Vec::new();
        let mut r = root.clone();
        while r.is_some() || !stack.is_empty() {
            while let Some(node) = r {
                stack.push(node.clone());
                r = node.borrow().left.clone();
            }
            r = stack.pop();
            if let Some(node) = r {
                res.push(node.borrow().val);
                r = node.borrow().right.clone();
            }
        }
        res
    }
}
pub fn main() {}
