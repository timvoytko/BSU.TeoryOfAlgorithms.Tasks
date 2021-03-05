#include<map>
#include<fstream>
#include<string>
#include<iostream>
#include<stack>
#include<vector>
#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:167772160")
std::string check_if_tree_binary() {
	// Node == pair - pair(left child number, right child number),(parent, value)
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	freopen("bst.in", "r", stdin); 
	int size;
	scanf("%d", &size);
	std::vector<std::pair<std::pair<int, int>,std::pair<int, long int>>> tree(size+1);
	long int root_value;
	scanf("%d", &root_value);
	tree[1] = { {0,0},{0,root_value} };
	for (int i = 2; i <=size; i++) {
		long int m;
		int p;
		char lr;
		scanf("%d %d %c", &m, &p, &lr);
		if (lr == 'R') {
			tree[p].first.second = i;
			tree[i].second.first = p;
			if (m >= tree[p].second.second) {
				tree[i].second.second = m;
			}
			else {
				return "NO";
			}
		}
		else {
			tree[p].first.first = i;
			tree[i].second.first = p;
			if (m < tree[p].second.second) {
				tree[i].second.second = m;
			}
			else {
				return"NO";
			}
		}
	}
	std::stack<int> stack_of_node_indexes;
	// so if it was binary search tree, this vector should be sorted(after inOrder)
	std::vector<long int> sorted_values;
	int top = 1;
	int prev = 0;
	// inOrder
	while (top != 0 || !stack_of_node_indexes.empty()) {
		if (!stack_of_node_indexes.empty()) {
			top = stack_of_node_indexes.top();
			stack_of_node_indexes.pop();
			sorted_values.push_back(tree[top].second.second);
			prev = top;
			top = tree[top].first.second;
			if (!stack_of_node_indexes.empty() && top!=0) {
				// so we want to find first left parrent and check >=
				while (prev != tree[stack_of_node_indexes.top()].first.first) {
					prev = tree[prev].second.first;
				}
				int first_left = tree[stack_of_node_indexes.top()].second.second;
				if (first_left <= tree[top].second.second) {
					return "NO";
				}
			}
		}
		while (top !=0) {
			stack_of_node_indexes.push(top);
			top = tree[top].first.first;
		}
	}
	for (int i = 1; i < sorted_values.size(); i++) {
		if (sorted_values[i - 1] > sorted_values[i]) {
			return "NO";
		}
	}
	return "YES";

}
int main() {
	std::ofstream of("bst.out");
	of << check_if_tree_binary();
	
}
