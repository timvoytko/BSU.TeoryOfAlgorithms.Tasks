#include <fstream>
#include <string>
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int value) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree {
    Node* root;

private:
    Node* insert_recursive(Node* curr_node, int value) {
        if (curr_node == nullptr) {
            return new Node(value);
        }
        if (value < curr_node->value) {
            curr_node->left = insert_recursive(curr_node->left, value);
        }
        else if (value > curr_node->value) {
            curr_node->right = insert_recursive(curr_node->right, value);
        }
        else {
            return curr_node;
        }
        return curr_node;
    }
    template<class T> 
    void pre_order_traversal_recursive(Node* curr_node, T action) {
        if (curr_node == nullptr) {
            return;
        }
        action(curr_node);
        pre_order_traversal_recursive(curr_node->left, action);
        pre_order_traversal_recursive(curr_node->right, action);
        return;
    }

public:
    BinaryTree() {
        this->root = nullptr;
    }
    void insert(int value) {
        this->root = insert_recursive(root, value);
        return;
    }
    template<class T>
    void pre_order_traversal(T action) {
        pre_order_traversal_recursive(this->root, action);
    }
};
int main() {
    std::ifstream in("input.txt");
    std::string line;
    BinaryTree tree;
    while (std::getline(in, line)) {
        tree.insert(atoi(line.c_str()));
    }
    std::ofstream of("output.txt");
    auto action = [&](Node* node) {
        of << std::to_string(node->value) + '\n';
    };;
    tree.pre_order_traversal(action);

}
