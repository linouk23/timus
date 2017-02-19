// 1136. Parliament - http://acm.timus.ru/problem.aspx?space=1&num=1136

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;

    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};


class BST {
    private:
    Node *root = nullptr;

    void add_helper(Node *root, int val) {
        if (val > root->val) {
            if (root->right) {
                add_helper(root->right, val);
            } else {
                root->right = new Node(val);
            }
        } else if (val < root->val) {
            if (root->left) {
                add_helper(root->left, val);
            } else {
                root->left = new Node(val);
            }
        }
    }

    void right_post_order_helper(Node *root) {
        if (root) {
            right_post_order_helper(root->right);
            right_post_order_helper(root->left);
            cout << root->val << endl;
        }
    }

    public:
    void add(int val) {
        if (root != nullptr) {
            this->add_helper(root, val);
        } else {
            root = new Node(val);
        }
    }

    void right_post_order() {
        this->right_post_order_helper(root);
    }
};


int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    BST tree;

    int num_of_members;
    cin >> num_of_members;

    vector<int> members;
    int member;
    for (int index = 0; index < num_of_members; ++index) {
        cin >> member;
        members.emplace_back(member);
    }

    for (int index = 0; index < (int)members.size(); ++index) {
        tree.add(members[num_of_members - index - 1]);
    }
    
    tree.right_post_order();
    
    return 0;
}