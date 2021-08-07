#pragma once

#include <string>
#include <vector>

// leetcode TreeNode
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


TreeNode *build_tree(std::string nodes);

ListNode* build_list(std::string nodes);

void print_tree_preorder(TreeNode *root) noexcept;

void print_list(ListNode* head) noexcept;