#pragma once

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "DataStruct.hpp"

#pragma region Basic Function

// TreeNode* 
//     build_tree(std::vector<int>& inorder, std::vector<int>& postorder);
// TreeNode* 
//     build_tree_from_level_order(const std::vector<int>& levelOrder);

#pragma endregion

#pragma region Chapter 1 Basic DFS
// int 
//     maxDepth(TreeNode* root);
// int 
//     minDepth(TreeNode* root);
// bool 
//     hasPathSum(TreeNode* root, int targetSum);
// TreeNode* 
//     invertTree(TreeNode* root);
// bool 
//     isSameTree(TreeNode* p, TreeNode* q);
// bool 
//     isSymmetric(TreeNode* root);
// int 
//     sumNumbers(TreeNode* root);

#pragma endregion

#pragma region Testing Function

void
Test_maxDepth();
void
Test_minDepth();
void
Test_hasPathSum();
void
Test_invertTree();
void
Test_isSameTree();
void
Test_sumNumbers();
void
Test_lowestCommonAncestor();
void
Test_buildTree();

#pragma endregion
