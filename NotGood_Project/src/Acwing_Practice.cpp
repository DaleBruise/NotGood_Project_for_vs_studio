#include "Acwing_Practice.hpp"

#pragma region 前半部分练习
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

void choir_formation() {
    std::vector<int> formation{ 8, 186, 186, 150, 200, 160, 130, 197, 220 };
    int size = formation.size();
    std::vector<int> f, g;
    for (int i = 0; i < size; ++i) {
        f.push_back(1);
        g.push_back(1);
    }

    for (int i = size - 2; i >= 0; --i)
        for (int j = i + 1; j < size; ++j)
            if (formation[i] > formation[j] && f[i] <= f[j] + 1)
                f[i] = f[j] + 1;

    for (int i = 1; i < size; ++i)
        for (int j = 0; j < i; ++j)
            if (formation[i] > formation[j] && g[i] <= g[j] + 1)
                g[i] = g[j] + 1;

    int res = 0;
    std::vector<int> s(size, 0);
    for (int i = 0; i < size; ++i) {
        s[i] = f[i] + g[i] - 1;
        if (s[i] > res)
            res = s[i];
    }
    res = size - res;
    std::cout << "The result is: " << res << '\n';
}
#pragma endregion

#pragma region SJTU Computer Science Entrance Examination Questions

#pragma region qubic_matrix_number
bool is_sqaured(int x) {
    int s = static_cast<int>(std::sqrt(x));
    return s * s == x;
}

void dfs(const std::vector<int>& f, std::vector<int>& vis,
    int size, int last, int remain, int& res) {
    if (remain == 0) {
        ++res;
        return;
    }

    for (int i = 1; i <= size; ++i) {
        if (vis[i])
            continue;

        int temp_sum = last + f[i];
        if (is_sqaured(temp_sum) || last == -1) {
            vis[i] = 1;
            dfs(f, vis, size, f[i], remain - 1, res);
            vis[i] = 0;
        }
    }
}

void qubic_matrix_number() {
    int size;
    std::cin >> size;

    std::vector<int> f(size + 1, 0);
    f[0] = -1;
    for (int i = 1; i <= size; ++i)
        std::cin >> f[i];

    for (auto it : f)
        std::cout << it << ' ';

    std::vector<int> vis(size + 1, 0);
    int res = 0;
    dfs(f, vis, size, -1, size, res);
    std::cout << '\n' << res;
}
#pragma endregion

#pragma region old_bills
bool check(std::vector<int>& nums, int amount, int& myriabit, int& unit, int& unit_price) {
    int sum = 0;
    int times = 1000;
    for (const auto& it : nums) {
        sum += it * times;
        times /= 10;
    }

    for (int i = 9; i > 0; --i)
        for (int j = 9; j >= 0; --j) {
            int temp = sum + i * 10000 + j * 1;
            if (temp % amount == 0) {
                myriabit = i;
                unit = j;
                unit_price = temp / amount;
                return true;
            }
        }

    myriabit = 0;
    unit = 0;
    unit_price = 0;
    return false;
}

void old_bills() {
    std::vector<std::pair<int, std::vector<int>>> inputs;
    std::vector<std::vector<int>> outputs;
    int amount;

    while (std::cin >> amount) {
        if (amount == -1)
            break;

        std::vector<int> nums(3, 0);
        for (int i = 0; i < 3; ++i)
            std::cin >> nums[i];

        std::pair<int, std::vector<int>> temp_pair = { amount, nums };
        int myriabit = 0;
        int unit = 0;
        int unit_price = 0;

        auto flag = check(temp_pair.second, temp_pair.first, myriabit, unit, unit_price);
        std::vector<int> output;
        if (flag) {
            output.reserve(3);
            output.push_back(myriabit);
            output.push_back(unit);
            output.push_back(unit_price);
        }
        else
            output.push_back(0);

        outputs.emplace_back(output);
    }

    for (const auto& its : outputs) {
        for (const auto& it : its)
            std::cout << it << ' ';
        std::cout << '\n';
    }
}
#pragma endregion

#pragma region reverse_number
inline int reverse(int x) {
    int reversed = 0;
    while (x != 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    return reversed;
}

bool check(int a, int b) {
    int reversed_a = reverse(a);
    int reversed_b = reverse(b);

    int origin_sum = a + b;
    int reversed_sum = reverse(a + b);
    if (reversed_sum == reversed_a + reversed_b)
        return true;
    else
        return false;
}

void reverse_number() {
    std::vector<int> outputs;
    std::vector<int*> number_sets;
    int a, b;
    while (std::cin >> a) {
        if (a == -1)
            break;

        std::cin >> b;

        bool flag = check(a, b);
        if (flag)
            outputs.push_back(a + b);
        else
            outputs.push_back(0);
    }

    for (const auto& it : outputs) {
        if (it == 0)
            std::cout << "NO" << '\n';
        else
            std::cout << it << '\n';
    }
}
#pragma endregion

#pragma region factorial_zero
void factorial_zero() {
    int n;
    std::cin >> n;

    int count = 0;
    for (long long i = 5; n / i > 0; i *= 5)
        count += n / i;

    std::cout << count;
}
#pragma endregion

#pragma region split_array
void dp(std::vector<int>& inputs, int& sum_a, int& sum_b) {
    long long sum = 0;
    for (const auto& it : inputs)
        sum += it;

    long long target = sum / 2;
    std::vector<int> dp(target + 1, 0);
    dp[0] = 1; // 1 for true, 0 for false;
    for (const auto& num : inputs)
        for (int i = target; i >= num; --i)
            if (dp[i - num] == 1)
                dp[i] = 1;

    int res = 0;
    for (int i = target; i >= 0; --i)
        if (dp[i] == 1)
        {
            res = i;
            break;
        }

    sum_a = sum - res;
    sum_b = res;
}

void split_array() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line)) {

        if (line.empty()) continue;

        std::istringstream iss(line);
        std::vector<int> inputs;
        int num;
        while (iss >> num) {
            inputs.push_back(num);
        }

        int sum_a = 0;
        int sum_b = 0;
        dp(inputs, sum_a, sum_b);

        if (sum_a >= sum_b)
            std::cout << sum_a << ' ' << sum_b;
        else
            std::cout << sum_b << ' ' << sum_a;
    }
}
#pragma endregion

#pragma region suffix_substring_sorting
void suffix_substring_sorting() {
    std::string s;
    std::cin >> s;

    std::set<std::string> sub_strings;
    int size = s.length();
    for (int i = 0; i < size; ++i) {
        std::string sub_string = s.substr(i);
        sub_strings.insert(sub_string);
    }

    for (auto it = sub_strings.begin(); it != sub_strings.end(); ++it) {
        std::cout << *it << '\n';
    }
}

#pragma endregion

#pragma region preceding_subsequent
int dfs(const std::vector<std::vector<int>>& dp,
    std::string& pre, std::string& post, int m_ary) {
    int cnt = 0;
    int sum = 1;
    pre.erase(pre.begin());
    post.erase(post.end());
    for (int i = 0, j = 0; i < pre.size();) {
        while (pre[i] != post[j])
            ++j;

        std::string sub_pre = pre.substr(i, j - i + 1);
        std::string sub_post = post.substr(i, j - i + 1);
        sum *= dfs(dp, sub_pre, sub_post, m_ary);

        ++cnt;
        i = ++j;
    }
    return sum * dp[m_ary][cnt];
}

void preceding_subsequent() {
    std::vector<std::vector<int>> c(25, std::vector<int>(25, 0));
    for (int i = 0; i <= 20; ++i)
        for (int j = 0; j <= i; ++j) {
            if (j == 0)
                c[i][j] = 1;
            else
                c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }

    int m_ary = 0;
    std::string str1;
    std::string str2;
    while (std::cin >> m_ary >> str1 >> str2)
        std::cout << dfs(c, str1, str2, m_ary) << '\n';

}
#pragma endregion

#pragma region pouring_quiz
void dfs(int A, int B, int C,
    int a, int b, int c,
    std::vector<int>& res,
    std::set<std::pair<int, int>>& sets,
    std::set<int>& set_c) {
    if (sets.count({ a, b }) && set_c.count(c))
        return;
    else
    {
        sets.insert({ a, b });
        set_c.insert(c);
    }

    if (res[c] == 0)
        res[c] = 1;

    /* C->A */
    if (c < (A - a))
        dfs(A, B, C, a + c, b, 0, res, sets, set_c);
    else
        dfs(A, B, C, A, b, c - (A - a), res, sets, set_c);

    /* C->B */
    if (c < (B - b))
        dfs(A, B, C, a, b + c, 0, res, sets, set_c);
    else
        dfs(A, B, C, a, B, c - (B - b), res, sets, set_c);

    /* B->A */
    if (b < (A - a))
        dfs(A, B, C, a + b, 0, c, res, sets, set_c);
    else
        dfs(A, B, C, A, b - (A - a), c, res, sets, set_c);

    /* B->C */
    if (b < (C - c))
        dfs(A, B, C, a, 0, c + b, res, sets, set_c);
    else
        dfs(A, B, C, a, b - (C - c), C, res, sets, set_c);

    /* A->B */
    if (a < (B - b))
        dfs(A, B, C, 0, b + a, c, res, sets, set_c);
    else
        dfs(A, B, C, a - (B - b), B, c, res, sets, set_c);

    /* A->C */
    if (a < (C - c))
        dfs(A, B, C, 0, b, c + a, res, sets, set_c);
    else
        dfs(A, B, C, a - (C - c), b, C, res, sets, set_c);

}


void pouring_quiz() {
    int a, b, c;
    while (std::cin >> a >> b >> c) {
        if (a == -1)
            break;

        int max_size = std::max(a, std::max(c, b));
        std::vector<int> res(max_size + 1, 0);
        std::set<std::pair<int, int>> sets;
        std::set<int> set_c;
        dfs(a, b, c, 0, 0, c, res, sets, set_c);

        int count = 0;
        for (const auto& it : res)
            if (it == 1)
                ++count;
        std::cout << count << '\n';
    }
}
#pragma endregion

#pragma region remainder_quiz
std::map<int, int> factorize(int x) {
    std::map<int, int> factors;
    for (int i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            ++factors[i];
            x /= i;
        }
    }
    if (x > 1)
        ++factors[x];

    return factors;
}

int count_factor_in_factors(int n, int p) {
    int sum = 0;
    int power = p;
    while (power <= n) {
        sum += n / power;
        power *= p;
    }
    return sum;
}

void remainder_quiz() {
    int n, a;
    std::cin >> n >> a;

    auto factors = factorize(a);
    int min_k = INT_MAX;
    for (const auto& [p, exp] : factors) {
        int count = count_factor_in_factors(n, p);
        int k = count / exp;
        if (k < min_k)
            min_k = k;
    }

    std::cout << min_k << '\n';
}
#pragma endregion

#pragma region kth_prime
void kth_prime() {
    std::vector<int> prime(10100, 0);
    int num = 0;
    for (int i = 2; i <= 105000; ++i) {
        int flag = 1;
        for (int j = 2; j <= std::sqrt(i); ++j)
            if (i % j == 0)
                flag = 0;

        if (flag)
            prime[num++] = i;
    }

    int k = 0;
    while (std::cin >> k)
        std::cout << prime[k - 1] << '\n';
}
#pragma endregion

#pragma region get_mid_value
void get_mid_value() {

}
#pragma endregion

#pragma region date_delta
inline bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline void in_year_sum(const std::vector<int>& leap, const std::vector<int> non_leap,
    int m, int size, bool is_leap,
    long long& sum, int day_a, int day_b) {
    if (is_leap) {
        if (m == size)
            sum += std::abs(day_a - day_b) + 1;
        else
            for (int i = m - 1; i < size; ++i) {
                if (i == m - 1)
                    sum += leap[i] - day_a + 1;
                else if (i == size - 1)
                    sum += day_b;
                else
                    sum += leap[i];
            }
    }
    else {
        if (m == size)
            sum += std::abs(day_a - day_b) + 1;
        else
            for (int i = m - 1; i < size; ++i) {
                if (i == m - 1)
                    sum += non_leap[i] - day_a + 1;
                else if (i == size - 1)
                    sum += day_b;
                else
                    sum += non_leap[i];
            }
    }
}

void date_delta() {

    std::vector<int> leap = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    std::vector<int> non_leap = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    std::string date_a;
    std::string date_b;
    while (std::cin >> date_a >> date_b) {
        int year_a = std::stoi(date_a.substr(0, 4));
        int month_a = std::stoi(date_a.substr(4, 2));
        int day_a = std::stoi(date_a.substr(6, 2));

        int year_b = std::stoi(date_b.substr(0, 4));
        int month_b = std::stoi(date_b.substr(4, 2));
        int day_b = std::stoi(date_b.substr(6, 2));

        long long delta = 0;
        bool is_leap_a = is_leap_year(year_a);
        bool is_leap_b = is_leap_year(year_b);
        if (year_a == year_b) {
            if (month_a == month_b) {
                delta = std::abs(day_a - day_b) + 1;
                std::cout << delta << '\n';
                continue;
            }
            else {
                int m = std::min(month_a, month_b);
                int n = std::max(month_a, month_b);
                in_year_sum(leap, non_leap, m, n, is_leap_a, delta, day_a, day_b);
            }
        }
        else {
            if (year_a < year_b) {
                /* first year */
                in_year_sum(leap, non_leap, month_a, 12, is_leap_a, delta, day_a, 31);
                /* last year */
                in_year_sum(leap, non_leap, 1, month_b, is_leap_b, delta, 1, day_b);
                /* middle years */
                for (int i = year_a + 1; i < year_b; ++i) {
                    if (is_leap_year(i))
                        delta += 366;
                    else
                        delta += 365;
                }
            }
            else {
                /* first year */
                in_year_sum(leap, non_leap, month_b, 12, is_leap_b, delta, day_b, 31);
                /* last year */
                in_year_sum(leap, non_leap, 1, month_a, is_leap_a, delta, 1, day_a);
                /* middle years */
                for (int i = year_b + 1; i < year_a; ++i) {
                    if (is_leap_year(i))
                        delta += 366;
                    else
                        delta += 365;
                }
            }
        }

        std::cout << delta << '\n';

        int waite = 1;
    }
}
#pragma endregion

#pragma region factorial_sum
void factorial_sum() {

    constexpr int N = 10;
    constexpr int M = 1000000;
    std::vector<int> f(N, 0);
    std::vector<int> s(N, 0);
    std::vector<int> dp(M + 10, 0);

    int i = 0;
    int j = 0;
    f[0] = s[0] = 1;
    for (i = 1; i < N; ++i) {
        f[i] = i * f[i - 1];
        s[i] = f[i] + s[i - 1];
    }

    dp[0] = 1;
    for (i = 0; i < N; ++i) {
        for (j = std::min(s[i], M); j >= f[i]; --j) {
            dp[j] = dp[j] | dp[j - f[i]];
        }
    }

    dp[0] = 0;
    int n = 0;
    while (std::cin >> n) {
        if (n <= -1)
            break;
        if (dp[n] == 1)
            std::cout << "YES" << '\n';
        else
            std::cout << "NO" << '\n';
    }
}
#pragma endregion

#pragma region wertyu
void wertyu() {
    std::string charactors = "1234567890-=QWERTYUIOP[]ASDFGHJKL;'ZXCVBNM,./";

    std::string sentence;
    while (std::getline(std::cin, sentence)) {
        for (auto& c : sentence) {
            int pos = charactors.find(c);
            if (pos != std::string::npos) {
                c = charactors[pos - 1];
                std::cout << c;
            }
            else if (c == ' ')
                std::cout << c;
            else {
                std::cout << "Fault : input invalid!" << '\n';
                return;
            }
        }
        std::cout << '\n';
    }
}
#pragma endregion

#pragma region valid_number
void valid_number() {
    std::string str = " ";
    while (std::cin >> str) {
        std::string number_str;
        bool found_number = false;
        for (const auto& it : str) {
            int asc = it - '0';
            if (found_number && (asc < 0 || asc > 9))
                break;
            else if (asc >= 0 && asc <= 9) {
                number_str.push_back(it);
                found_number = true;
            }
            else
                found_number = false;
        }

        if (number_str == "") {
            std::cout << -1 << '\n';
            continue;
        }

        double number = std::stod(number_str);
        if (number > INT_MAX)
            std::cout << -1 << '\n';
        else
            std::cout << static_cast<int>(number) << '\n';
    }
}
#pragma endregion

#pragma region massive_number_calc
namespace test{
    using namespace std;
    string removeLeadingZeros(const string & s) {
        size_t start = s.find_first_not_of('0');
        if (start == string::npos) {
            return "-1"; // 如果全是零
        }
        return s.substr(start);
    }

    int compareAbs(const string & a, const string & b) {
        if (a.length() > b.length()) return 1;
        if (a.length() < b.length()) return -1;
        return a.compare(b);
    }

    string addPositive(const string & a, const string & b) {
        string result = "";
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += (a[i--] - '0');
            if (j >= 0) sum += (b[j--] - '0');

            result = char(sum % 10 + '0') + result;
            carry = sum / 10;
        }
        return result;
    }

    string subPositive(const string & a, const string & b) {
        string result = "";
        int borrow = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;

        while (i >= 0) {
            int diff = (a[i--] - '0') - borrow;
            if (j >= 0) diff -= (b[j--] - '0');

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            result = char(diff + '0') + result;
        }
        return removeLeadingZeros(result);
    }

    string mulPositive(const string & a, const string & b) {
        if (a == "0" || b == "0") return "0";

        vector<int> result(a.length() + b.length(), 0);

        for (int i = a.length() - 1; i >= 0; i--) {
            for (int j = b.length() - 1; j >= 0; j--) {
                int mul = (a[i] - '0') * (b[j] - '0');
                int p1 = i + j;
                int p2 = i + j + 1;
                int sum = mul + result[p2];

                result[p2] = sum % 10;
                result[p1] += sum / 10;
            }
        }

        string s = "";
        for (int num : result) {
            if (!(s.empty() && num == 0)) {
                s += char(num + '0');
            }
        }
        return s.empty() ? "0" : s;
    }

    void massive_number_calc() {
        string a, b;
        cin >> a >> b;

        bool aIsNegative = false;
        bool bIsNegative = false;
        if (a[0] == '-') {
            aIsNegative = true;
            a = a.substr(1);
        }
        if (b[0] == '-') {
            bIsNegative = true;
            b = b.substr(1);
        }

        a = removeLeadingZeros(a);
        b = removeLeadingZeros(b);

        string result_add;
        if (aIsNegative == bIsNegative) {
            result_add = addPositive(a, b);
            if (aIsNegative) result_add = "-" + result_add;
        }
        else {
            int cmp = compareAbs(a, b);
            if (cmp == 0) {
                result_add = "0";
            }
            else if (cmp > 0) { // |a| > |b|
                result_add = subPositive(a, b);
                if (aIsNegative) result_add = "-" + result_add;
            }
            else { // |a| < |b|
                result_add = subPositive(b, a);
                if (bIsNegative) result_add = "-" + result_add;
            }
        }
        cout << result_add << endl;

        string result_sub;
        bool bIsNegativeForSub = !bIsNegative;

        if (aIsNegative == bIsNegativeForSub) {
            result_sub = addPositive(a, b);
            if (aIsNegative) result_sub = "-" + result_sub;
        }
        else {
            int cmp = compareAbs(a, b);
            if (cmp == 0) {
                result_sub = "0";
            }
            else if (cmp > 0) { // |a| > |b|
                result_sub = subPositive(a, b);
                if (aIsNegative) result_sub = "-" + result_sub;
            }
            else { // |a| < |b|
                result_sub = subPositive(b, a);
                if (bIsNegativeForSub) result_sub = "-" + result_sub;
            }
        }
        cout << result_sub << endl;

        string result_mul = mulPositive(a, b);
        if (aIsNegative != bIsNegative) {
            result_mul = "-" + result_mul;
        }
        cout << result_mul << endl;

    }
}

#pragma endregion

#pragma region fibonacci_sum
namespace test {
    void fibonacci_sum() {
        int n = 0;
        std::cin >> n;
        std::vector<long long> f;
        if (n >= 1) f.push_back(1);
        if (n >= 2) f.push_back(2);
        long long a = 1, b = 2;
        while (true) {
            long long c = a + b;
            if (c > n) break;
            f.push_back(c);
            a = b;
            b = c;
        }

        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (const auto& it : f)
            for (int j = n; j >= it; --j)
                dp[j] += dp[j - it];

        std::cout << dp[n] << '\n';
    }
}
#pragma endregion

#pragma region LCS 
void LCS() {
    std::vector<int> text1(1e6 + 10, 0);
    std::vector<int> text2(1e6 + 10, 0);
    std::vector<int> idx(1e6 + 10, 0);
    std::vector<int> tails;

    int length = 0;
    std::cin >> length;
    for (int i = 1; i <= length; ++i) {
        int w = 0;
        std::cin >> w;
        text1[i] = w;
        idx[text1[i]] = i;
    }
    for (int i = 1; i <= length; ++i) {
        int w = 0;
        std::cin >> w;
        text2[i] = idx[w];
    }

    for (int i = 1; i <= length; ++i) {
        int temp = text2[i];
        if (temp == 0)
            continue;
        if (tails.empty() || temp > tails.back())
            tails.push_back(temp);

        int index = std::lower_bound(tails.begin(), tails.end(), temp) - tails.begin();
        tails[index] = temp;
    }
    std::cout << tails.size();
}
#pragma endregion

#pragma region easy_sort
void easy_sort() {
    int n = 0;
    std::cin >> n;
    std::vector<int> f;
    int temp = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> temp;
        bool flag_found = false;
        for (const auto& it : f) {
            if (it == temp) {
                flag_found = true;
                break;
            }
        }
        if (flag_found)
            continue;
        else
            f.push_back(temp);
    }

    std::sort(f.begin(), f.end());
    for (const auto& it : f)
        std::cout << it << ' ';
}

#pragma endregion

#pragma region SDS
void shortest_distace_sum() {
    int n = 0;
    std::cin >> n;

    int temp = 0;
    auto f = new int[512][512];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> f[i][j];

    int node_num = n;
    int res = 0;
    for (int k = node_num - 1; k > 0; --k) {
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
                f[j][i] = f[i][j];
                if (i >= k && j >= k)
                    res += f[i][j] * 2;
            }
        }
    }
    std::cout << res << '\n';
    delete f;
}
#pragma endregion

#pragma region longest_consecutive_increasing_subsequence
void LCIS() {
    int n = 0;
    std::cin >> n;

    auto f = new int[10001];
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
        std::cin >> f[i];

    std::vector<int> dp(n + 1, 1);
    dp[0] = 0;
    dp[1] = 1;
    int res = 1;
    for (int i = 2; i <= n; ++i) {
        if (f[i] > f[i - 1])
        {
            dp[i] = dp[i - 1] + 1;
            if (dp[i] > res)
                res = dp[i];
        }
    }
    std::cout << res << '\n';
}
#pragma endregion

#pragma endregion
