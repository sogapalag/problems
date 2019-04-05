// rust impl from https://leetcode.com/problems/group-anagrams/discuss/19183/Java-beat-100!!!-use-prime-number
struct Solution;
impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        let primes = [
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,
            97, 101, 103,
        ];
        let mut res: Vec<Vec<String>> = Vec::new();
        use std::collections::HashMap;
        let mut dict: HashMap<i32, usize> = HashMap::new();
        let mut value: usize = 0;
        for s in strs {
            let mut _k = 1;
            for c in s.chars() {
                _k *= primes[c as usize - 'a' as usize];
            }

            match dict.get(&_k) {
                Some(&_v) => res[_v].push(s),
                _ => {
                    dict.insert(_k, value);
                    res.push(vec![s]);
                    value += 1;
                }
            }
        }
        return res;
    }
}

fn main() {
    let strs: Vec<String> = ["eat", "tea", "tan", "ate", "nat", "bat"]
        .iter()
        .map(|&s| s.into())
        .collect();
    let res = Solution::group_anagrams(strs);
    println!("{:?}", res);
}
