
#include <vector>

using namespace std;
#ifndef BINPACKING_BNB_TREE_H
#define BINPACKING_BNB_TREE_H

 struct Node {
    int lowerBound;
    int z;
    int index;
    vector<int> weight;
    vector<Node *> children;
    Node *parent;
};

class Tree {
private:
    Node *root;
public:
    void init(Node *root);

    void putChild(Node *node, Node *parent);

    void putChildren(vector<Node *> nodes, Node *parent);

};

Node initNode(int lowerBound, int z, vector<int> weight,int index);

#endif //BINPACKING_BNB_TREE_H
