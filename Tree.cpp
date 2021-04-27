
#include "Tree.h"

void Tree::init(Node *root) {
    this->root = root;
}

void Tree::putChild(Node *node, Node *parent) {
    parent->children.push_back(node);
    node->parent = parent;
}

void Tree::putChildren(vector<Node *> nodes, Node *parent) {
    for (int i = 0; i < nodes.size(); ++i) {
        putChild(nodes[i], parent);
    }
}

Node initNode(int lowerBound, int z, vector<int> weight,int index) {
    Node node;
    node.lowerBound = lowerBound;
    node.weight = weight;
    node.z=z;
    node.index=index;
    return node;
}

