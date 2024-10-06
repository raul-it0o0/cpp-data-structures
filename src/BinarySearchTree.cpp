#include "BinarySearchTree.hpp"
#include "Node.hpp"
#include <iostream>

BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    traverse_from(this->root, Node::deleteNode);
}

Node * BinarySearchTree::search(int val) const {
    Node* iterator = this->root;

    while (iterator && (iterator->getKey() != val)) {
        if (val < iterator->getKey())
            iterator = iterator->left;
        else
            iterator = iterator->right;
    }

    return iterator;

}

Node* BinarySearchTree::min() const {
    Node* iterator = this->root;

    while (iterator->left)
        iterator = iterator->left;

    return iterator;
}

Node* BinarySearchTree::max() const {
    Node* iterator = this->root;

    while (iterator->right)
        iterator = iterator->right;

    return iterator;
}

int BinarySearchTree::depth() const {
    return this->root->depth();
}

void BinarySearchTree::print() {
    this->traverse_from(this->root, action_printNode);
    std::cout << std::endl;
}

/*
Node* BinarySearchTree::predecessor(int key) const {
    Node* node = this->search(key);

    if (!node)
        return nullptr;
    // key not found

    // If node has a left child,
    // Go left once, then go right as much as you can
    if (node->left) {
        node = node->left;

        while (node->right)
            node = node->right;

        return node;
    }

    // If node does not have a left child,
    // Keep going up, ensuring you are coming up from the left child
    // When you come from the right child, that is the successor (the parent of that child)
    else {
        Node* parent = node->parent;

        // while there is a parent, and I am coming from the left child
        while (parent && (node == parent->left)) {
            node = parent;
            parent = parent->parent;
        }

        return parent;
    }
}

Node* BinarySearchTree::successor(int key) const {
    Node *node = this->search(key);

    if (!node)
        return nullptr;
    // key not found

    // If node has a right child,
    // Go right once, then go left as much as you can
    if (node->right) {
        node = node->right;

        while (node->left)
            node = node->left;

        return node;
    }

    // If node does not have a right child,
    // Keep going up, ensuring you are coming up from the right child
    // When you come from the left child, that is the successor (the parent of the child)
    else {
        Node* parent = node->parent;

        while (parent && (node == parent->right)) {
            node = parent;
            parent = parent->parent;
        }

        return parent;
    }
}
 */

void BinarySearchTree::insert(int key) {

    Node* node = new Node(key);

    // If tree is empty
    if (!this->root) {
        this->root = node;
        return;
    }

    Node* iterator = this->root;
    Node* iteratorParent = nullptr;

    // Move node to its final position in the tree
    while (iterator) {
        iteratorParent = iterator;

        if (node->getKey() < iterator->getKey())
            // Move left
            iterator = iterator->left;
        else if (node->getKey() > iterator->getKey())
            // Move right
            iterator = iterator->right;
        else
            // Keys are equal which is not allowed in a tree
            return;
    }

    // Link pointers
    node->parent = iteratorParent;

    // Have the parent point to its new child
    if (node->getKey() < iteratorParent->getKey())
        iteratorParent->left = node;
    else
        iteratorParent->right = node;

}

void BinarySearchTree::remove(int key) {

    Node* node = this->search(key);

    if (!node)
        // Return if null
        return;

    // Check how many children node has
    if (!node->left)
        // only right child or none
        // new subtree will be rooted at right child (which can be null)
        rootTransplant(node, node->right);

    else if (!node->right)
        // only left child or none
        // new subtree will be rooted at left child (which can be null)
        rootTransplant(node, node->left);

    else {
        // node has both children

        // find successor of node
        Node* successor = node->successor();

        if (successor != node->right) {
            // if successor is not the direct right child of node
            // new subtree rooted at the successor
            // becomes rooted at successor's right child (can be null)
            rootTransplant(successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }

        rootTransplant(node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
    }

    Node::deleteNode(node);

}

void BinarySearchTree::rootTransplant(Node* oldRoot, Node* newRoot) {
    // 1. Have the parent of old root point to its new child (newRoot)
    // Check if oldRoot is the root of the whole tree
    if (!oldRoot->parent)
        this->root = newRoot;

    // Check which child of the parent is oldRoot and have the parent point to its new child
    else if (oldRoot->parent->left == oldRoot)
        oldRoot->parent->left = newRoot;
    else if (oldRoot->parent->right == oldRoot)
        oldRoot->parent->right = newRoot;

    // 2. Have newRoot point to its new parent
    // This can only happen if newRoot is not null (which can be the case)
    if (newRoot)
        newRoot->parent = oldRoot->parent;

}

void action_printNode(Node* node) {
    std::cout << node->getKey() << " " << std::flush;
}

void BinarySearchTree::traverse_from(Node* node, void (*action)(Node* node)) {
    if (!node)
        return;

    traverse_from(node->left, action);

    Node* rightTemp = node->right;

    action(node);

    traverse_from(rightTemp, action);

}


