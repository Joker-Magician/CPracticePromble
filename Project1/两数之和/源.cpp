#include <iostream>
#include <vector>
#include <unordered_map>

class Solution1 {
public:
    /*std::vector<int> twoSum(std::vector<int>& nums, int target) {
        int a, b;
        for (a = 0; a < nums.size(); a++) {
            for (b = a + 1; b < nums.size(); b++) {
                if ((nums[a] + nums[b]) == target)
                    break;
            }
        }
        std::cout << nums[a] << " " << nums[b] << std::endl;
    }*/

    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> hashtable;
        for (int a = 0; a < nums.size(); a++) {
            auto it = hashtable.find((target - nums[a]));
            if (it != hashtable.end()) {
                return { it->second, a };
            }
            hashtable[nums[a]] = a;
        }
        return {};
    }
};

class Solution2 {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int r = 0;
        while (x > r) {
            r = r * 10 + x % 10;
            x /= 10;
        }

        return x == r || x == r / 10;
    }
};



int main() {
    
	return 0;
}

