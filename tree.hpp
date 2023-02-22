#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

template <typename T> // the template allows the weight of vertex to take any numeric data type (denoted by T).
class BST {
	public:
        /* define your data structure to represent a binary search tree (bst) */

        vector<pair<string,T>> bst;                             // BST is made from a vector of a string (key), template (weight) pair
        vector<bool> in_bst;                                    // A boolean vector to check if the current position is filled by a vertex or not

        T total_weight = 0;                                     // A template value that collects the sum of all vertices' weights  
        vector<string> vertices;                                // A vector of strings to get all filled vertex keys in the BST



        /* added methods */
        int num_child(const string& u);                         // Gets the number of children of a given vertex
        int get_position(const string&);                        // Gets the position of a given vertex
        bool is_left_child(const string&, const string&);       // Tests if the second vertex is a left child of the first
        bool is_right_child(const string&, const string&);      // Tests if the second vertex is a right child of the first
        vector<string> get_path(int);                           // Gets the path of a vertex to the root vertex given it's weight

        /* test1 */
		BST(); // the contructor function.
		~BST(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the bst.
		size_t num_edges(); // returns the total number of edges in the bst.
        T sum_weight(); // return the total weight of all the vertices in the bst.

        /* test2 */
        void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
        
        /* test3 */

        vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
        vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
                                     //     Leaves are the vertices that do not have any children in the bst.

        /* test4 */
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
		
        /* test8 */
        vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
        
        /* test9 */
        vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
        
        /* test10 */
        vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
		
        /* test11 */
        vector<string> path(const string&, const string&);  // returns a vector of all the vertices in the path from the first vertex to the second vertex.
                                                            //     A path should include the source and destination vertices at the begining and the end, respectively.

        /* test12 */
        vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
                                       //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.

        /* test13 */
        size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

        /* test14 */
        void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.
};

/* test1 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
BST<T>::BST() {
    bst.resize(10);                                                         // Set the size of the BST to 10
    in_bst.resize(10);                                                      // Set the size of the vector to check if the position in BST is filled to 10
}

template <typename T>
BST<T>::~BST() {}


template <typename T>
size_t BST<T>::num_vertices() {
    return vertices.size();                                                 // Returns the size of the vector 'vertices'
}

template <typename T>
size_t BST<T>::num_edges() {
    if (vertices.size() < 1) {                                              // If the vertices vector is empty, return 0 for the number of edges
        return 0;
    }
    else {                                                                  // If the vertices vector is not empty, return the number of vertices subtract 1
        return (num_vertices()-1);                                          // since in a BST, the number of edges is always 1 less than the number of vertices
    }
}

template <typename T>
T BST<T>::sum_weight() {
    return total_weight;                                                    // Return the total weight of all the vertices
}

/* test2 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {
    int pos = 0;                                                            // Set a integer value called position to zero
    while (pos < bst.size() && in_bst[pos]) {                               // While the position value is less than the size of the BST and the position contains a vertex
        if (w < bst[pos].second) {                                          // If the weight is less than the current vertex
            pos = 2*pos+1;                                                  // Set the position to the double of the current value plus 1 
        }   
        else {                                                              // If the weight is greater than or equal to the current vertex
            pos = 2*pos+2;                                                  // Set the position to the double of the current value plus 2
        }
    }
    while (pos >= bst.size()) {                                             // If the position becomes greater than the size of the BST
        bst.resize(2*bst.size());                                           // Double the size of the BST to make room 
        in_bst.resize(2*in_bst.size(), false);                              // Double the size of the vector used to check if the positions are filled
    }
    bst[pos] =  make_pair(u,w);                                             // Fill the current position of the BST to the added pair
    vertices.push_back(u);                                                  // Add this vertex into the vertices vector
    total_weight+= w;                                                       // Add the weight into the total weight
    in_bst[pos] = true;                                                     // Set the position of the BST to be marked as filled by a vertex 
}

template <typename T>
bool BST<T>::contains(const string& u) {
    for (auto i : vertices) {                                               // Looping through the vertices vector to check 
        if (i == u) {                                                       // if the input key is equal to any existing key
            return true;                                                    // If there is a match, set to true
        }
    }
    return false;                                                           // Else, set to false
}

/* test3 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::get_vertices() {
    return vertices;                                                        // Return the vertices vector
}

template <typename T>
vector<string> BST<T>::get_leaves() {
    vector<string> leaves;                                                  // Create a vector which will hold all leaf nodes
    for (int pos = 0 ; pos < bst.size(); pos++) {                           // Loop over all positions in the BST
        if (in_bst[pos] && num_child(bst[pos].first) == 0)  {               // If the position is filled and the number of children is zero
            leaves.push_back(bst[pos].first);                               // Add the vertex into the vector leaves
        }
    }
    return leaves;                                                          // Return the leaves vector
}

/* test4 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) {
    for (int pos = 0 ; pos < bst.size(); pos++) {                           // For each position in the BST
        if (2*pos+2 < bst.size()) {                                         // Check if the position is still within the boundary
            if (in_bst[pos] && (in_bst[2*pos+1] || in_bst[2*pos+2]) &&      // If the position and the child is within the BST 
                bst[pos].first == u || bst[pos].first == v) {               // If the current key at the current position is the same as either input key
                if (bst[2*pos+1].first == v || bst[2*pos+2].first == v ||   // If the second input key is in the left or right position of the first input key
                    bst[2*pos+1].first == u || bst[2*pos+2].first == u) {   // or if the first is in the left or right position of the second input key
                    return true;                                            // Return true
                }
            }
        }
        
    }
    return false;                                                           // Return false
}   

/* added methods ---------------------------------------------------------------------------------------------------------------------------------------------------*/
template <typename T>
int BST<T>::get_position(const string& u) {                                 
    int pos = 0;                                                            // Set position to zero
    for (int pos = 0; pos < bst.size(); pos++) {                            // For each position in the BST
        if (in_bst[pos] && bst[pos].first == u) {                           // If the position is in the BST and the value is equal to the input
            return pos;                                                     // Return this position
        }
    }
    return -1;                                                              // Returns negative one is nothing is found
}

template <typename T>
bool BST<T>::is_left_child(const string& parent, const string& child) {
    return (2*(get_position(parent))+1 == get_position(child) );            // Return if the child key is equal to the double of the parent key + 1 indicating left
}

template <typename T>
bool BST<T>::is_right_child(const string& parent, const string& child) {
    return (2*(get_position(parent))+2 == get_position(child) );            // Return if the child key is equal to the double of the parent key + 2 indicating right
}

template <typename T>
int BST<T>::num_child(const string& u) {                                    
    int num = 0;                                                            // Set number of children to zero
    for (auto i : get_neighbours(u)) {                                      // For each neighbour of the input vector
        if (is_left_child(u,i)) {                                           // If the neighbour is a left child of input vector
            num++;                                                          // Increment number of children by one
        }
        if (is_right_child(u,i)) {                                          // If the neighbour is a right child of input vector
            num++;                                                          // Increment number of children by one
        }   
    }
    return num;                                                             // Return the number of children
}

/* test5 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<pair<string,string>> BST<T>::get_edges() {               
    vector<pair<string, string>> edges;                                     // Create an edges vector to store each edge in the form (A,B)
    for (auto i : vertices) {                                               // Loop over the vertices vector once through key i
        for (auto j : vertices) {                                           // Loop over the vertices vector again through key j
            if (adjacent(i,j) &&                                            // If both vertices are adjacent
                !count(edges.begin(), edges.end(), make_pair(j,i)) ) {      // and the edge does not exist in the edge vector yet
                edges.push_back(make_pair(i,j));                            // Add the pair into the vector
            }
        }
    }
    return edges;                                                           // Return the vector edges
}   

/* test6 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {
    vector<string> neighbours;                                              // Create a vector for all neighbours of a vertex
    int pos = 0;
    for (int pos = 0 ; pos < bst.size(); pos++) {                             // Loop over all positions in the BST
        if (in_bst[pos] && adjacent(u,bst[pos].first)) {                    // If the position is filled and the vertex in the position is adjacent to the input vertex
            neighbours.push_back(bst[pos].first);                           // Add the vertex key in the position into the vector
        }
    }
    return neighbours;                                                      // Return the neighbours vector
}

template <typename T>
size_t BST<T>::degree(const string& u) {
    return get_neighbours(u).size();                                        // Return the size of the neighbours vector of a given vertex
}

/* test7 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::preorder_traversal() {
    vector<string> output;                                                  // Create an output vector for the traversal
    stack<string> s;                                                        // Create a stack to collect the vertices in order
    int pos = 0;                                                            // Set an integer position to zero
    string current = bst[pos].first;                                        // Set a string current to be the first (root) vector in the BST
    while (pos < bst.size() && in_bst[pos]) {                               // While the position is filled in the BST and the position is still less than the BST size
        output.push_back(current);                                          // Add the current string into the output vector
        if ((2*pos+2 < bst.size()) && in_bst[2*pos+2]) {                    // If the right position is within the BST and is filled
            s.push(bst[2*pos+2].first);                                     // Add the right child to the stack
        }   
        if ((2*pos+1 < bst.size()) && in_bst[2*pos+1]) {                    // If the left position is within the BST and is filled
            s.push(bst[2*pos+1].first);                                     // Add the left child to the stack
        }
        if (!s.empty()) {                                                   // If the stack is not empty
            current = s.top();                                              // Set the current value to the top of the stack
            for (int i = 0 ; i < bst.size() ; i++) {                        // For each position (i) in the BST 
                if (bst[i].first == current) {                              // If the position's key is the same as the current key
                    pos = i;                                                // Set the position to 'i'
                }
            }
            s.pop();                                                        // Delete the top of the stack 
        }
        else {                                                              // If the stack is empty
            break;                                                          // Break out of the loop
        }
    }
    return output;                                                          // Return the output vector
}

/* test8 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::inorder_traversal() {
    vector<string> output;                                                  // Create an output vector for the traversal
    vector<T> sorted_weights;                                               // Create a vector which gets all the weights in ascending order

    for (int pos=0; pos < bst.size(); pos++) {                              // For each position in the BST
        if (in_bst[pos]) {                                                  // If the current position is filled in the BST
            sorted_weights.push_back(bst[pos].second);                      // Add the weight into the vector
        }
    }
    sort(sorted_weights.begin(), sorted_weights.end());                     // Sort the weights in ascending order
    
    for (auto i : sorted_weights) {                                         // For each value in the sorted_weights vector
        for (int j=0; j < bst.size(); j++) {                                // For each position (j) in the BST
            if (in_bst[j] && bst[j].second == i) {                          // If the position (j) is filled and the weight is equal to the current smallest weight
                output.push_back(bst[j].first);                             // Add the current key into the output
            }
        }                                   
    }
    return output;                                                          // Return the output vector
}                                                                           // Since inorder traversal goes from the smallest to the largest, we can sort the weights
                                                                            // and add each vertex from their weights from the smallest to largest

/* test9 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::postorder_traversal() {

    return vector<string>();
}

/* test10 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::breadth_first_traversal() {
    vector<string> output;                                                          // Create an output vector for the traversal
    queue<string> q;                                                                // Create a queue to collect the vertices in order
    
    for (int pos = 0; pos < bst.size(); pos++) {                                    // For each position within the BST
        q.push(bst[pos].first);                                                     // Add the positions key into the queue
        while (!q.empty() || in_bst[pos]) {                                         // If the queue is empty 
            string current = q.front();                                             // Set a ctring called current to take th e value of the front of the queue
            q.pop();                                                                // Delete the front of the queue
            if (!count(output.begin(), output.end(), current) && in_bst[pos]) {     // If the position is filled and the current key is not in the current 
                output.push_back(current);                                          // Add the current key to the output vector
                break;                                                              // Break out of the loops
            }
        }
    }
    return output;                                                                  // Return the output vector
}

/* test11 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v){
    int i=0, j=0, intersection=0;                                                   // Set integer values for i and j and the intersection position
    vector<string> path1, path2, final_path;                                        // Create three string vectors for both key's path from root and the output path
    int weight1 = bst[get_position(u)].second;                                      // Set the first weight to weight of key 'u'
    int weight2 = bst[get_position(v)].second;                                      // Set the second weight to the weight of key 'v'
    if (u==v) {                                                                     // If u and v are the same key
        return final_path;                                                          // Return an empty path
    }
    path1 = get_path(weight1);                                                      // Set path1 to be the path of the root to the key 'u'
    path2 = get_path(weight2);                                                      // Set path2 to be the path of the root to the key 'v'

    while (i != path1.size() || j != path2.size()) {                                // While one of the counters i and j are still smaller than the size of their path
        if (i == j && path1[i] == path2[j]) {                                       // If both follow the same path on the same vertex
            i++;                                                                    // Add to i
            j++;                                                                    // Add to j
        }
        else {                                                                      // If the path begins to diverge
            intersection = j - 1;                                                   // Set the intersection point as where they begin to diverge from root
            break;                                                                  // Break out of the loop
        }
    }
    for (int i = path1.size() - 1; i > intersection; i--) {                         // From the end vertex of path1 to the intersection, 
        final_path.push_back(path1[i]);                                             // add each vertex into the final path 
    }
    for (int i = intersection; i < path2.size(); i++) {                             // From the intersection to end vertex of path2
        final_path.push_back(path2[i]);                                             // add each vertex into the final path 
    }
    return final_path;                                                              // Return the final path
}

/* added method ----------------------------------------------------------------------------------------------------------------------------------------------------*/

template<typename T>
vector<string> BST<T>::get_path(int w) {
    int pos = 0;                                                                    // Set the current position to zero
    vector<string> path;                                                            // Create a vector called path
    while (in_bst[pos] && pos < bst.size()-1) {                                     // While the position is filled in the BST and is still less than the BST - 1
        if (bst[pos].second < w) {                                                  // If the vertex at position has a smaller weight than w
            path.push_back(bst[pos].first);                                         // Add the vertex's key to the path
            pos = 2*pos+2;                                                          // Set the position to the right child 
        }
        else if (bst[pos].second > w) {                                             // If the vertex at position has a larger weight than w
            path.push_back(bst[pos].first);                                         // Add the vertex's key to the path
            pos = 2*pos+1;                                                          // Set the position to the left child 
        }
        else if (bst[pos].second == w) {                                            // If the vertex at position is equal to the weight w
            path.push_back(bst[pos].first);                                         // Add the vertex's key to the path
            break;                                                                  // Break out of the loop
        }    
    }
    return path;                                                                    // Return the path
}


/* test12 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<string> BST<T>::path_with_largest_weight(){
    return vector<string>();
}

/* test13 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
size_t BST<T>::height() {
    int height = 0;                                                                 // Set the height to zero
    vector<string> leaves = get_leaves();                                           // Create a string vector for all the leaves
    for (auto leaf : leaves) {                                                      // For each leaf in the leaves vector
        for (int pos = 0; pos < bst.size(); pos++) {                                // Loop through the whole BST
            if (in_bst[pos] && bst[pos].first == leaf) {                            // If the BST is filled at the position and the position is of a leaf
                if (int(log(pos)/log(2)) > height) {                                // If the position of the leaf's power of 2 is greater than the height
                    height = int(log(pos)/log(2));                                  // Set the height to be the this
                }              
            }
        }
    }
    return height;                                                                  // Return the height
                                                                                    // Basically, since the position of each filled vector is always (2x parent + 1 or 2)
}                                                                                   // If we get the furthest leaf node and get its position, it's position will always 
                                                                                    // be closest to 2 to the power of the height 
/* test14 ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
void BST<T>::remove_vertex(const string& u) {}

