#pragma once
#include "Node.hpp"

void action_printNode(Node* node);

class BinarySearchTree {
private:
    Node* root;
    void traverse_from(Node* node, void (*action)(Node* node));
public:
    BinarySearchTree();
    ~BinarySearchTree();

    // Query operations
    Node * search(int val) const;
    Node* min() const;
    Node* max() const;
    int depth() const;
    void print();

    // Update operations
    void insert(int key);
    void remove(int key);

    // Helper methods
    void rootTransplant(Node* old_root, Node* new_root);
};
