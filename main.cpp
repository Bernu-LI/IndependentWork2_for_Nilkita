#include <vector>
#include <iostream>

struct node {
    node(int v): value(v) {}
    int value;
    node* next = nullptr;
};


struct myStack {

    myStack(const std::vector <int>& array) {
        for (auto& i : array) {
            add(i);
        }
    }

    node* top = nullptr;

    void add(int number) {
        node* newEl = new node(number);
        if (top == nullptr) {
            top = newEl;
        }
        else {
            newEl->next = top;
            top = newEl;
        }
    }
};

struct BST {

    struct BST_node {
        BST_node(const node* const aNode): value(aNode->value) {}
        int value;
        BST_node* parent = nullptr;
        BST_node* left = nullptr;
        BST_node* right = nullptr;
    };

    BST(const myStack& s1, const myStack& s2) {
        node* temp = s1.top;
        while (temp != nullptr) {
            insert(temp);
            temp = temp->next;
        }
        temp = s2.top;
        while (temp != nullptr) {
            insert(temp);
            temp = temp->next;
        }
    }

    BST_node* root = nullptr;

    void insert(node* aNode) {
        BST_node* newEl = new BST_node(aNode);
        if (root == nullptr) {
            root = newEl;
        }
        else {
            BST_node* temp = root;
            while (true) {
                if (newEl->value < temp->value) {
                    if (temp->left == nullptr) {
                        temp->left = newEl;
                        newEl->parent = temp;
                        break;
                    }
                    temp = temp->left;
                }
                else {
                    if (temp->right == nullptr) {
                        temp->right = newEl;
                        newEl->parent = temp;
                        break;
                    }
                    temp = temp->right;
                }
            }
        }
    }

};

struct myQueue {

    myQueue(const BST& myBST) {
        inOrderTraversalSort(myBST.root);
    }

    node* tail = nullptr;

    void insert(BST::BST_node* el) {
        node* temp = new node(el->value);
        temp->next = nullptr;
        if (tail == nullptr) {
            tail = temp;
        }
        else {
            temp->next = tail;
            tail = temp;
        }
    }

    void inOrderTraversalSort(BST::BST_node* temp) {
        if (temp != nullptr) {
            inOrderTraversalSort(temp->left);
            insert(temp);
            inOrderTraversalSort(temp->right);
        }
    }

    void print(node* temp) {
        if (temp != nullptr) {
            print(temp->next);
            std::cout << temp->value << " ";
        }
    }

};


int main() {
    myStack s1({1, 2, 3, 4, 5});
    myStack s2({5, 6, 7, 8, 9, 10});
    BST myBST1(s1, s2);
    myQueue q1(myBST1);
    q1.print(q1.tail);
    return 0;
}