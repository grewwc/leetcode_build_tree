#include "leetcode_build_tree.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;


void print_tree_preorder(TreeNode* root) noexcept
{
	if (!root) return;
	std::cout << root->val << std::endl;
	print_tree_preorder(root->left);
	print_tree_preorder(root->right);
}


namespace
{
	TreeNode* build_tree(const vector<string>& nodes) noexcept
	{
		vector<TreeNode*> vec(nodes.size());
		vec[0] = new TreeNode(stoi(nodes[0]));
		int parent_idx = 0;
		int count = 0;
		for (size_t i = 1; i < nodes.size(); i++) {
            if (count == 2) {
				count = 0;
				parent_idx++;
				while (parent_idx < nodes.size() && !vec[parent_idx])
					parent_idx++;
			}

            
			if (nodes[i] == "null") {
				count++;
				continue;
			}
			

			vec[i] = new TreeNode(stoi(nodes[i]));
			if (count % 2 == 1) {
				vec[parent_idx]->right = vec[i];
			}
			else {
				vec[parent_idx]->left = vec[i];
			}
			count++;
		}
		return vec[0];
	}
}



// it is NOT efficient, but does its work
// we only new, but don't delete (it has memory leak). 
// It doesn't matter in this case. 
// here just copy the string, no string_view or (const) reference
TreeNode* build_tree(string nodes)
{
	vector<string> vec;

	// transform "," & "[" & "]" to empty space
	transform(cbegin(nodes), cend(nodes), begin(nodes),
		[](char ch) {
			if (ch != ',' && ch != '[' && ch != ']') {
				return ch;
			};
			return ' ';
		});

	// use iss to ignore empty space 
	istringstream iss{ move(nodes) };
	string next_word;

	while (!iss.eof()) {
		iss >> next_word;
		if (!next_word.empty())  // avoid push_back trailing empty space
			vec.push_back(move(next_word));
	}

	return build_tree(vec);
}

ListNode* build_list(string nodes)
{
    string node_val;
    ListNode* head = new ListNode(0);
    auto cur = head;
    for(int i=0; i<nodes.size();i++)
    {
        char ch = nodes[i];
        switch(ch)
        {
        case ' ':
        case '[':
            continue;
        case ',':
        case ']':
            cur->next = new ListNode(stoi(node_val));
            cur = cur->next;
            node_val.clear();
            break;
        default:
            node_val += ch;
        }
    }
    return head->next;
}

void print_list(ListNode* head) noexcept
{
    while(head)
    {
        cout << head->val << endl;
        head = head->next;
    }
}