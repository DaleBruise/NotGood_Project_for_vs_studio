#include "Depth_First_Search.hpp"

#pragma region Basic Function

TreeNode* build_tree(std::vector<int>& inorder, std::vector<int>& postorder) {
    const int n = inorder.size();
    if (n < 1)
        return nullptr;

    TreeNode* root = new TreeNode(postorder[n - 1]);
    std::stack<TreeNode*> stk;
    stk.push(root);
    int in_index = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        auto post_val = postorder[i];
        auto node = stk.top();
        if (node->val != inorder[in_index]) {
            node->right = new TreeNode(post_val);
            stk.push(node->right);
        }
        else {
            while (!stk.empty() && stk.top()->val == inorder[in_index]) {
                node = stk.top();
                stk.pop();
                in_index--;
            }
            node->left = new TreeNode(post_val);
            stk.push(node->left);
        }
    }
    return root;
}

TreeNode* build_tree_from_level_order(const std::vector<int>& levelOrder) {
    if (levelOrder.empty() || levelOrder[0] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(levelOrder[0]);
    std::queue<TreeNode*> q;
    q.push(root);

    size_t index = 1; // 当前处理到 levelOrder 的位置

    while (!q.empty() && index < levelOrder.size()) {
        TreeNode* current = q.front();
        q.pop();

        // 处理左子节点
        if (index < levelOrder.size()) {
            int leftVal = levelOrder[index++];
            if (leftVal != -1) {
                current->left = new TreeNode(leftVal);
                q.push(current->left);
            }
            // 如果是 -1，则 left 保持为 nullptr
        }

        // 处理右子节点
        if (index < levelOrder.size()) {
            int rightVal = levelOrder[index++];
            if (rightVal != -1) {
                current->right = new TreeNode(rightVal);
                q.push(current->right);
            }
            // 如果是 -1，则 right 保持为 nullptr
        }
    }
    return root;
}

#pragma endregion

#pragma region Chapter 1 Basic DFS

int maxDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;

    return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

int minDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;
    if (root->left != nullptr && root->right != nullptr)
        return std::min(minDepth(root->left), minDepth(root->right)) + 1;
    else
        return std::max(minDepth(root->left), minDepth(root->right)) + 1;
}

bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr)
        return false;
    if (root->left == nullptr && root->right == nullptr)
        return targetSum == root->val;
    return hasPathSum(root->left, targetSum - root->val)
        || hasPathSum(root->right, targetSum - root->val);
}

void dfs_inverTree(TreeNode* root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr))
        return;

    auto temp = root->left;
    root->left = root->right;
    root->right = temp;

    dfs_inverTree(root->left);
    dfs_inverTree(root->right);
}

TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr)
        return root;

    dfs_inverTree(root);
    return root;
}

bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr ^ q == nullptr)
        return false;

    if (p == nullptr && q == nullptr)
        return true;

    if (p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    else
        return false;
}

bool dfs_isSymmetric(TreeNode* p, TreeNode* q) { /* p is left node, q is right node */
    if (p == nullptr && q == nullptr)
        return true;
    if (p == nullptr ^ q == nullptr)
        return false;

    return (p->val == q->val)
        && dfs_isSymmetric(p->left, q->right)
        && dfs_isSymmetric(p->right, q->left);
}

bool isSymmetric(TreeNode* root) {
    if (root == nullptr)
        return true;

    return dfs_isSymmetric(root->left, root->right);
}

int dfs_sumNumbers(TreeNode* root, int prev_sum) {
    if (root == nullptr)
        return 0;

    int sum = prev_sum * 10 + root->val;
    if (root->left == nullptr && root->right == nullptr)
        return sum;
    else
        return dfs_sumNumbers(root->left, sum) + dfs_sumNumbers(root->right, sum);
}

int sumNumbers(TreeNode* root) {
    if (root == nullptr)
        return 0;

    return dfs_sumNumbers(root, 0);
}

bool dfs_lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& res) {
    if (root == nullptr)
        return false;

    bool left = dfs_lowestCommonAncestor(root->left, p, q, res);
    bool right = dfs_lowestCommonAncestor(root->right, p, q, res);
    if ((left && right)
        || ((left || right) && (root->val == q->val || root->val == p->val)))
        res = root;
    return left || right || (root->val == p->val || root->val == q->val);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root->left == p && root->right == q)
        return root;

    TreeNode* res;
    dfs_lowestCommonAncestor(root, p, q, res);
    return res;
}

TreeNode* dfs_buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder,
    std::unordered_map<int, int>& visited,
    int p_left, int p_right, int i_left, int i_right) {
    if (p_left > p_right)
        return nullptr;

    int p_root = p_left;
    int i_root = visited[preorder[p_root]];

    auto root = new TreeNode(preorder[p_root]);
    int size_left = i_root - i_left;
    root->left = dfs_buildTree(preorder, inorder, visited,
        p_left + 1, p_left + size_left,
        i_left, i_root - 1);
    root->right = dfs_buildTree(preorder, inorder, visited,
        p_left + size_left + 1, p_right,
        i_root + 1, i_right);
    return root;
}

TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
    int size = preorder.size();

    std::unordered_map<int, int> visited;
    for (int i = 0; i < size; ++i)
        visited.insert({ inorder[i], i });

    return dfs_buildTree(preorder, inorder, visited,
        0, size - 1, 0, size - 1);
}

#pragma endregion

#pragma region Testing Function

void Test_maxDepth() {
    std::cout << "Testing:   maxDepth" << "\n";

    std::vector<int> inorder{ 9, 3, 15, 20, 7 };
    std::vector<int> postorder{ 9, 15, 7, 20, 3 };
    auto root = build_tree(inorder, postorder);
    int res = maxDepth(root);
    std::cout << "The result is: " << res << "\n";
}

void Test_minDepth() {
    std::cout << "Testing:   minDepth" << "\n";

    std::vector<int> inorder{ 2, 3, 4, 5, 6 };
    std::vector<int> postorder{ 6, 5, 4, 3, 2, 1 };
    auto root = build_tree(inorder, postorder);
    int res = minDepth(root);
    std::cout << "The result is: " << res << "\n";
}

void Test_hasPathSum() {
    std::cout << "Testing:   hasPathSum" << "\n";

    std::vector<std::pair<TreeNode*, int>> roots;
    std::vector<int> inorder_1{ 7, 11, 2, 4, 5, 13, 8, 4, 1 };
    std::vector<int> postorder_1{ 7, 2, 11, 4, 13, 1, 4, 8, 5 };
    roots.emplace_back(build_tree(inorder_1, postorder_1), 22);

    std::vector<int> inorder_2{ 2, 1, 3 };
    std::vector<int> postorder_2{ 2, 3, 1 };
    roots.emplace_back(build_tree(inorder_2, postorder_2), 5);

    roots.emplace_back(nullptr, 0);

    for (const auto& it : roots) {
        auto root = it.first;
        auto target = it.second;
        auto res = hasPathSum(root, target);
        std::cout << "The result is: " << res << "\n";
    }
}

void Test_invertTree() {
    std::cout << "Testing:   invertTree" << "\n";

    std::vector<TreeNode*> roots;
    std::vector<int> inorder_1{ 1, 2, 3, 4, 6, 7, 9 };
    std::vector<int> postorder_1{ 1, 3, 2, 6, 9, 7, 4 };
    roots.emplace_back(build_tree(inorder_1, postorder_1));

    std::vector<int> inorder_2{ 1, 2, 3 };
    std::vector<int> postorder_2{ 1, 3, 2 };
    roots.emplace_back(build_tree(inorder_2, postorder_2));

    roots.emplace_back(nullptr);

    for (auto& it : roots) {
        auto res = invertTree(it);
        std::cout << "The result is: " << res << "\n";
    }
}

void Test_isSameTree() {
    std::cout << "Testing:   isSameTree" << "\n";

    std::vector<std::pair<TreeNode*, TreeNode*>> roots;
    std::vector<int> tree_1{ 1, 2, 3 };
    std::vector<int> tree_2{ 1, 2, 3 };
    roots.emplace_back(build_tree_from_level_order(tree_1),
        build_tree_from_level_order(tree_2));

    std::vector<int> tree_3{ 1, 2 };
    std::vector<int> tree_4{ 1, -1, 2 };
    roots.emplace_back(build_tree_from_level_order(tree_3),
        build_tree_from_level_order(tree_4));

    std::vector<int> tree_5{ 1, 2, 1 };
    std::vector<int> tree_6{ 1, 1, 2 };
    roots.emplace_back(build_tree_from_level_order(tree_5),
        build_tree_from_level_order(tree_6));

    for (auto& it : roots) {
        auto tree_1 = it.first;
        auto tree_2 = it.second;
        auto res = isSameTree(tree_1, tree_2);
        std::cout << "The result is: " << res << "\n";
    }
}

void Test_isSymmetric() {
    std::cout << "Testing:   isSymmetric" << "\n";

    std::vector<TreeNode*> roots;
    std::vector<int> tree_1{ 1, 2, 2, 3, 4, 4, 3 };
    roots.emplace_back(build_tree_from_level_order(tree_1));

    std::vector<int> tree_3{ 1, 2, 2, -1, 3, -1, 3 };
    roots.emplace_back(build_tree_from_level_order(tree_3));

    for (auto& it : roots) {
        auto res = isSymmetric(it);
        std::cout << "The result is: " << res << "\n";
    }
}

void Test_sumNumbers() {
    std::cout << "Testing:   sumNumbers" << "\n";

    std::vector<TreeNode*> roots;
    std::vector<int> tree_1{ 1, 2, 3 };
    roots.emplace_back(build_tree_from_level_order(tree_1));

    std::vector<int> tree_3{ 4, 9, 0, 5, 1 };
    roots.emplace_back(build_tree_from_level_order(tree_3));

    for (auto& it : roots) {
        auto res = sumNumbers(it);
        std::cout << "The result is: " << res << "\n";
    }
}

void Test_lowestCommonAncestor() {
    std::cout << "Testing:   lowestCommonAncestor" << "\n";

    std::vector<std::vector<TreeNode*>> sets;
    std::vector<int> tree_1{ 3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4 };
    std::vector<TreeNode*> set_1;
    auto tree = build_tree_from_level_order(tree_1);
    set_1.emplace_back(tree);
    set_1.emplace_back(tree->left);
    set_1.emplace_back(tree->right);
    sets.emplace_back(set_1);

    std::vector<int> tree_3{ 3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4 };
    std::vector<TreeNode*> set_2;
    tree = build_tree_from_level_order(tree_3);
    set_2.emplace_back(tree);
    set_2.emplace_back(tree->left);
    set_2.emplace_back(tree->left->right->right);
    sets.emplace_back(set_2);

    std::vector<int> tree_5{ 1, 2, -1 };
    std::vector<TreeNode*> set_3;
    tree = build_tree_from_level_order(tree_5);
    set_3.emplace_back(tree);
    set_3.emplace_back(tree);
    set_3.emplace_back(tree->left);
    sets.emplace_back(set_3);

    for (auto& it : sets) {
        auto root = it[0];
        auto n_1 = it[1];
        auto n_2 = it[2];
        auto res = lowestCommonAncestor(root, n_1, n_2);
        int waite = 1;
    }
}

void Test_buildTree() {
    std::cout << "Testing:   sumNumbers" << "\n";

    std::vector<TreeNode*> roots;
    std::vector<int> tree_1{ -1 };
    std::vector<int> tree_2{ -1 };
    roots.emplace_back(buildTree(tree_1, tree_2));

    std::vector<int> tree_3{ 3, 9, 20, 15, 7 };
    std::vector<int> tree_4{ 9, 3, 15, 20, 7 };
    roots.emplace_back(buildTree(tree_3, tree_4));

    for (auto& it : roots) {
        auto res = it;
        int waite = 1;
    }
}

#pragma endregion