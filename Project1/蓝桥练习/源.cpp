//#include<iostream>
//
//int main(){
//	int a, b;
//	std::cin >> a >> b;
//
//	int c, d;
//	c = a / b;
//	d = a % b;
//
//	std::cout << c << " " << d;
//	return 0;
//}

//#include <iostream>
//#include <cmath>
//
//int main() {
//	int a, b;
//	std::cin >> a >> b;
//
//	int ans = 1;
//	int base = a % 7;
//
//	for (int i = 0; i < b; i++) {
//		ans = (ans * base) % 7;
//	}
//	       
//	switch (ans) {
//	case 1:
//		std::cout << "Monday";
//		break;
//	case 2:
//		std::cout << "Tuesday";
//		break;
//	case 3:
//		std::cout << "Wednesday";
//		break;
//	case 4:
//		std::cout << "Thursday";
//		break;
//	case 5:
//		std::cout << "Friday";
//		break;
//	case 6:
//		std::cout << "Saturday";
//		break;
//	case 0:
//		std::cout << "Sunday";
//		break;
//	default:
//		std::cout << "错误";
//	}
// 
// // 建立一个打表数组，下标 0 对应 Sunday，1 对应 Monday...
// string days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
// 
// // 直接用计算出的余数作为下标，一行代码搞定输出！
// std::cout << days[ans] << '\n';
// 
//	return 0;
//}

//#include <iostream>
//
//int main() {
//	int a, b;
//	long long n = 1;
//	long long c = 0;
//
//	long long MOD = 1000000000;
//
//	for (a = 1; a < 40; a++) {
//		n = (n * a) % MOD;
//		c = (c + n) % MOD;
//	}
//
//	std::cout << c;
//	return 0;
//}

//#include<iostream>
//
//int main() {
//	int a = 20;
//	int cnt = 1;
//	for (a = 20; cnt < 22; cnt++) {
//		a = (20 * a) % 7;
//	}
//	
//	int today = 6;
//	int fianl_day = (today + a) % 7;
//
//	if (fianl_day == 0) {
//		std::cout << 7;
//	}
//	else {
//		std::cout << fianl_day;
//	}
//
//	return 0;
//}

//#include <iostream>
//
//int main() {
//	long long k, a, q;
//	std::cin >> k >> a >> q;
//
//	long long MOD = 722733748;
//	int cnt ;
//	long long curr = a % MOD;
//	long long fianl = a % MOD;
//
//	for (cnt = 1; cnt < k; cnt++) {
//		curr = (curr * q) % MOD;
//		fianl = (fianl * curr) % MOD;
//	}
//
//	std::cout << fianl;
//
//	return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//int main() {
//    int n;
//    cin >> n;
//
//    // 1. 外层循环：遍历 2 到 n 的每一个数字
//    for (int i = 2; i <= n; i++) {
//
//        // sum 用来累加因数。
//        // 因为 1 肯定是任何数的因数，所以我们直接把 sum 初始值设为 1。
//        // 这样一来，内层循环就可以从 2 开始找了。
//        int sum = 1;
//
//        // 2. 内层循环：高效找因数，条件是 j 的平方不超过 i
//        for (int j = 2; j * j <= i; j++) {
//
//            // 如果 j 能被 i 整除，说明找到了因数
//            if (i % j == 0) {
//                sum += j; // 把小的那个因数加进去
//
//                // 还要把配对的大的那个因数 (i / j) 也加进去！
//                // 陷阱防范：如果 i 是 9，j 是 3，3*3=9，不要把两个 3 都加进去。
//                if (j * j != i) {
//                    sum += i / j;
//                }
//            }
//        }
//
//        // 3. 检查：因数之和等不等于它自己
//        if (sum == i) {
//            cout << i << '\n';
//        }
//    }
//
//    return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//// 写一个专门判断素数的辅助函数，让逻辑更清晰
//bool isPrime(int x) {
//    if (x < 2) return false; // 0 和 1 不是素数
//
//    // 核心优化：只检查到平方根！(这和上一题的 j * j <= i 是一模一样的)
//    for (int j = 2; j * j <= x; j++) {
//        if (x % j == 0) {
//            return false; // 只要找到一个因数，立刻判死刑，不是素数！
//        }
//    }
//    return true; // 如果全都没找到，就是素数，无罪释放！
//}
//
//int main() {
//    int n;
//    cin >> n;
//    int count = 0; // 记录素数的个数
//
//    // 遍历从 2 到 n 的每一个数字
//    for (int i = 2; i <= n; i++) {
//        if (isPrime(i)) {
//            count++;
//        }
//    }
//    cout << count << '\n';
//    return 0;
//}


//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//    int n;
//    cin >> n;
//
//    // 创建一个大小为 n+1 的布尔数组，初始全为 true
//    // true 代表“目前认为它是素数”，false 代表“被划掉了，是合数”
//    vector<bool> is_prime(n + 1, true);
//
//    // 0 和 1 无论如何都不是素数，先强行划掉
//    is_prime[0] = false;
//    is_prime[1] = false;
//
//    int count = 0; // 记录素数个数
//
//    // 开始从 2 扫到 n
//    for (int i = 2; i <= n; i++) {
//        if (is_prime[i] == true) { // 发现了一个幸存者！它是素数！
//            count++;
//
//            // 开始大屠杀：把这个素数在 n 以内的所有倍数全部划掉
//            // 优化陷阱：i * i 可能会超过 int 的最大值导致溢出，所以用 long long
//            for (long long j = (long long)i * i; j <= n; j += i) {
//                is_prime[j] = false;
//            }
//        }
//    }
//
//    cout << count << '\n';
//    return 0;
//}

//#include <iostream>
//#include <vector>
//
//int main() {
//	int n;
//	std::cin >> n;
//
//	std::vector<bool> is_prime(n + 1, true);
//	int count = 0;
//	std::vector<int> p;
//	int a = 0;
//
//	is_prime[0] = false;
//	is_prime[1] = false;
//
//	for (int i = 2; i <= n; i++) {
//		if (is_prime[i] == true) {
//			count++;
//			p.push_back(i);
//
//			for (long long j = (long long)i * i; j <= n; j += i) {
//				is_prime[j] = false;
//			}
//			a++;
//		}
//	}
//
//	int cnt = 0;
//	for (int i = 0; i < p.size() - 1; i++) {
//		if ((p[i + 1] - p[i]) == 2) {
//			std::cout << p[i] << " " << p[i + 1] << '\n';
//			cnt++;
//		}
//	}
//	if (cnt == 0) {
//		std::cout << "empty";
//	}
//
//	return 0;
//}

//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//// 专门为反转后的数字准备的“素数检测仪”（上节课学过的试除法）
//bool isPrimeHelper(int x) {
//    if (x < 2) return false;
//    for (int i = 2; i * i <= x; i++) {
//        if (x % i == 0) return false;
//    }
//    return true;
//}
//
//int main() {
//    int M, N;
//    cin >> M >> N;
//
//    // 1. 埃氏筛法，制作 0 到 N 的素数户口本
//    vector<bool> is_prime(N + 1, true);
//    is_prime[0] = false;
//    is_prime[1] = false;
//    for (int i = 2; i <= N; i++) {
//        if (is_prime[i] == true) {
//            for (long long j = (long long)i * i; j <= N; j += i) {
//                is_prime[j] = false;
//            }
//        }
//    }
//
//    int cnt = 0;
//    bool is_first = true; // 极其好用的小技巧：用来控制逗号的输出
//
//    for (int i = M; i <= N; i++) {
//        // 如果 i 本身连素数都不是，直接跳过，不用费劲反转了
//        if (is_prime[i] == false) continue;
//
//        // 2. 正确的反转逻辑
//        int temp = i; // 用 temp 代替 j，不破坏原数字
//        int reversed_num = 0; // 用名字更清晰的变量代替 n
//        while (temp > 0) {    // 修复 Bug 1：必须是 > 0
//            reversed_num = reversed_num * 10 + temp % 10;
//            temp /= 10;
//        }
//
//        // 3. 查验反转后的数字是不是素数（使用独立的函数，防止越界！）
//        if (isPrimeHelper(reversed_num)) {
//            // 4. 完美的逗号输出逻辑
//            if (!is_first) {
//                cout << ","; // 如果不是第一个，就先打个逗号
//            }
//            cout << i;       // 输出数字本身，而不是 true/1
//            is_first = false; // 第一个输出完了，关掉开关
//            cnt++;
//        }
//    }
//
//    // 5. 注意题目要求的大小写
//    if (cnt == 0) {
//        cout << "No\n"; // 不是 NO
//    }
//    else {
//        cout << '\n';   // 换个行是个好习惯
//    }
//
//    return 0;
//}

//#include <iostream>
//#include <vector>
//
//int main() {
//    // 算法竞赛提速黑魔法（解决输入输出慢的问题）
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//
//    int N;
//    std::cin >> N;
//
//    // 1. 埃氏筛法找素数（记得加上 if 判断）
//    std::vector<bool> is_prime(N + 1, true);
//    is_prime[0] = false;
//    is_prime[1] = false;
//    for (int i = 2; i <= N; i++) {
//        if (is_prime[i] == true) { 
//            for (long long j = (long long)i * i; j <= N; j += i) {
//                is_prime[j] = false;
//            }
//        }
//    }
//
//    // 2. 验证哥德巴赫猜想
//    for (int i = 4; i <= N; i += 2) {
//
//        // 只需要遍历第一个加数 j。
//        // 因为 j + k = i，而且 j 要尽可能小，所以 j 只要查到 i / 2 就可以了
//        // (如果 j 超过 i/2，剩下的 k 就会比 j 小，这就和"第一个加数最小"矛盾了)
//        for (int j = 2; j <= i / 2; j++) {
//
//            // 核心数学关系：另一个加数必定是 i - j
//            // 直接查户口本，看 j 和 i - j 是不是都是素数
//            if (is_prime[j] == true && is_prime[i - j] == true) {
//
//                // 找到了！输出答案
//                // 竞赛细节：用 '\n' 代替 std::endl 可以大幅提升输出速度防止超时
//                std::cout << i << "=" << j << "+" << (i - j) << '\n';
//
//                // 题目要求：输出第一个加数最小的方案。
//                // 因为我们的 j 是从 2 开始从小到大找的，找到的第一个绝对是 j 最小的！
//                // 找到了就直接跳出内层循环，去查下一个偶数 i
//                break;
//            }
//        }
//    }
//
//    return 0;
//}

/*假设我们现在要计算所有 p 的倍数（p 可以是 5, 25, 125...）的贡献总和。
在这个范围里，最大的 p 的倍数是 M * p，其中 M = [n/p]（也就是 n 除以 p 的商）。
我们要计算的贡献和是：S = (n - 1p + 1) + (n - 2p + 1) + (n - 3p + 1) + ··· + (n - Mp + 1)把这个长长的式子稍微整理一下
（把 (n+1) 提出来，把 -p 提出来）：
S = M * (n + 1) - p * (1 + 2 + 3 + ··· + M)后面的 (1 + 2 + ··· + M) 不就是高斯发明的等差数列求和吗！
直接变成 M(M+1)/2。
所以，对于任何一个次幂 p，它能提供的因子 5 的总数，一行公式就能算出来：S = M * (n + 1) - p * M *(M+1)/2 */

//#include <iostream>
//
//using namespace std;
//
//int main() {
//    // 算法竞赛起手式
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    // 因为 n 最大是 10^8，最终的零的个数会非常庞大，极易超过 int 的上限(21亿)
//    // 所以参与计算的所有变量，必须全部开 long long！
//    long long n;
//    cin >> n;
//
//    long long total_zeros = 0; // 记录所有的 0（即因子 5 的总和）
//
//    // p 代表 5, 25, 125, 625...
//    for (long long p = 5; p <= n; p *= 5) {
//
//        // M 代表 n 里面有多少个 p 的倍数
//        long long M = n / p;
//
//        // 套用我们刚刚推导出的终极公式！
//        // 因为除以 2，为了防止奇数除法出问题，M * (M + 1) 必定是偶数，可以直接除。
//        long long contribution = M * (n + 1) - p * (M * (M + 1) / 2);
//
//        total_zeros += contribution;
//    }
//
//    cout << total_zeros << '\n';
//
//    return 0;
//}

//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int n, m;
//    cin >> n >> m;
//
//    // 1. 物理容量：防崩溃的底层大数组，写死 40005
//    const int SAFE_SIZE = 40005;
//    vector<bool> has_A(SAFE_SIZE, false);
//    vector<bool> has_B(SAFE_SIZE, false);
//
//    for (int i = 0; i < n; i++) {
//        int val;
//        cin >> val;
//        has_A[val] = true;
//    }
//    for (int i = 0; i < m; i++) {
//        int val;
//        cin >> val;
//        has_B[val] = true;
//    }
//
//    // 2. 逻辑上限：这道题真正允许的 S 的最大值
//    int limit = n + m;
//
//    // 3. 制作素数表，只需要做到 limit 就可以了（省时间）
//    vector<bool> is_prime(limit + 1, true);
//    // 注意处理一下边界情况，如果 limit < 2，直接就是 0 种魔法
//    if (limit >= 0) is_prime[0] = false;
//    if (limit >= 1) is_prime[1] = false;
//
//    for (int i = 2; i <= limit; i++) {
//        if (is_prime[i] == true) {
//            for (long long j = (long long)i * i; j <= limit; j += i) {
//                is_prime[j] = false;
//            }
//        }
//    }
//
//    int cnt = 0;
//
//    // 4. 逆向枚举 S，严格遵守题目约束，只跑到 limit！
//    for (int S = 2; S <= limit; S++) {
//        if (!is_prime[S]) continue;
//
//        for (int x = 1; x < S; x++) {
//            if (has_A[x] == true && has_B[S - x] == true) {
//                cnt++;
//                break;
//            }
//        }
//    }
//
//    cout << cnt << '\n';
//
//    return 0;
//}

//#include <iostream>
//#include <vector>
//
//int main()
//{
//	int n;
//	std::cin >> n;
//
//	std::vector<bool> is_prime(n + 1, true);
//	is_prime[0] = false;
//	is_prime[1] = false;
//
//	for (int i = 2; i <= n; i++) {
//		if (is_prime[i] == true) {
//			for (long long j = (long long)i * i; j <= n; j += i) {
//				is_prime[j] = false;
//			}
//		}
//	}
//
//	for (int i = 2; i <= n; i++) {
//		if (is_prime[i] != true) continue;
//		for (int j = 2; j <= n; j++) {
//			if (is_prime[j] != true) continue;
//			int k = n - i - j;
//			if (k >=2 && is_prime[k] == true) {
//				std::cout << i << " " << j << " " << n - i - j;
//				return 0;
//			}
//		}
//	}
//
//	return 0;
//}

//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <algorithm> // 为了使用 max 函数
//
//using namespace std;
//
//int main() {
//    // 提速黑魔法
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    // 必须全部用 long long，防止各种奇怪的溢出
//    long long L, R;
//    if (!(cin >> L >> R)) return 0;
//
//    // --- 第 1 步：找出 2 到 sqrt(R) 内的所有素数 ---
//    long long limit = sqrt(R) + 1;
//    vector<bool> is_small_prime(limit + 1, true);
//    vector<long long> small_primes; // 用一个专门的盒子把小素数存起来
//
//    is_small_prime[0] = false;
//    is_small_prime[1] = false;
//    for (long long i = 2; i <= limit; i++) {
//        if (is_small_prime[i] == true) {
//            small_primes.push_back(i); // 存入盒子
//            for (long long j = i * i; j <= limit; j += i) {
//                is_small_prime[j] = false;
//            }
//        }
//    }
//
//    // --- 第 2 步：只筛 [L, R] 这个小区间 ---
//    // 这个数组只有 100万 的大小，绝对不会 MLE！
//    // 下标 i 代表真实的数字 L + i
//    vector<bool> is_prime_LR(R - L + 1, true);
//
//    for (long long p : small_primes) {
//        // 数学难点：找到大于等于 L 的最小的 p 的倍数！
//        // 比如 L=10, p=3，我们要找到 12。公式是 ((L + p - 1) / p) * p
//        // 同时，划掉的倍数必须至少是 p 的 2 倍，不能把素数 p 本身划掉！
//        long long start = max(2LL * p, ((L + p - 1) / p) * p);
//
//        // 开始精准打击，每次步长为 p
//        for (long long j = start; j <= R; j += p) {
//            is_prime_LR[j - L] = false; // 把真实数字 j 映射到数组下标 j - L
//        }
//    }
//
//    // --- 第 3 步：统计答案 ---
//    // 唯一的特判：如果 L 是 1，1 不是素数，手动划掉
//    if (L == 1) {
//        is_prime_LR[0] = false;
//    }
//
//    int cnt = 0;
//    for (long long i = 0; i <= R - L; i++) {
//        if (is_prime_LR[i] == true) {
//            cnt++;
//        }
//    }
//
//    cout << cnt << '\n';
//
//    return 0;
//}

///欧拉筛法：任何一个合数，只能被它自己的『最小质因数』划掉一次
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//    int n;
//    cin >> n;
//
//    vector<bool> is_prime(n + 1, true);
//    is_prime[0] = false;
//    is_prime[1] = false;
//
//    // 专门准备一个“素数档案馆”，用来存放目前找到的所有素数
//    vector<int> primes;
//
//    // 外层循环：必须老老实实从 2 走到 n (不能是 sqrt(n) 了！)
//    for (int i = 2; i <= n; i++) {
//
//        // 1. 如果 i 没被划掉，那它就是素数，立刻收录进档案馆
//        if (is_prime[i]) {
//            primes.push_back(i);
//        }
//
//        // 2. 遍历档案馆里目前已知的所有素数
//        for (int j = 0; j < primes.size(); j++) {
//            int p = primes[j]; // 拿出一个素数 p
//
//            // 如果 i 和 p 乘起来已经超过范围了，直接结束内层循环
//            if (1LL * i * p > n) break;
//
//            // 划掉合数：用当前的数 i，乘以档案馆里的素数 p
//            is_prime[i * p] = false;
//
//            // 欧拉筛的灵魂！！！如果 i 能被 p 整除，立刻停止！
//            if (i % p == 0) {
//                break;
//            }
//        }
//    }
//
//    cout << "找到素数个数: " << primes.size() << '\n';
//    return 0;
//}

//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//int main() {
//	int N, M;
//	std::cin >> N  >> M;
//
//	std::vector<int> spf(M + 1);
//
//	for (int i = 2; i <= M; i++) {
//		spf[i] = i;
//	}
//
//	for (int i = 2; i * i <= M; i++) {
//		if (spf[i] == i) {
//			for (long long j = i * i; j <= M; j += i) {
//				if (spf[j] == j) {
//					spf[j] = i;
//				}
//			}
//		}
//	}
//	
//	std::vector<int> cnt(M + 1, 0);
//	int max_cnt = 0;
//
//	for (int i = 2; i <= M; i++) {
//		cnt[i] = cnt[i / spf[i]] + 1;
//		if (i >= N) {
//			max_cnt = std::max(max_cnt, cnt[i]);
//		}
//	}
//
//	std::cout << max_cnt;
//
//	return 0;
//}

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXP = 4000;
vector<int> primes;
bool is_prime[MAXP + 1];

// 预处理 4000 以内的素数（埃氏筛法）
void init_primes() {
    fill(is_prime, is_prime + MAXP + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXP; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= MAXP; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

// 检查是否为完全平方数（注意精度，使用 long double 版的 sqrtl）
bool is_sqr(long long n) {
    long long r = round(sqrtl(n));
    return r * r == n;
}

// 检查是否为完全立方数
bool is_cub(long long n) {
    long long r = round(cbrtl(n));
    return r * r * r == n;
}

void solve() {
    long long a;
    cin >> a;

    // 第一步：用 4000 以内的质数去扒它
    for (int p : primes) {
        if (a % p == 0) {
            int count = 0;
            // 把这个质数 p 剥干净，并数一下有几个
            while (a % p == 0) {
                a /= p;
                count++;
            }
            // 只要发现某个质因数只有 1 个，直接没救，输出 no
            if (count == 1) {
                cout << "no\n";
                return;
            }
        }
    }

    // 第二步：判断剩下的部分
    if (a == 1) {
        cout << "yes\n";
    }
    else if (is_sqr(a) || is_cub(a)) {
        cout << "yes\n"; // 剩下的是完全平方或完全立方，也行得通
    }
    else {
        cout << "no\n";  // 否则必定藏着指数为 1 的质数
    }
}

int main() {
    // 算法竞赛起手式：解除输入输出绑定，大幅提升 cin/cout 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes(); // 提前准备好子弹（素数表）

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}