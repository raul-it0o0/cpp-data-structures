#include "Node.hpp"
#include <algorithm>

Node::Node(int key) {
    this->key = key;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

int Node::getKey() const {
    return this->key;
}

Node* Node::predecessor() {
    Node* node = this;

    // If node has a left child
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
        Node* parentNode = node->parent;

        while (parentNode && (node == parentNode->left)) {
            node = parentNode;
            parentNode = parentNode->parent;
        }

        return parentNode;
    }
}

Node* Node::successor() {
    Node* node = this;

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
        // When you come from the left child, that is the successor (the parent of that child)
    else {
        Node* parentNode = node->parent;

        while (parentNode && (node == parentNode->right)) {
            node = parentNode;
            parentNode = parentNode->parent;
        }

        return parentNode;
    }
}

void Node::deleteNode(Node *node) {
    node->key = 0;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;

    delete node;
    node = nullptr;
}

int Node::height() {
    int height = 0;
    Node* iterator = this;

    while (iterator->parent) {
        iterator = iterator->parent;
        height++;
    }

    return height;
}

int Node::depth() {
    int depth = 0, leftDepth = 0, rightDepth = 0;

    if ((this->left) or (this->right))
        // if node has any children
        depth++;

    if (this->left)
        leftDepth = this->left->depth();
    if (this->right)
        rightDepth = this->right->depth();

    depth += std::max(leftDepth, rightDepth);

    return depth;
}