// Search
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::unique_ptr;
using std::cout;
using std::endl;
using std::cerr;

// create an unordered graph node
class GraphNode
{
public:
	int val;
	vector<GraphNode*> adjacent;
};

// create a binary tree node
class BSTNode
{
public:
	BSTNode(int _v=0)
	: val(_v), l(NULL), r(NULL)
	{}
		
	int val;
	BSTNode* l;
	BSTNode* r;
};

// create and populate a random BST
class BSTTree
{
public:
	BSTTree()
		{ }
 	~BSTTree(); // Iterate through the tree and delete all nodes
	
	void createAndPopulate(int n); // create the tree of n elements and populate with random values
	void insert(BSTNode*& root, int v);
	void printInOrder(const BSTNode* root) const;
	
	const BSTNode* DFS(int val) const;
	
	BSTNode* root() { return _root; }
private:
	void deleteTree(BSTNode* root);
	void printInOrderHelper(const BSTNode* root) const;
	const BSTNode* DFSHelper(const BSTNode* curr, int val) const;
	BSTNode* _root;
};

void BSTTree::insert(BSTNode*& root, int v)
{
	cerr << "Insert " << v << endl;
	if(root == NULL)
		root = new BSTNode(v);
	else if(v <= (root)->val)
	{
		if(root->l != NULL)
		{
			cerr << "go left" <<endl;
			insert(root->l, v);
		}
		else
		{
			root->l = new BSTNode(v);
		}
	}
	else
	{
		if(root->r != NULL)
		{
			cerr << "go right" << endl;
			insert(root->r, v);
		}
		else
		{
			root->r = new BSTNode(v);
		}
	}
}

BSTTree::~BSTTree()
{
	// delete all the nodes post-order
	deleteTree(_root);
}

void BSTTree::deleteTree(BSTNode* root)
{
	if(root == NULL)
		return;
	if(root->l != NULL)
	{
		deleteTree(root->l);
	}
 	if(root->r != NULL)
	{
		deleteTree(root->r);
	}
	delete root;
}

void BSTTree::createAndPopulate(int n)
{
	srand(time(NULL));
	for(int i=0; i < n; ++i)
	{
		int val = rand() % 1000;
		cerr << "inserting " << val << endl;
		insert(_root, val);
	}
}

void BSTTree::printInOrder(const BSTNode* root) const
{
	printInOrderHelper(root);
	cout << endl;
}

void BSTTree::printInOrderHelper(const BSTNode* root) const 
{
	if(root==NULL)
		return;
	if(root->l != NULL)
	{
		printInOrderHelper(root->l);
	}
	cout << root->val << " ";
	if(root->r != NULL)
	{
		printInOrderHelper(root->r);
	}
}

const BSTNode* BSTTree::DFS(int val) const
{
	if(_root != NULL)
	{
		return DFSHelper(_root, val);
	}
	else
		return NULL;
}

const BSTNode* BSTTree::DFSHelper(const BSTNode* curr, int val) const 
{
	const BSTNode* result;
	if(curr == NULL)
	{
		return NULL;
	}
	if(val == curr->val)
		return curr;
	
	if((result = DFSHelper(curr->l, val)) != NULL)
		return result;
	
	else if((result = DFSHelper(curr->r, val)) != NULL)
		return result;
	else
		return NULL;
}

int main(int argc, char** argv)
{
	BSTTree bst;
	cerr << "here 1" << endl;
	bst.createAndPopulate(100);
	cerr << "here 2" << endl;
	bst.printInOrder(bst.root());
	const BSTNode* subtree;
	if((subtree = bst.DFS(250)) != NULL)
	{
		bst.printInOrder(subtree);
	}
}
