#include "DataStruct.hpp"
#include "Acwing_Practice.hpp"

void SuffixSubstringSorting(std::string str) {
    std::vector<std::pair<std::string, int>> substring;
    int length = str.length() - 1;
    for (int i = length; i >= 0; i--) {
        auto temp = str.substr(i);
        int ffont = static_cast<int>(temp[0]);
        substring.emplace_back(temp, ffont);
        // std::cout << temp << '\n'; 
    }

    while (substring.size() > 0) {
        int min_value = INT_MAX;
        int min_index = 0;
        for (int i = 0; i < substring.size(); i++) {
            if (substring[i].second < min_value) {
                min_index = i;
                min_value = substring[i].second;
            }
        }

        std::cout << substring[min_index].first << '\n';
        substring.erase(substring.begin() + min_index);
        min_value = INT_MAX;
        min_index = 0;
    }

    int wait = 1;
}

/*勒让德定理*/
void FactorialZero(int n, int& res) {
    if (n <= 4) {
        res = 0;
        return;
    }

    res = 0;
    long long int fact = n;
    for (int i = n - 1; i > 0; i--) {
        fact *= i;
    }

    std::string str = std::to_string(fact);
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '0')
            res++;
    }
    int wait = 1;
}

/*动态规划*/
int LCS(std::vector<int> s1, std::vector<int> s2) {

    int size = s1.size();
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(size + 1, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (s1[i] == s2[j])
                dp[i + 1][j + 1] = dp[i][j] + 1;
            else {
                auto temp = std::max(dp[i][j + 1], dp[i + 1][j]);
                dp[i + 1][j + 1] = temp;
            }
        }
    }

    return dp[size][size];
}

/*DFS + 剪枝 + 全排列*/
int res = 0;

bool IsSqaure(int a, int b) {
    int temp = a + b;
    int num = static_cast<int>(std::sqrt(temp));
    return num * num == temp;
}

void DfsForSquare(std::vector<int>& A, int count, int prev, std::vector<bool>& visited) {
    if (count == A.size()) {
        res++;
        return;
    }

    for (int i = 0; i < A.size(); i++) {
        int j = i - 1;
        if (i > 0 && j > 0)
            if (!visited[j] && A[j] == A[i])
                continue;
        if (!visited[i] && (prev == -1) || IsSqaure(prev, A[i]))
        {
            visited[i] = true;
            DfsForSquare(A, count + 1, A[i], visited);
            visited[i] = false;
        }
    }
    return;
}

int SquareVector(int n, std::vector<int> A) {
    std::vector<bool> visited(A.size(), false);
    auto temp_tree = A;
    std::sort(temp_tree.begin(), temp_tree.end());
    DfsForSquare(temp_tree, 1, -1, visited);
    return res;
}

#pragma region 前后序排列组合
/*动态规划 + DFS*/
int DfsForFrontRare(std::vector<std::vector<int>>& dp, int n,
    std::string pre, std::string post) {
    int sum = 1;
    int cnt = 0;
    pre.erase(pre.begin());
    post.erase(post.end() - 1);
    for (int i = 0, j = 0; i < pre.size();) {
        while (pre[i] != post[j])
            j++;
        std::string sub_pre = pre.substr(i, j - i + 1);
        std::string sub_post = post.substr(i, j - i + 1);
        sum *= DfsForFrontRare(dp, n,
            sub_pre,
            sub_post);
        cnt++;
        i = ++j;
    }
    return sum * dp[n][cnt];
}

int CalcMidSeq(int n, std::string pre, std::string post) {
    std::vector<std::vector<int>> dp(25,
        std::vector<int>(25, 0));

    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) dp[i][j] = 1;
            else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
    int result = DfsForFrontRare(dp, n, pre, post);
    return result;
}
#pragma endregion

