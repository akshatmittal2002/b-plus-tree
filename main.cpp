#include <bits/stdc++.h>
using namespace std;

class tree_node;

class node{
    public:
        int data_val;
        tree_node *leftchild;
        node(){
            leftchild = nullptr;
        }
};

class tree_node{
    public:
        vector<node *> val;
        bool isDataNode;
        tree_node *right_child;
        tree_node *parent;
        tree_node(){
            right_child = nullptr;
            parent = nullptr;
            isDataNode = false;
        }
};

bool compare(node* &a, node* &b){
    return (a->data_val) < (b->data_val);
}

class b_plus_tree{
    public:
        tree_node *root;
        int d, t;
        b_plus_tree(int d, int t){
            root = nullptr;
            this->d = d;
            this->t = t;
        }
        void insert(int data);
        int countIndexNodes(tree_node *node);
        int countDataNodes(tree_node *node);
        void status();
};

int main(){
    int d, t;
    cin>>d>>t;
    b_plus_tree tree(d, t);
    int x,val;
    cin>>x;
    while (x != 3){
        if (x == 1){
            cin>>val;
            tree.insert(val);
        }
        else if (x == 2){
            tree.status();
        }
        else{
            // cout<<"Invalid Command!";
        }
        cin>>x;
    }
    return 0;
}

void b_plus_tree::status(){
    if (root == nullptr){
        cout<<"0 0\n";
        return;
    };
    cout<<countIndexNodes(root)<<" "<<countDataNodes(root);
    for (int i = 0; i < root->val.size(); i++){
        cout<<" "<<(root->val[i])->data_val;
    }
    cout<<"\n";
}

int b_plus_tree::countDataNodes(tree_node *node){
    if (node == nullptr) return 0;
    if (node->isDataNode == true) return 1;
    int k = 0;
    for (int i = 0; i < node->val.size(); i++){
        k += countDataNodes((node->val[i])->leftchild);
    }
    k += countDataNodes(node->right_child);
    return k;
}

int b_plus_tree::countIndexNodes(tree_node *node){
    if (node == nullptr) return 0;
    if (node->isDataNode == true) return 0;
    int k = 1;
    for (int i = 0; i < node->val.size(); i++){
        k += countIndexNodes((node->val[i])->leftchild);
    }
    k += countIndexNodes(node->right_child);
    return k;
}

void b_plus_tree::insert(int data){
    // First Insertion, i.e., root is null
    if (root == nullptr){
        tree_node *x = new tree_node();
        x->isDataNode = true;
        node *n = new node();
        n->data_val = data;
        x->val.push_back(n);
        root = x;
        return;
    }
    // Root is a Data Node
    if (root->isDataNode == true){
        // Before insertion root is not full
        if (root->val.size() < 2*d){
            node *n = new node();
            n->data_val = data;
            root->val.push_back(n);
            sort(root->val.begin(), root->val.end(), compare);
        }
        // Before insertion root is full
        else{
            node *n = new node();
            n->data_val = data;
            root->val.push_back(n);
            sort(root->val.begin(), root->val.end(), compare);

            tree_node *right_node = new tree_node();
            right_node->isDataNode = true;

            for (int i = d; i < root->val.size(); i++){
                node *n = new node();
                n->data_val = (root->val[i])->data_val;
                right_node->val.push_back(n);
            }
            for (int i = 0; i <= d; i++){
                root->val.pop_back();
            }

            tree_node *new_root = new tree_node();

            n = new node();
            n->data_val = (right_node->val[0])->data_val;
            n->leftchild = root;

            new_root->val.push_back(n);
            new_root->right_child = right_node;

            root = new_root;
            ((root->val[0])->leftchild)->parent = root;
            (root->right_child)->parent = root;
        }
        return;
    }
    // Root is index node
    // Finding data node
    tree_node *curr = root;
    while (curr->isDataNode == false){
        int k = 0;
        for (int i = 0; i < curr->val.size(); i++){
            if (curr->val[i]->data_val > data){
                k = 1;
                curr = (curr->val[i])->leftchild;
                break;
            }
        }
        if (k == 0){
            curr = curr->right_child;
        }
    }

    if (curr->val.size() < 2 * d){
        node *n = new node();
        n->data_val = data;
        curr->val.push_back(n);
        sort(curr->val.begin(), curr->val.end(), compare);
        return;
    }

    // Adding new values in data node
    node *n = new node();
    n->data_val = data;
    curr->val.push_back(n);
    sort(curr->val.begin(), curr->val.end(), compare);

    // splitting data node
    tree_node *right_node = new tree_node();
    right_node->isDataNode = true;

    for (int i = d; i < curr->val.size(); i++){
        node *n = new node();
        n->data_val = curr->val[i]->data_val;
        right_node->val.push_back(n);
    }
    for (int i = 0; i < d + 1; i++){
        curr->val.pop_back();
    }

    // Sending index value to parent
    n = new node();
    n->data_val = right_node->val[0]->data_val;
    right_node->parent = curr->parent;

    n->leftchild = curr;
    if (n->data_val > curr->parent->val[curr->parent->val.size() - 1]->data_val){
        curr->parent->val.push_back(n);
        curr->parent->right_child = right_node;
    }
    else{
        curr->parent->val.push_back(n);
        tree_node *curr_parent = curr->parent;
        sort(curr_parent->val.begin(), curr_parent->val.end(), compare);
        int j = 0;
        for (j = 0; j < curr_parent->val.size(); j++){
            if (curr_parent->val[j]->data_val == n->data_val){
                break;
            }
        }
        curr_parent->val[j + 1]->leftchild = right_node;
    }
    curr = curr->parent;
    if (curr == nullptr){
        return;
    }
    while (curr->val.size() > 2 * t + 1){
        // Special root case
        if (curr == root || curr == nullptr){
            break;
        }

        // Splitting index node
        tree_node *right_node = new tree_node();
        right_node->isDataNode = false;

        int up_val = curr->val[t]->data_val;
        for (int i = t + 1; i < curr->val.size(); i++){
            node *n = new node();
            n->data_val = curr->val[i]->data_val;
            n->leftchild = curr->val[i]->leftchild;
            right_node->val.push_back(n);
        }

        right_node->parent = curr->parent;
        right_node->right_child = curr->right_child;
        curr->right_child = curr->val[t]->leftchild;
        for (int i = 0; i < t + 2; i++){
            curr->val.pop_back();
        }
        for (int i = 0; i < right_node->val.size(); i++){
            right_node->val[i]->leftchild->parent = right_node;
        }
        right_node->right_child->parent = right_node;

        // Sending index value to parent
        node *n = new node();
        n->data_val = up_val;
        n->leftchild = curr;

        if (n->data_val > curr->parent->val[curr->parent->val.size() - 1]->data_val){
            curr->parent->val.push_back(n);
            curr->parent->right_child = right_node;
        }
        else{
            curr->parent->val.push_back(n);
            tree_node *curr_parent = curr->parent;
            sort(curr_parent->val.begin(), curr_parent->val.end(), compare);
            int j = 0;
            for (j = 0; j < curr_parent->val.size(); j++){
                if (curr_parent->val[j]->data_val == n->data_val){
                    break;
                }
            }
            curr_parent->val[j + 1]->leftchild = right_node;
        }
        curr = curr->parent;
    }

    if (curr == root && curr->val.size() > 2 * t + 1){
        tree_node *right_node = new tree_node();
        right_node->isDataNode = false;

        int up_val = curr->val[t]->data_val;

        for (int i = t + 1; i < root->val.size(); i++){
            node *n = new node();
            n->data_val = root->val[i]->data_val;
            n->leftchild = root->val[i]->leftchild;
            right_node->val.push_back(n);
        }

        right_node->right_child = curr->right_child;
        curr->right_child = curr->val[t]->leftchild;

        for (int i = 0; i < t + 2; i++){
            root->val.pop_back();
        }
        for (int i = 0; i < right_node->val.size(); i++){
            right_node->val[i]->leftchild->parent = right_node;
        }
        right_node->right_child->parent = right_node;

        tree_node *new_root = new tree_node();
        new_root->isDataNode = false;

        n = new node();
        n->data_val = up_val;
        n->leftchild = root;

        new_root->val.push_back(n);
        new_root->right_child = right_node;

        root = new_root;
        root->val[0]->leftchild->parent = root;
        root->right_child->parent = root;
    }
}