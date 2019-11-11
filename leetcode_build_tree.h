#pragma once 

#include <string>

// leetcode TreeNode
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


TreeNode* build_tree(std::string nodes);

void print_tree_preorder(TreeNode* root) noexcept;

