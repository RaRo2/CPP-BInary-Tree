#include "tree.hpp"

int main(){

	BST<int> t;
	
	t.add_vertex("v1", 15);
	t.add_vertex("v4", 5);
	t.add_vertex("v0", 10);
	t.add_vertex("v3", 30);
	t.add_vertex("v2", 17);
	t.add_vertex("v5", 1);
	t.add_vertex("v7", 3);
	t.add_vertex("v6", 20);

	// for (auto x : t.get_neighbours("v0")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	// for (auto x : t.get_neighbours("v1")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	// for (auto x : t.get_neighbours("v3")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	// for (auto x : t.get_neighbours("v4")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	// for (auto x : t.get_neighbours("v5")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	// for (auto x : t.get_neighbours("v6")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	// for (auto x : t.get_neighbours("v7")) {
	// 	cout << x << " ";
	// } 
	// cout << endl;
	cout << boolalpha;
	cout << t.num_vertices() << endl;
	cout << t.num_edges() << endl;

	cout << t.sum_weight() << endl;
	
	for(auto x : t.path_with_largest_weight()){
		cout << x << " ";
	}
	cout << endl;
}
