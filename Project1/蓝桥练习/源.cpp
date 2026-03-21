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