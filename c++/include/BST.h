/**
 * @file BST.h
 * @brief Advanced Programming final exam
 * @author Michela Venturini and Alessia Paoletti
 */

#include <iostream>
#include <memory>
#include<vector>
//#include <string> <--- tree to string
#include<functional>
/**
 * @brief Class that implements a Binary Search Tree
 *
 *The implementation is a simple not autobalancing Binary Search Tree.
 *The binary tree is ordered according to the keys and it is templated on the
 * of the key and on the type of the value.
 *
 *@tparam K the key typename
 *@tparam V the value typename
 *@tparam C the comparison function
 */
template <typename K, typename V, typename C = std::greater<K>>
class BST{

private:
		struct Node;
		/** Unique pointer to the root of the tree */
		std::unique_ptr<Node> root{nullptr};

public:
		class Iterator;
		class ConstIterator;
		/**  The comparison operator  */
		C compare;

public:

	/** construct a new BST object */
	BST(){};
	/**
	 *@brief Move constructor
	 *@param other: the tree that has to be moved
	 */
	BST(BST<K,V,C>&& other) noexcept: root{std::move(other.root)} {}
	/**
	 *@brief Copy constructor
	 *@param other the tree that has to be copied
	 */
	BST(const BST<K,V,C>& other){
		if(other.root) copy(*other.root);
	}

	/** default destructor*/
	~BST() noexcept = default;

	/**
	 *@brief Move assigment
	 *@param other: the tree that has to be moved
	 */
  BST<K,V,C>& operator=(BST<K,V,C>&& other) noexcept{
    root = std::move(other.root);
    return *this;
  }

	/**
	 *@brief Copy assigment
	 *@param other: the tree that has to be copied
	 */
	BST<K,V,C>&operator=(const BST<K,V,C>& other ){
		if(!other.root) root.reset();
		else {
			if (root) clear();
			copy(*other.root);
		}
		return *this;
	}

	/**
	 *@brief Non const version of the overloading of the operator[]
	 *
	 * If the key exists in the tree, the corresponding value is returned,
	 * otherwise a node with that key and empty value is added to the tree.
	 *
	 *@param current_key: the key that has to be search
	 *@return the value corresponding to the key
	 */
	V& operator[](const K& current_key);

	/**
	 *@brief Const version of the overloading of the operator[]
	 *
	 * If the key exists in the tree, the corresponding value is returned.
	 *@param current_key: the key that has to be search
	 *@return the value corresponding to the key if it exists
	 */
	const V& operator[](const K& current_key) const;

  /**
	*@brief Overloading the operator<<
	*
	*@param out: the std::ostream where to print the result
	*@param bst: the BST to print
	*@return: std::ostream&
	*/
	template <typename k, typename v, typename c>
	friend std::ostream& operator<< (std::ostream& out, const BST<k,v,c>& bst);

private:

	/**
	 *@brief Auxiliar function to add a node in the tree
	 *
	 *Given a node passed as argument, the key of this node is compared with
	 *the key of the node that we want to add.
	 *If the new key is greater than the key of the node and the node does not have
	 *the right child, the new node becomes its right child, otherwise a recursive
	 *call on the right child is done.
	 *If the new key is lower than the key of the node and the node does not have left
	 *child, the new node becomes its left child, otherwise a recursive vall on the left
	 *child is done.
	 *In this function it also decided the value of parent of new node. If the new
	 *node is added as a right child, his parent is the parent of the node who added him.
	 *If the new node is added as left child, his parent is the node who added him.
	 *This decision is done to allow a simpler in order crossing of the tree.
	 *
	 *@param current_node: the node used for the comparison of the key
	 *@param key: the const key of the pair
	 *@param val: the value of the pair
	 */
	bool insert(Node* current_node, const K key, const V val);

	/**
	 *@brief Control if the tree is balanced.
	 *
	 *Given a node, it is checked that the tree with that node as root is
	 *balanced or not. To check if a tree is balanced the difference between the
	 *height of the right subtree and the height of the left subtree is less or
	 *equal to 1. To know if the right and the left subtrees are balanced
	 *recusrive call of this function are done.
	 *The function height() is used to compute the height of the trees.
	 *
	 *@param current_node is the root of the tree
	 *@return true if the tree is balanced, false otherwise
	 */
	bool isBalanced(Node* current_node) const noexcept;

	/**
	 *@brief Compute the height of the tree
	 *
	 *Given the root of the tree as parameter, the height of the tree is computed.
	 *
	 *@param current_node is the root of the tree
	 *@return the height of the tree

	*/
	size_t height(const Node* current_node) const noexcept;

	/**
	 *@brief Store in order the nodes in a vector.
	 *
	 *Auxiliar function to balance the tree.
	 *This function stores the pair(key,value) of the Node in the vector. Since
	 *we want to store the nodes in order, if the node has the left child before store
	 *the his pair a recursive call on the left child is done. Then the his pair is
	 *stored and it has a right child a recursive call on him is done.
	 *
	 *@param current_node is the root of the tree
	 *@param vector_nodes the vector of the pairs(key,value) of the nodes of the tree
	*/
	void storeBST(Node* current_node, std::vector<std::pair<K,V>>& vector_nodes);

	/**
	 *@brief Auxiliar function to balance the tree
	 *
	 *The aim is to store in order the pairs of the nodes of the tree.
	 *Every time the middle node of the vector that start in the index start
	 *and end in the index end is addes to the tree. Then recursive call are done
	 *on the left part and on the right part of the vector.
	 *The function will stop when the index start is greater than the index end.
	 *
	 *@param start start index of the vector
	 *@param end end index of the vector
	 *@param vector_nodes the vector of the pairs(key,value) of the nodes of the tree
	*/
	void balanceHelper(std::vector<std::pair<K,V>>& vector_nodes, int start, int end);

/**
	*@brief Auxiliar function to do the deep copy of tree
	*
	*This auxiliar function is used both in the copy constructor and in the copy
	*assigment.Given a node as parameter, in order to do a deep copy,a node with
	*same key and value is added to the tree. If the node given as parameter has
	*the left child and/or the right child recursive calls are done on them.
	*
	*@param current_node the node that has to be copied
 */
	void copy( const Node& current_node);

	/**
		*@brief Auxiliar function for the FindFunction
		*
		*This auxiliar function is used to find a key in the tree.
		*Given a node as parameter, the key to find is compared with the key of the
		*node. If it is greater, the key is searched (through a recursive call) in the
		*subtree with root the right child of the node (if exists).
		*If the key is lower than the key of node, it is searched (through a recursive call)
		*in the subtree with root the left child of the node (if exists).
		*If the key to find is equal to the key of the node, an Iterator to that node
		*is returned. If the key is not in the tree, an Iterator to end() is returned.
		*
		*@param key: the key that has to be find the tree
		*@param current_node the node that has to be copied
		*@return an Iterator to the corresponding node if the key is found,
		*an Iterator to end() otherwise
	 */
	Iterator findHelper(const K key, Node* current_node) const;

public:
	/**
	* @brief Find a node in the tree
	*
  *Given a key return an Iterator to that node. If the key is not found
	*end() is returned.
	*
	*@param key: the key that has to be search in the tree
	*@return an Iterator to the corresponding node if the key is found,
	*an Iterator to end() otherwise
	*/
	Iterator find(const K key) const noexcept;

	/**
	* @brief Return an Iterator to the first node
	*
  *The first node in the traversal order is the node with minimum key.
	*/
	Iterator begin() const noexcept {
		Node* beg = root.get();
		while(beg->left) beg=beg->left.get();
		return Iterator{beg};
	}

	/**
	* @brief Return an Iterator that indicates the end of tree.
	*
  *The end of the tree is indicated as nullptr
	 */
	Iterator end() const noexcept {
		return Iterator{nullptr};
	}

	/**
	* @brief Return a ConstIterator to the first node
	*
  *The first node in the traversal order is the node with minimum key.
	 */
	ConstIterator cbegin() const noexcept {
		Node* beg = root.get();
		while(beg->left) beg=beg->left.get();
		return ConstIterator{beg};
	}
	/**
	* @brief Return a ConstIterator that indicates the end of tree.
	*The end of the tree is indicated as nullptr
	 */
	ConstIterator cend() const noexcept{
		return ConstIterator{nullptr};
	}

	/**
	* @brief Add a node in the tree
	*
	* If the tree is empty, the node becomes the root of the tree.
	* If in the tree some nodes are already present, the node is inserted according
	* to the key.
	*
	*@param key: is the const key of the pair of the node
	*@param val: is the val of the pair of the node
	 */
	bool add(const K key, const V val);

	/**
	* @brief Clean the tree
	*/
	void clear() noexcept {
		root.reset(nullptr);
	}

	/**
	* @brief Balance a tree
	*
	*After checking that the tree exists and that it is not already balanced,
	*all the pairs (key,value) of all the nodes of the tree are stored in order
	*in a vector.
	*Then the unbalanced tree is deleted and a new balanced is created.
	*
	*@param key: is the const key of the pair of the node
	*@param val: is the val of the pair of the node
	 */
	void balance();

	//const Node* getRoot() const noexcept{ return root.get(); }

	//void treeToString(const Node* root) const;
};


/**
 * @brief Structure that implements a node of the tree.
 *
 *Each node stores a pair of a const key and the associated value.
 *Each node can have at most 2 children, left child and right child.
 *For each node is also stored the parent node, whose value depends on the order
 *with the nodes are added in the tree.
 *The node, is templated on the type of the key, on the type of the value and on
 *the comparison operator of the key.
 *
 *@tparam K the key typename
 *@tparam V the value typename
 *@tparam C the comparion operator typename
 */
template <typename K, typename V, typename C>
struct BST<K,V,C>::Node {
	/** pair with const key and value*/
	std::pair<const K, V> pair;
	/** left child*/
  std::unique_ptr<Node> left{};
	/** right child*/
  std::unique_ptr<Node> right{};
	/** parent node*/
  Node* const parent{};

	/** constructor for a new Node object */
	Node(const K key,const V val, Node *const parent):
  	pair{std::make_pair(key,val)},
    left{nullptr},
    right{nullptr},
    parent{parent} {}

	/** default destructor */
  ~Node() noexcept = default;
};

/**
 * @brief Class that implement an Iterator .
 *
 *The Iterator is used to scan the entire BST without knowing its implementation.
 *An Iterator stores a pointer to a node.
 *The class inherits from std::iterator of forward category and with
 *std::pair<const K, V> as type obtained by dereferencing the iterator.
 *The Iterator is templated on the type of the key, on the type of the value
 *of the node and on the type of comparison operator of the key.
 *
 *@tparam K the key typename
 *@tparam V the value typename
 *@tparam C the comparison operator typename
 */
template <typename K, typename V, typename C>
class BST<K,V,C>::Iterator : public std::iterator<std::forward_iterator_tag,std::pair<const K, V>>{

	public:
		/** pointer to one Node*/
		BST<K,V,C>::Node* current{};

		/**constructor for a new Iterator object */
		Iterator(BST<K,V,C>::Node* n): current{n} {}

		/** Overloading of the operator ==  */
		bool operator== ( const Iterator another_it ) const {
			return (another_it.current == current) ;
		}

		/** Overloading of the operator !=  */
		bool operator!= ( const Iterator another_it) const {
			return (another_it.current != current);
		}

		/** Overloading of the prefix increment  */
		Iterator& operator++();

		/** Overloading of the postfix   */
		Iterator operator++ (int) {
			Iterator prev = *this;
		 	++(*this);
		 	return prev;
		}

		/** Overloading of the operator *  */
		std::pair<const K,V>& operator*() const {
			if (current == nullptr) throw std::logic_error("Invalid iterator dereference!");
			return current->pair;
		}

		/** Overloading of the operator ->  */
		std::pair<const K,V>* operator->() const {
			return &(*(*this));
		}
};

/**
 * @brief Class that implement a ConstIterator .
 *
 *The Iterator is used to scan the entire BST without knowing its implementation.
 *A ConstIterator inherits from Iterator and overload only operator* and -> to
 * make them return pointer to a const Node.
 */
template <typename K, typename V, typename C>
class BST<K,V,C>::ConstIterator: public BST<K,V,C>::Iterator{

	public:
		using BST<K,V,C>::Iterator::Iterator;
		/** Overloading of the operator *  */
		const std::pair<const K,V>& operator*() const {
			return BST<K,V,C>::Iterator::operator*();
		 }

		/** Overloading of the operator ->  */
		const std::pair<const K,V>* operator->() const {
			return BST<K,V,C>::Iterator::operator->();
		}
};

template<typename K, typename V,typename C>
std::ostream& operator<<(std::ostream& out, const BST<K,V,C>& bst) {
	if (!bst.root) out<<"The tree does not exist";
	else {
		for(const auto& node : bst )
				out << "(" << node.first << ":" << node.second << ") ";
	}
	return out;
}

template<typename K, typename V,typename C>
V& BST<K,V,C>::operator[](const K& current_key){
	auto find_value = find(current_key);
	if (find_value!=end()) return find_value->second;
	else add(current_key, V{});
	auto find_value2 = find(current_key);
	return find_value2->second;
	}

template<typename K, typename V,typename C>
const V& BST<K,V,C>::operator[](const K& current_key) const{
	ConstIterator find_value = find(current_key);
	if (find_value!=end()) return find_value->second;
	//is a constant method, if it does not find the key it throws an exception
	throw std::runtime_error("This key does not exist in the tree");
}// ---> perché?

template<typename K, typename V, typename C>
bool BST<K,V,C>::insert(Node* current_node, const K key,  const V val) {
  if (compare(current_node->pair.first, key)){
    if (!current_node->left) {
      current_node->left.reset(new Node(key, val, current_node));
    } else {
      insert(current_node->left.get(), key, val);
    }
	} else if (compare(key, current_node->pair.first)){
    if (!current_node->right) {
        current_node->right.reset(new Node(key, val, current_node->parent));
    } else {
      insert(current_node->right.get(), key, val);
    }
  } else return false;
return true;
}

template<typename K, typename V, typename C>
bool BST<K,V,C>::add(const K key,const V val){
  if (root){
    return insert(root.get(), key, val);
  } else {
    root.reset(new Node(key, val, nullptr));
		return true;
  }
}

template<typename K, typename V, typename C>
bool BST<K,V,C>::isBalanced(Node* current_node) const noexcept {
	 if(!current_node) return true;
   int  lh, rh;
   lh = height(current_node->left.get());
   rh = height(current_node->right.get());

   if( abs(lh-rh) <= 1 && isBalanced(current_node->left.get()) && isBalanced(current_node->right.get()) )
     return true; //tree balanced
  return false; // tree not balanced
}

template<typename K, typename V, typename C>
size_t BST<K,V,C>::height( const Node* current_node) const noexcept {
   if(!current_node) return 0;
   return 1 + std::max(height(current_node->left.get()), height(current_node->right.get()));
}

template<typename K, typename V, typename C>
void BST<K,V,C>::storeBST(Node* current_node, std::vector<std::pair<K,V>>& vector_nodes){
  if (!current_node) return;
  storeBST(current_node->left.get(), vector_nodes);
  vector_nodes.push_back(current_node->pair); //store the pair (key,value) in the vector
  storeBST(current_node->right.get(), vector_nodes);
}

template<typename K, typename V, typename C>
void BST<K,V,C>::balanceHelper(std::vector<std::pair<K,V>>& vector_nodes, int start,int end){
  if (!(start>end)){
    int  mid = (start+end)/2;
    this->add(vector_nodes[mid].first, vector_nodes[mid].second );
    balanceHelper(vector_nodes,start,mid-1); //create left subtree
    balanceHelper(vector_nodes,mid+1,end); //create right subtree
  }
}

template<typename K, typename V, typename C>
void BST<K,V,C>::balance(){
	if (!root) return; //if the tree does not exist
  if( isBalanced(root.get())) return ; //if the tree is already balanced
  std::vector<std::pair<K,V>> vector_nodes;
  storeBST(root.get(),vector_nodes); //stores the nodes in order in the vector
  clear();
  balanceHelper(vector_nodes, 0,vector_nodes.size()-1); //create a new balance tree
	//std::cout<<vector_nodes.size()<<std::endl;
  vector_nodes.clear();
  std::vector<std::pair<K,V>>().swap(vector_nodes);
}

template<typename K, typename V, typename C>
typename BST<K,V,C>::Iterator BST<K,V,C>::find(const K key) const noexcept {
		if(!root) return Iterator{end()};
		return findHelper(key, root.get());
}

template <typename K, typename V, typename C>
typename BST<K,V,C>::Iterator BST<K,V,C>::findHelper(const K key, Node* current_node) const {
	//std::cout<<"key="<<key<<" current_node="<<current_node->pair.first<<std::endl;
	if (compare(key, current_node->pair.first)) {
		//if the key to find is greater than the key of the current_node,
		//search it in the subtree with root the right child of the current_node (if exists)
		if (current_node -> right) return BST<K,V,C>::findHelper(key, current_node -> right.get());
	}
	else if (compare(current_node -> pair.first, key) ) {
		//if the key to find is lower than the key of the current_node,
		//search it in the subtree with root the left child of the current_node (if exists)
		if(current_node->left) return BST<K,V,C>::findHelper(key, current_node -> left.get());
	}
	else if (key == current_node -> pair.first) return Iterator{current_node};
	return Iterator{end()};
	}

template <typename K, typename V, typename C>
void BST<K,V,C>::copy( const Node& current_node){
				add(current_node.pair.first, current_node.pair.second);
				if (current_node.left) copy(*current_node.left);
				if (current_node.right) copy(*current_node.right);
}

template <typename K, typename V, typename C>
typename BST<K,V,C>::Iterator& BST<K,V,C>::Iterator::operator++() {
	if (!current) throw std::out_of_range ("Out-of-bounds iterator increment!");
  if ( (!current->right && !current->left) || !current->right ){ 	//if the node has no children or only the left one
    current = current->parent; //the successor is the parent
  }
  else if ( current->right ) { // if the node has the right child
		//the successor is the node with min key in the subtree radicated in the right child
		current=current->right.get();
		while(current->left)
			current = current->left.get();
  }
  return *this;
}

// BST<K,V,C>::void treeToString(const Node* root) const
// {
// 		static std::string str='';
//     // bases case
//     if (!root) {
// 			std::cout<<str<<std::endl;
// 			return;
// 		}
//     // push the root data as character
//     str+=std::to_string(root->pair.first);
//     // if leaf node, then return
//     if (!root->left && !root->right) return;
//     // for left subtree
//     str.push_back('(');
//     treeToString(root->left.get());
//     str.push_back(')');
//
//     // only if right child is present to
//     // avoid extra parenthesis
//     if (root->right) {
//         str.push_back('(');
//         treeToString(root->right.get());
//         str.push_back(')');
//     }
//
// }
