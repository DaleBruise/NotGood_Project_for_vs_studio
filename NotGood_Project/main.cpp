#include "Depth_First_Search.hpp"

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

bool is_sqaured(int x) {
    int s = static_cast<int>(std::sqrt(x));
    return s * s == x;
}

void dfs(const std::vector<int>& f, int size, int last, int remain, int& res) {
    if (remain == 0) {
        ++res;
        return;
    }

    for (int i = 1; i <= size; ++i) {
        int temp_sum = last + f[i];
        if (is_sqaured(temp_sum) || last == -1)
            dfs(f, size, f[i], remain - 1, res);
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

    int res = 0;
    dfs(f, size, -1, size, res);
    std::cout << '\n' << res;
}

int main(int argc, char* argv[])
{
    qubic_matrix_number();


    std::cout << "Program name: " << argv[0] << std::endl;
    std::cout << "Number of arguments: " << argc << std::endl;

    Test_buildTree();

    return 0;
}
