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
	TreeNode* build_tree(const vector<string>& nodes)
	{
		vector<TreeNode*> vec(nodes.size());
		vec[0] = new TreeNode(stoi(nodes[0]));
		for (size_t i = 1; i < nodes.size(); i++) {
			if (nodes[i] == "null") continue;
			int parent_idx = (i - 1) / 2;  // parent node index

			// to find the next non-null parent node
			while (vec[parent_idx] == nullptr) parent_idx++;
			TreeNode* newNode = new TreeNode(stoi(nodes[i]));  // allocate memory, don't free
			vec[i] = newNode;
			if (i % 2 == 1) {
				vec[parent_idx]->left = newNode;
			}
			else {
				vec[parent_idx]->right = newNode;
			}
		}
		return vec[0];
	}
}



// it is NOT efficient, but does its work
// we only new, but don't delete (it has memory leak). 
//     It doesn't matter in this case. 
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
		if(!next_word.empty())  // avoid push_back trailing empty space
			vec.push_back(move(next_word));
	}
	
	return build_tree(vec);
}

