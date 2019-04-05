struct Solution;
impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        let mut res: Vec<Vec<String>> = Vec::new();
        use std::collections::HashMap;
        let mut dict: HashMap<_, usize> = HashMap::new();
        let mut value: usize = 0;
        for s in strs {
            let _k = Self::letters_counter(&s);
            if dict.contains_key(&_k) {
                let _v: usize = *dict.get(&_k).unwrap();
                res[_v].push(s);
            } else {
                dict.insert(_k, value);
                res.push(vec![s]);
                value += 1;
            }
        }
        return res;
    }
    pub fn letters_counter(s: &String) -> [i32; 26] {
        let mut c = [0; 26];

        for x in s.chars() {
            c[x as usize - 'a' as usize] += 1;
        }
        return c;
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
