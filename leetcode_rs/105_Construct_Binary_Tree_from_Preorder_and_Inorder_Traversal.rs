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
use std::collections::HashMap;
use std::rc::Rc;
struct Solution;
impl Solution {
    pub fn build_tree(preorder: Vec<i32>, inorder: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        Self::_iter_build(&preorder, &inorder)
        /////////////////////// recur. with hash
        // let mut map: HashMap<i32, usize> = HashMap::new();
        // for (i, &e) in inorder.iter().enumerate() {
        //    map.insert(e, i);
        // }
        // Self::_helper_hash(&preorder, 0, preorder.len(), 0, &map)
        /////////////////////// recur. brute-find
        // Self::_helper(&preorder, &inorder)
    }
    // relative addr
    fn _helper(_pre: &[i32], _in: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
        if _pre.len() == 0 {
            return None;
        }
        let value = _pre[0];
        let root = Rc::new(RefCell::new(TreeNode::new(value)));
        for (i, &e) in _in.iter().enumerate() {
            if e == value {
                root.borrow_mut().left = Self::_helper(&_pre[1..=i], &_in[0..i]);
                root.borrow_mut().right = Self::_helper(&_pre[i + 1..], &_in[i + 1..]);
                break;
            }
        }
        Some(root)
    }
    // absolute addr
    fn _helper_hash(
        _pre: &Vec<i32>,
        _pre_l: usize,
        _pre_r: usize,
        _in_l: usize,
        map: &HashMap<i32, usize>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        if _pre_l == _pre_r {
            return None;
        }
        let value = _pre[_pre_l];
        let root = Rc::new(RefCell::new(TreeNode::new(value)));
        let i = *map.get(&value).unwrap();
        let offset = i - _in_l;
        root.borrow_mut().left =
            Self::_helper_hash(_pre, _pre_l + 1, _pre_l + offset + 1, _in_l, map);
        root.borrow_mut().right = Self::_helper_hash(_pre, _pre_l + offset + 1, _pre_r, i + 1, map);
        Some(root)
    }
    fn _iter_build(_pre: &Vec<i32>, _in: &Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut stack = Vec::new();
        let mut p: usize = 0;
        let mut i: usize = 0;
        use std::i32::MIN;
        let mut r = Rc::new(RefCell::new(TreeNode::new(MIN)));

        let _r = r.clone();

        while i != _in.len() {
            let node_r = Rc::new(RefCell::new(TreeNode::new(_pre[p])));
            stack.push(node_r.clone());
            r.borrow_mut().right = Some(node_r.clone());
            r = node_r;
            // push till eq
            while _pre[p] != _in[i] {
                p += 1;
                let node_l = Rc::new(RefCell::new(TreeNode::new(_pre[p])));
                stack.push(node_l.clone());
                r.borrow_mut().left = Some(node_l.clone());
                r = node_l;
            }
            // pop till to_right
            // last equal's.
            while !stack.is_empty() && {
                let v = stack.last().unwrap().borrow().val;
                v == _in[i]
            } {
                i += 1;
                r = stack.pop().unwrap();
            }
            p += 1;
        }
        let r = _r.borrow().right.clone();
        r
    }
}
pub fn main() {
    let pre = vec![3, 9, 20, 15, 7];
    let ino = vec![9, 3, 15, 20, 7];
    let root = Solution::build_tree(pre, ino);
}
