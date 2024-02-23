#include <vector>

struct BST {

    struct BST_node {
        BST_node(int v): value(v) {}
        int value;
        BST_node* left = nullptr;
        BST_node* right = nullptr;
    };

    BST_node* root = nullptr;

    BST_node* insert(BST_node* temp, int number) {
        if (temp == nullptr) {
            return new BST_node(number);
        }
        else if (number < temp->value) {
            temp->left = insert(temp->left, number);
        }
        else {
            temp->right = insert(temp->right, number);
        }
        return temp;
    }

    BST_node* isExisting(BST_node* temp, int number) const {
        if (temp == nullptr or temp->value == number) {
            return temp;
        }
        if (number < temp->value) {
            return isExisting(temp->left, number);
        }
        else {
            return isExisting(temp->right, number);
        }
    }
};


struct myQueue {

    myQueue(std::vector <int> array) {
        for (auto& i : array) {
            insert(i);
        }
    }

    myQueue() = default;

    struct node {
        node(int v): value(v) {}
        int value;
        node* next = nullptr;
    };

    node* tail = nullptr;
    node* head = nullptr;

    void insert(int number) {
        node* temp = new node(number);
        if (head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {
            temp->next = tail;
            tail = temp;
        }
    }

    void auxiliary_function_with(node* temp) {
        if (temp != nullptr) {
            auxiliary_function_with(temp->next);
            insert(temp->value);
        }
    }

    myQueue& union_with_repetition(const myQueue& aQueue) const {
        myQueue newQueue;
        newQueue.auxiliary_function_with(tail);
        newQueue.auxiliary_function_with(aQueue.tail);
        return newQueue;
    }

    myQueue& union_without_repetition(const myQueue& aQueue) const {
        myQueue newQueue;
        BST newBST;
        node *temp = tail;
        while (temp != nullptr) {
            if (newBST.isExisting(newBST.root, temp->value) == nullptr) {
                newQueue.insert(temp->value);
                newBST.root = newBST.insert(newBST.root, temp->value);
            }
            temp = temp->next;
        }
        temp = aQueue.tail;
        while (temp != nullptr) {
            if (newBST.isExisting(newBST.root, temp->value) == nullptr) {
                newQueue.insert(temp->value);
                newBST.root = newBST.insert(newBST.root, temp->value);
            }
            temp = temp->next;
        }
        return newQueue;
    }
};


int main() {
    myQueue q1({1, 2, 3, 4, 5});
    myQueue q2({5, 6, 7, 8, 9, 10});
    myQueue q3 = q1.union_with_repetition(q2);
    myQueue q4 = q1.union_without_repetition(q2);
    return 0;
}