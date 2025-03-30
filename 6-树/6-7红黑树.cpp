#include <iostream>
using namespace std;

// claude编写

enum Color {
    red, black
};

class Node 
{
public:
    int data;
    Node *left, *right, *parent;
    Color color;

    Node(int data)
    {
        this->data = data;
        this->color = red;
        this->left = this->right = this->parent = nullptr;
    }
};

class RedBlackTree
{
private:
    Node *root;
    
    // Utility functions
    void leftRotate(Node *x);
    void rightRotate(Node *y);
    void fixViolation(Node *&root, Node *&pt);
    void inorderHelper(Node *root);
    void fixDeleteViolation(Node *x, Node *parent, bool isLeft);
    Node* BST_insert(Node *root, Node *pt);
    Node* minimum(Node *node);
    void rbTransplant(Node *u, Node *v);
    void deleteFixup(Node *x, Node *xParent, bool isLeft);
    
public:
    RedBlackTree() { root = nullptr; }
    
    void insert(int data);
    void remove(int data);
    void inorder();
    Node* search(int data);
};

// Left rotation
void RedBlackTree::leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    
    if (y->left != nullptr)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

// Right rotation
void RedBlackTree::rightRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    
    if (x->right != nullptr)
        x->right->parent = y;
    
    x->parent = y->parent;
    
    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

// Fix violations after insertion
void RedBlackTree::fixViolation(Node *&root, Node *&pt)
{
    Node *parent_pt = nullptr;
    Node *grand_parent_pt = nullptr;
    
    while ((pt != root) && (pt->color != black) && (pt->parent->color == red))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        
        // Case A: Parent of pt is left child of Grand-parent of pt
        if (parent_pt == grand_parent_pt->left)
        {
            Node *uncle_pt = grand_parent_pt->right;
            
            // Case 1: The uncle of pt is also red
            if (uncle_pt != nullptr && uncle_pt->color == red)
            {
                grand_parent_pt->color = red;
                parent_pt->color = black;
                uncle_pt->color = black;
                pt = grand_parent_pt;
            }
            else
            {
                // Case 2: pt is right child of its parent
                if (pt == parent_pt->right)
                {
                    leftRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                
                // Case 3: pt is left child of its parent
                rightRotate(grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
        // Case B: Parent of pt is right child of Grand-parent of pt
        else
        {
            Node *uncle_pt = grand_parent_pt->left;
            
            // Case 1: The uncle of pt is also red
            if (uncle_pt != nullptr && uncle_pt->color == red)
            {
                grand_parent_pt->color = red;
                parent_pt->color = black;
                uncle_pt->color = black;
                pt = grand_parent_pt;
            }
            else
            {
                // Case 2: pt is left child of its parent
                if (pt == parent_pt->left)
                {
                    rightRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                
                // Case 3: pt is right child of its parent
                leftRotate(grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    
    root->color = black;
}

// Standard BST insertion
Node* RedBlackTree::BST_insert(Node *root, Node *pt)
{
    if (root == nullptr)
        return pt;
    
    if (pt->data < root->data)
    {
        root->left = BST_insert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data > root->data)
    {
        root->right = BST_insert(root->right, pt);
        root->right->parent = root;
    }
    
    return root;
}

// Insert a new key
void RedBlackTree::insert(int data)
{
    Node *pt = new Node(data);
    
    // Do a normal BST insert
    root = BST_insert(root, pt);
    
    // Fix Red-Black Tree violations
    fixViolation(root, pt);
}

// Find the node with minimum value
Node* RedBlackTree::minimum(Node *node)
{
    while (node->left != nullptr)
        node = node->left;
    
    return node;
}

// Replace u with v
void RedBlackTree::rbTransplant(Node *u, Node *v)
{
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    
    if (v != nullptr)
        v->parent = u->parent;
}

void RedBlackTree::fixDeleteViolation(Node *x, Node *parent, bool isLeft)
{
    while (x != root && (x == nullptr || x->color == black))
    {
        if (isLeft)
        {
            Node *w = parent->right;
            
            if (w->color == red)
            {
                w->color = black;
                parent->color = red;
                leftRotate(parent);
                w = parent->right;
            }
            
            if ((w->left == nullptr || w->left->color == black) && 
                (w->right == nullptr || w->right->color == black))
            {
                w->color = red;
                x = parent;
                if (x->parent != nullptr)
                {
                    isLeft = (x == x->parent->left);
                    parent = x->parent;
                }
                else
                    break;
            }
            else
            {
                if (w->right == nullptr || w->right->color == black)
                {
                    if (w->left != nullptr)
                        w->left->color = black;
                    w->color = red;
                    rightRotate(w);
                    w = parent->right;
                }
                
                w->color = parent->color;
                parent->color = black;
                if (w->right != nullptr)
                    w->right->color = black;
                leftRotate(parent);
                x = root; // To break the loop
            }
        }
        else
        {
            Node *w = parent->left;
            
            if (w->color == red)
            {
                w->color = black;
                parent->color = red;
                rightRotate(parent);
                w = parent->left;
            }
            
            if ((w->right == nullptr || w->right->color == black) && 
                (w->left == nullptr || w->left->color == black))
            {
                w->color = red;
                x = parent;
                if (x->parent != nullptr)
                {
                    isLeft = (x == x->parent->left);
                    parent = x->parent;
                }
                else
                    break;
            }
            else
            {
                if (w->left == nullptr || w->left->color == black)
                {
                    if (w->right != nullptr)
                        w->right->color = black;
                    w->color = red;
                    leftRotate(w);
                    w = parent->left;
                }
                
                w->color = parent->color;
                parent->color = black;
                if (w->left != nullptr)
                    w->left->color = black;
                rightRotate(parent);
                x = root; // To break the loop
            }
        }
    }
    
    if (x != nullptr)
        x->color = black;
}

// Remove a node with given data
void RedBlackTree::remove(int data)
{
    if (root == nullptr)
        return;
    
    Node *z = search(data);
    
    if (z == nullptr)
    {
        cout << "No node found to delete with value: " << data << endl;
        return;
    }
    
    Node *y = z;
    Node *x = nullptr;
    Node *xParent = nullptr;
    bool isLeft = false;
    Color yOriginalColor = y->color;
    
    if (z->left == nullptr)
    {
        x = z->right;
        xParent = z->parent;
        isLeft = (z->parent != nullptr && z == z->parent->left);
        rbTransplant(z, z->right);
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        xParent = z->parent;
        isLeft = (z->parent != nullptr && z == z->parent->left);
        rbTransplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        
        if (y->parent == z)
        {
            if (x != nullptr)
                x->parent = y;
            xParent = y;
            isLeft = false;
        }
        else
        {
            xParent = y->parent;
            isLeft = (y == y->parent->left);
            rbTransplant(y, y->right);
            y->right = z->right;
            if (y->right != nullptr)
                y->right->parent = y;
        }
        
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    delete z;
    
    if (yOriginalColor == black)
    {
        fixDeleteViolation(x, xParent, isLeft);
    }
}

// Search for a node with given data
Node* RedBlackTree::search(int data)
{
    Node *temp = root;
    
    while (temp != nullptr)
    {
        if (data < temp->data)
            temp = temp->left;
        else if (data > temp->data)
            temp = temp->right;
        else
            return temp;
    }
    
    return nullptr;
}

// Inorder traversal
void RedBlackTree::inorderHelper(Node *root)
{
    if (root == nullptr)
        return;
    
    inorderHelper(root->left);
    cout << root->data << "(" << (root->color == red ? "Red" : "Black") << ") ";
    inorderHelper(root->right);
}

void RedBlackTree::inorder()
{
    inorderHelper(root);
    cout << endl;
}

int main()
{
    RedBlackTree tree;
    
    // Example usage
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    
    cout << "Inorder traversal of the red-black tree: " << endl;
    tree.inorder();
    
    cout << "Removing 18, 11, 3" << endl;
    tree.remove(18);
    tree.remove(11);
    tree.remove(3);
    
    cout << "Inorder traversal after deletion: " << endl;
    tree.inorder();
    
    return 0;
}