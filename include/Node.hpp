#pragma once

class Node {
private:
    int key;

public:
    Node* left;
    Node* right;
    Node* parent;

    Node(int key);
    int getKey() const;

    Node* predecessor();
    Node* successor();

    static void deleteNode(Node* node);

    int height();
    // The higher the height, the lower the depth in the tree
    // Height defines
    // the number of parents one has
    // to traverse through to get to the root node
    // Root has min height (0), and leaf nodes have max height

    int depth();
    // The higher the depth, the lower the height
    // Root has max depth, leaf nodes have min depth
};