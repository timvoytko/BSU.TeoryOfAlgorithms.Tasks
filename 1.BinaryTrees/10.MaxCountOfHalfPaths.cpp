#include <fstream>
#include <string>
#include<vector>
#include<set>
#include<stack>
struct Node {
    long long value;
    Node* left;
    Node* right;
    Node* parrent;
    long long height;
    long long length_of_half_path;
    long long count_of_leaf_on_distance_h;
    long long count_of_diffrence_half_path_if_root;
    long long count_of_diffrence_half_path_if_not_root;
    long long length_of_incoming_max_half_path;
    long long count_of_incoming_max_halp_path;
    Node(long long value) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->parrent = nullptr;
        this->height = 0;
        this->length_of_half_path = 0;
        this->count_of_leaf_on_distance_h = 0;
        this->count_of_diffrence_half_path_if_root = 0;
        this->count_of_diffrence_half_path_if_not_root = 0;
        this->length_of_incoming_max_half_path = 0;
        this->count_of_incoming_max_halp_path = 0;

    }
    int count_of_childs() {
        return (int)(this->left != nullptr) + (int)(this->right != nullptr);
    }
};
class Tree {
public:
    long long max_length_of_half_path;
    Node* root;
    Tree() {
        this->max_length_of_half_path = 0;
        this->root = nullptr;
    }
    void insert_with_parrent(long long value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }
        Node* tmp = root;
        Node* tmp_parrent = nullptr;
        while (tmp != nullptr) {
            tmp_parrent = tmp;
            if (value > tmp->value) {
                tmp = tmp->right;
            }
            else if (value < tmp->value) {
                tmp = tmp->left;
            }
            else {
                return;
            }
        }
        tmp = new Node(value);
        tmp->parrent = tmp_parrent;
        if (value > tmp_parrent->value) {
            tmp_parrent->right = tmp;
        }
        else {
            tmp_parrent->left = tmp;
        }
    }
    void remove_node_by_pointer(Node* removing_node) {
        if (removing_node == this->root) {
            switch (removing_node->count_of_childs())
            {
            case 0: {
                this->root = nullptr;
                break;
            }
            case 1: {
                if (root->left == nullptr) {
                    root->right->parrent = nullptr;
                    this->root = root->right;
                }
                else {
                    root->left->parrent = nullptr;
                    this->root = root->left;
                }
                break;
            }
            case 2: {
                Node* replacing_node = root->right;
                while (replacing_node->left != nullptr) {
                    replacing_node = replacing_node->left;
                }
                if (replacing_node == root->right) {
                    root->right->parrent = nullptr;
                    root->right->left = root->left;
                    root->left->parrent = root->right;
                    root = root->right;

                }
                else {
                    if (replacing_node->right == nullptr) {
                        replacing_node->parrent->left = nullptr;
                    }
                    else {
                        replacing_node->parrent->left = replacing_node->right;
                        replacing_node->right->parrent = replacing_node->parrent;
                    }
                    replacing_node->parrent = nullptr;
                    replacing_node->right = root->right;
                    replacing_node->right->parrent = replacing_node;
                    replacing_node->left = root->left;
                    replacing_node->left->parrent = replacing_node;
                    root = replacing_node;
                }
                break;
            }
            default:
                break;
            }
        }
        else {
            switch (removing_node->count_of_childs())
            {
            case 0: {
                if (removing_node->value > removing_node->parrent->value) {
                    removing_node->parrent->right = nullptr;
                }
                else {
                    removing_node->parrent->left = nullptr;
                }
                removing_node = nullptr;
                break;
            }
            case 1: {
                if (removing_node->left == nullptr) {
                    if (removing_node->value > removing_node->parrent->value) {
                        removing_node->parrent->right = removing_node->right;
                        removing_node->right->parrent = removing_node->parrent;
                    }
                    else {
                        removing_node->parrent->left = removing_node->right;
                        removing_node->right->parrent = removing_node->parrent;
                    }
                }
                else {
                    if (removing_node->value > removing_node->parrent->value) {
                        removing_node->parrent->right = removing_node->left;
                        removing_node->left->parrent = removing_node->parrent;
                    }
                    else {
                        removing_node->parrent->left = removing_node->left;
                        removing_node->left->parrent = removing_node->parrent;
                    }
                }
                break;
            }
            case 2: {
                Node* replacing_node = removing_node->right;
                while (replacing_node->left != nullptr) {
                    replacing_node = replacing_node->left;
                }
                if (replacing_node == removing_node->right) {
                    if (removing_node->value < removing_node->parrent->value) {
                        removing_node->parrent->left = replacing_node;
                        replacing_node->parrent = removing_node->parrent;
                        replacing_node->left = removing_node->left;
                        removing_node->left->parrent = replacing_node;
                    }
                    else {
                        removing_node->parrent->right = replacing_node;
                        replacing_node->parrent = removing_node->parrent;
                        replacing_node->left = removing_node->left;
                        removing_node->left->parrent = replacing_node;
                    }
                }
                else {
                    if (replacing_node->right == nullptr) {
                        replacing_node->parrent->left = nullptr;
                    }
                    else {
                        replacing_node->parrent->left = replacing_node->right;
                        replacing_node->right->parrent = replacing_node->parrent;
                    }
                    replacing_node->parrent = removing_node->parrent;
                    if (removing_node->value > removing_node->parrent->value) {
                        removing_node->parrent->right = replacing_node;
                    }
                    else {
                        removing_node->parrent->left = replacing_node;
                    }
                    replacing_node->left = removing_node->left;
                    removing_node->left->parrent = replacing_node;
                    replacing_node->right = removing_node->right;
                    removing_node->right->parrent = replacing_node;
                }
                break;
            }
            default:
                break;
            }
        }
    }
    void remove_with_parrent(long long value) {
        Node* tmp = root;
        bool is_found = false;
        while (tmp != nullptr) {
            if (value > tmp->value) {
                tmp = tmp->right;

            }
            else if (value < tmp->value) {
                tmp = tmp->left;
            }
            else {
                is_found = true;
                break;
            }
        }
        if (is_found) {
            this->remove_node_by_pointer(tmp);
        }
        else {
            return;
        }
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
    template<class T>
    void pre_order_traversal(T action) {
        pre_order_traversal_recursive(this->root, action);
        return;
    }
    template<class T>
    void post_order_traversal_recursive(Node* curr_node, T action) {
        if (curr_node == nullptr) {
            return;
        }
        post_order_traversal_recursive(curr_node->left, action);
        post_order_traversal_recursive(curr_node->right, action);
        action(curr_node);
        return;
    }
    template<class T>
    void post_order_traversal(T action) {
        post_order_traversal_recursive(this->root, action);
        return;
    }
    void set_heights_and_lengths_of_half_paths() {
        auto action = [&](Node* node) {
            switch (node->count_of_childs()) {
            case 2: {
                if (node->left->height > node->right->height) {
                    node->height = node->left->height + 1;
                    node->count_of_leaf_on_distance_h = node->left->count_of_leaf_on_distance_h;
                }
                else if (node->right->height > node->left->height) {
                    node->height = node->right->height + 1;
                    node->count_of_leaf_on_distance_h = node->right->count_of_leaf_on_distance_h;
                }
                else {
                    node->height = node->right->height + 1;
                    node->count_of_leaf_on_distance_h = node->left->count_of_leaf_on_distance_h
                        + node->right->count_of_leaf_on_distance_h;
                }
                node->length_of_half_path = node->left->height + node->right->height + 2;
                break;
            }
            case 1: {
                if (node->left == nullptr) {
                    node->height = node->right->height + 1;
                    node->count_of_leaf_on_distance_h = node->right->count_of_leaf_on_distance_h;
                }
                else {
                    node->height = node->left->height + 1;
                    node->count_of_leaf_on_distance_h = node->left->count_of_leaf_on_distance_h;
                }
                node->length_of_half_path = node->height;
                break;
            }
            case 0: {
                node->count_of_leaf_on_distance_h = 1;
                break;
            }
            }
            if (this->max_length_of_half_path < node->length_of_half_path) {
                this->max_length_of_half_path = node->length_of_half_path;
            }

        };
        this->post_order_traversal(action);

    }
    long long set_counts_of_half_paths_and_get_max() {
        auto action = [&](Node* node) {
            if (node->length_of_half_path == this->max_length_of_half_path) {
                if (node->count_of_childs() == 0) {
                    node->count_of_diffrence_half_path_if_root = 1;
                }
                else if (node->count_of_childs() == 1) {
                    if (node->right == nullptr) {
                        node->count_of_diffrence_half_path_if_root = node->left->count_of_leaf_on_distance_h;
                    }
                    else {
                        node->count_of_diffrence_half_path_if_root = node->right->count_of_leaf_on_distance_h;
                    }
                }
                else {
                    node->count_of_diffrence_half_path_if_root = node->left->count_of_leaf_on_distance_h *
                        node->right->count_of_leaf_on_distance_h;
                }
            }
        };
        this->post_order_traversal(action);
        long long max_count_of_half_paths = -1;
        auto action1 = [&](Node* node) {
            if (node == this->root) {
                node->count_of_incoming_max_halp_path = 1;
                node->length_of_incoming_max_half_path = 0;
                node->count_of_diffrence_half_path_if_not_root = 0;
            }
            switch (node->count_of_childs()) {
            case 2: {
                // max half path from right and curr = root of it
                if (node->length_of_incoming_max_half_path == node->right->height + 1) {
                    node->left->length_of_incoming_max_half_path = node->right->height + 2;
                    node->left->count_of_incoming_max_halp_path = node->count_of_incoming_max_halp_path
                        + node->right->count_of_leaf_on_distance_h;
                }
                // max half path from right
                else if (node->length_of_incoming_max_half_path < node->right->height + 1) {
                    node->left->length_of_incoming_max_half_path = node->right->height + 2;
                    node->left->count_of_incoming_max_halp_path = node->right->count_of_leaf_on_distance_h;
                }
                // max half path from curr
                else {
                    node->left->length_of_incoming_max_half_path = node->length_of_incoming_max_half_path + 1;
                    node->left->count_of_incoming_max_halp_path = node->count_of_incoming_max_halp_path;
                }
                // same for right node
                if (node->length_of_incoming_max_half_path == node->left->height + 1) {
                    node->right->length_of_incoming_max_half_path = node->left->height + 2;
                    node->right->count_of_incoming_max_halp_path = node->count_of_incoming_max_halp_path
                        + node->left->count_of_leaf_on_distance_h;
                }
                else if (node->length_of_incoming_max_half_path < node->left->height + 1) {
                    node->right->length_of_incoming_max_half_path = node->left->height + 2;
                    node->right->count_of_incoming_max_halp_path = node->left->count_of_leaf_on_distance_h;
                }
                else {
                    node->right->length_of_incoming_max_half_path = node->length_of_incoming_max_half_path + 1;
                    node->right->count_of_incoming_max_halp_path = node->count_of_incoming_max_halp_path;
                }
                break;
            }
            case 1: {
                if (node->left == nullptr) {
                    node->right->count_of_incoming_max_halp_path = node->count_of_incoming_max_halp_path;
                    node->right->length_of_incoming_max_half_path = node->length_of_incoming_max_half_path + 1;
                }
                else {
                    node->left->count_of_incoming_max_halp_path = node->count_of_incoming_max_halp_path;
                    node->left->length_of_incoming_max_half_path = node->length_of_incoming_max_half_path + 1;
                }
                break;
            }
            case 0: {

                break;
            }
            default:
                break;
            }
            if (node->length_of_incoming_max_half_path + node->height == this->max_length_of_half_path) {
                if (node != this->root) {
                    node->count_of_diffrence_half_path_if_not_root = node->count_of_incoming_max_halp_path * node->count_of_leaf_on_distance_h;
                }
            }
            if (node->count_of_diffrence_half_path_if_not_root + node->count_of_diffrence_half_path_if_root > max_count_of_half_paths) {
                max_count_of_half_paths = node->count_of_diffrence_half_path_if_not_root + node->count_of_diffrence_half_path_if_root;
            }
        };
        this->pre_order_traversal(action1);
        return max_count_of_half_paths;
    }
    void delete_nodes_with_max_half_path_count() {
        this->set_heights_and_lengths_of_half_paths();
        long long max = this->set_counts_of_half_paths_and_get_max();
        /* auto action = [&](Node* node) {
             if (node->count_of_diffrence_half_path_if_not_root + node->count_of_diffrence_half_path_if_root == max) {
                 this->remove_node_by_pointer(node);
             }
         };
         this->post_order_traversal(action);*/
        std::stack<Node*> node_stack;
        std::vector<Node*>removing_nodes;
        Node* top = this->root;
        while (top != nullptr || !node_stack.empty()) {
            if (!node_stack.empty()) {
                top = node_stack.top();
                node_stack.pop();
                if (!node_stack.empty() && top->right == node_stack.top()) {
                    top = node_stack.top();
                    node_stack.pop();
                }
                else {
                    if (top->count_of_diffrence_half_path_if_not_root + top->count_of_diffrence_half_path_if_root == max) {
                        removing_nodes.push_back(top);
                    }
                    top = nullptr;
                }
            }
            while (top != nullptr) {
                node_stack.push(top);
                if (top->right != nullptr) {
                    node_stack.push(top->right);
                    node_stack.push(top);
                }
                top = top->left;
            }
        }
        for (Node* tmp : removing_nodes) {
            this->remove_node_by_pointer(tmp);
        }
    }
};

void pre_order_traversal_to_file(Tree& tree, std::string filename = "out.txt") {
    std::ofstream of(filename);
    auto action = [&](Node* node) {
        of << std::to_string(node->value) + '\n';
    };
    tree.pre_order_traversal(action);
}
int main() {
    std::ifstream in("in.txt");
    std::string line;
    Tree tree;
    while (getline(in, line)) {
        tree.insert_with_parrent(stol(line));
    }
    tree.delete_nodes_with_max_half_path_count();
    pre_order_traversal_to_file(tree);
}
