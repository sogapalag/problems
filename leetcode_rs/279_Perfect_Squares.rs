use std::cmp;
use std::sync::{Once, ONCE_INIT};
struct Solution;
// init
const CASH_SIZE: usize = 10001;

static mut DPCACHE: &'static mut [i32; CASH_SIZE] = &mut [5; CASH_SIZE];
static START: Once = ONCE_INIT;

impl Solution {
    pub fn num_squares(n: i32) -> i32 {
        //Self::_dp_method(n)
        Self::get_dpcache()[n as usize]
        //Self::do_math(n)
    }
    // 16ms
    fn _dp_method(n: i32) -> i32 {
        let size = n as usize;
        let mut dp: Vec<i32> = Vec::with_capacity(size+1); //like i32::MAX, upper_bound
        dp.push(0);
        for i in 1..=size {
            let mut crt = 5;
            for j in 1..=i {
                if j * j <= i {
                    crt = cmp::min(crt, dp[i - j * j] + 1);
                } else {
                    break;
                }
            }
            dp.push(crt);
        }
        dp[size]
    }
    // 4ms
    fn get_dpcache() -> &'static [i32; CASH_SIZE] {
        unsafe {
            START.call_once(|| {
                Self::_dp_cal();
            });
            DPCACHE
        }
    }
    unsafe fn _dp_cal() {
        DPCACHE[0] = 0;
        for i in 1..CASH_SIZE {
            let mut crt = 5;
            for j in 1..=i {
                if j * j <= i {
                    crt = cmp::min(crt, DPCACHE[i - j * j] + 1);
                } else {
                    break;
                }
            }
            DPCACHE[i] = crt;
        }
    }
    // Lagrange's four-square theorem
    // Legendre's three-square theorem
    // 0ms
    fn do_math(n: i32) -> i32 {
        let is_sq = |x| {
            let k = (x as f64).sqrt() as i32;
            k * k == x
        };
        if is_sq(n) {
            return 1;
        }
        // 4^a(8b+7)
        let mut x = n;
        while x % 4 == 0 {
            x >>= 2;
        }
        if x % 8 == 7 {
            return 4;
        }
        let k = (n as f64).sqrt() as i32;
        for i in 1..=k {
            if is_sq(n - i * i) {
                return 2;
            }
        }
        3
    }
}
pub fn main() {
    let res = Solution::num_squares(1);
    println!("{}", res);
}
