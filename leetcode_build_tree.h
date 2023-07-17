#pragma once

#include <iostream>
#include <sstream>
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

// implementations
namespace
{
    TreeNode *build_tree(const std::vector<std::string> &nodes) noexcept
    {
        std::vector<TreeNode *> vec(nodes.size());
        vec[0] = new TreeNode(stoi(nodes[0]));
        int parent_idx = 0;
        int count = 0;
        for (size_t i = 1; i < nodes.size(); i++)
        {
            if (count == 2)
            {
                count = 0;
                parent_idx++;
                while (parent_idx < nodes.size() && !vec[parent_idx]) parent_idx++;
            }

            if (nodes[i] == "null")
            {
                count++;
                continue;
            }

            vec[i] = new TreeNode(stoi(nodes[i]));
            if (count % 2 == 1)
            {
                vec[parent_idx]->right = vec[i];
            }
            else
            {
                vec[parent_idx]->left = vec[i];
            }
            count++;
        }
        return vec[0];
    }
} // namespace

// it is NOT efficient, but does its work
// we only new, but don't delete (it has memory leak).
// It doesn't matter in this case.
// here just copy the string, no string_view or (const) reference
TreeNode *build_tree(std::string nodes)
{
    std::vector<std::string> vec;

    // transform "," & "[" & "]" to empty space
    transform(std::cbegin(nodes), std::cend(nodes), std::begin(nodes), [](char ch) {
        if (ch != ',' && ch != '[' && ch != ']')
        {
            return ch;
        };
        return ' ';
    });

    // use iss to ignore empty space
    std::istringstream iss{std::move(nodes)};
    std::string next_word;

    while (!iss.eof())
    {
        iss >> next_word;
        if (!next_word.empty()) // avoid push_back trailing empty space
            vec.push_back(std::move(next_word));
    }

    return build_tree(vec);
}
ListNode *build_list(std::string nodes)
{
    std::string node_val;
    ListNode *head = new ListNode(0);
    auto cur = head;
    for (int i = 0; i < nodes.size(); i++)
    {
        char ch = nodes[i];
        switch (ch)
        {
        case ' ':
        case '[': continue;
        case ',':
        case ']':
            cur->next = new ListNode(stoi(node_val));
            cur = cur->next;
            node_val.clear();
            break;
        default: node_val += ch;
        }
    }
    return head->next;
}

void print_list(ListNode *head) noexcept
{
    while (head)
    {
        std::cout << head->val << std::endl;
        head = head->next;
    }
}

void print_tree_preorder(TreeNode *root) noexcept
{
    if (!root) return;
    std::cout << root->val << std::endl;
    print_tree_preorder(root->left);
    print_tree_preorder(root->right);
}
