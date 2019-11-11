#include "leetcode_build_tree.h"

int main(){
    TreeNode* root = build_tree(" [2,2,5, null,null,  5,7 ]");
    print_tree_preorder(root);
}