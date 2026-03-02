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

int main(int argc, char** argv)
{
    std::cout << "Program name: " << argv[0] << std::endl;
    std::cout << "Number of arguments: " << argc << std::endl;

    Test_buildTree();

    return 0;
}
