#include <bits/stdc++.h>
using namespace std;

class AVL {
    struct Node {
        int value;
        Node *leftChild, *rightChild;
        int nodeHeight, nodeSize;
        Node(int v) : value(v), leftChild(NULL), rightChild(NULL), nodeHeight(1), nodeSize(1) {}
    };

    Node *rootNode;

    int getNodeHeight(Node *n) {
        return n ? n->nodeHeight : 0;
    }

    int getNodeSize(Node *n) {
        return n ? n->nodeSize : 0;
    }

    int getBalanceFactor(Node *n) {
        return getNodeHeight(n->leftChild) - getNodeHeight(n->rightChild);
    }

    void updateNode(Node *n) {
        if (n) {
            n->nodeHeight = 1 + max(getNodeHeight(n->leftChild), getNodeHeight(n->rightChild));
            n->nodeSize = 1 + getNodeSize(n->leftChild) + getNodeSize(n->rightChild);
        }
    }

    Node* rightRotate(Node *y) {
        Node *x = y->leftChild;
        Node *T2 = x->rightChild;
        x->rightChild = y;
        y->leftChild = T2;
        updateNode(y);
        updateNode(x);
        return x;
    }

    Node* leftRotate(Node *x) {
        Node *y = x->rightChild;
        Node *T2 = y->leftChild;
        y->leftChild = x;
        x->rightChild = T2;
        updateNode(x);
        updateNode(y);
        return y;
    }

    Node* balanceTree(Node *n) {
        updateNode(n);
        if (getBalanceFactor(n) > 1) {
            if (getBalanceFactor(n->leftChild) < 0) {
                n->leftChild = leftRotate(n->leftChild);
            }
            return rightRotate(n);
        }
        if (getBalanceFactor(n) < -1) {
            if (getBalanceFactor(n->rightChild) > 0) {
                n->rightChild = rightRotate(n->rightChild);
            }
            return leftRotate(n);
        }
        return n;
    }

    Node* insertNode(Node *n, int key) {
        if (!n) return new Node(key);
        if (key < n->value) n->leftChild = insertNode(n->leftChild, key);
        else if (key > n->value) n->rightChild = insertNode(n->rightChild, key);
        else return n;  // No duplicates allowed
        return balanceTree(n);
    }

    Node* findMinNode(Node *n) {
        Node *current = n;
        while (current->leftChild) current = current->leftChild;
        return current;
    }

    Node* removeNode(Node *n, int key) {
        if (!n) return n;
        if (key < n->value) n->leftChild = removeNode(n->leftChild, key);
        else if (key > n->value) n->rightChild = removeNode(n->rightChild, key);
        else {
            if (!n->leftChild || !n->rightChild) {
                Node *temp = n->leftChild ? n->leftChild : n->rightChild;
                if (!temp) {
                    temp = n;
                    n = NULL;
                } else *n = *temp;
                delete temp;
            } else {
                Node *temp = findMinNode(n->rightChild);
                n->value = temp->value;
                n->rightChild = removeNode(n->rightChild, temp->value);
            }
        }
        if (!n) return n;
        return balanceTree(n);
    }

    bool searchNode(Node *n, int key) {
        if (!n) return false;
        if (key < n->value) return searchNode(n->leftChild, key);
        if (key > n->value) return searchNode(n->rightChild, key);
        return true;
    }

    int rankOfKey(Node *n, int key) {
        if (!n) return 0;
        if (key < n->value) return rankOfKey(n->leftChild, key);
        if (key > n->value) return 1 + getNodeSize(n->leftChild) + rankOfKey(n->rightChild, key);
        return getNodeSize(n->leftChild);
    }

    Node* selectByOrder(Node *n, int k) {
        if (!n) return NULL;
        int leftSize = getNodeSize(n->leftChild);
        if (k < leftSize) return selectByOrder(n->leftChild, k);
        if (k > leftSize) return selectByOrder(n->rightChild, k - leftSize - 1);
        return n;
    }

    void inOrderTraversal(Node *n) {
        if (!n) return;
        inOrderTraversal(n->leftChild);
        cout << n->value << " ";
        inOrderTraversal(n->rightChild);
    }

    void preOrderTraversal(Node *n) {
        if (!n) return;
        cout << n->value << " ";
        preOrderTraversal(n->leftChild);
        preOrderTraversal(n->rightChild);
    }

    void postOrderTraversal(Node *n) {
        if (!n) return;
        postOrderTraversal(n->leftChild);
        postOrderTraversal(n->rightChild);
        cout << n->value << " ";
    }

public:
    AVL() : rootNode(NULL) {}

    bool search(int key) {
        return searchNode(rootNode, key);
    }

    void add(int key) {
        rootNode = insertNode(rootNode, key);
    }

    void remove(int key) {
        rootNode = removeNode(rootNode, key);
    }

    int rank(int key) {
        return rankOfKey(rootNode, key);
    }

    int select(int k) {
        Node *n = selectByOrder(rootNode, k);
        return n ? n->value : -1;
    }

    void displayInOrder() {
        inOrderTraversal(rootNode);
        cout << endl;
    }

    void displayPreOrder() {
        preOrderTraversal(rootNode);
        cout << endl;
    }

    void displayPostOrder() {
        postOrderTraversal(rootNode);
        cout << endl;
    }
};

int main() {
    AVL tree;
    tree.add(10);
    tree.add(20);
    tree.add(30);
    cout << tree.search(10) << endl;  // 1
    cout << tree.search(25) << endl;  // 0
    cout << tree.rank(25) << endl;  // 2
    cout << tree.select(1) << endl;  // 20
    tree.remove(10);
    cout << tree.search(10) << endl;  // 0
    tree.displayInOrder();  // 20 30
    tree.displayPreOrder();  // 20 30
    tree.displayPostOrder();  // 30 20
    return 0;
}
