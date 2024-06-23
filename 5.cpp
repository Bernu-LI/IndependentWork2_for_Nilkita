#include <vector>
#include <iostream>

struct node {
    node(int v): value(v) {}
    int value;
    node* next = nullptr;
};


struct myStack {

    // Конструктор стека
    myStack(const std::vector <int>& array) {   // Принимает в качестве параметра ссылку на массив
        for (auto& i : array) {       // Проходится по каждому элементу массива и добавляет его в стек
            add(i);
        }
    }

    node* top = nullptr;    // Указатель на вершину стека

    // Метод(функция) добавления элемента
    void add(int number) {                      // Принимает в качестве параметра число, которое хотим добавить
        node* newEl = new node(number);      // Создаём новый элемент
        if (top == nullptr) {                   // Если указатель на вершину стека пуст, значит сам стек пуст, то:
            top = newEl;                          // привязываем элемент к top
        }
        else {                                  // Если указатель на вершину стека не пуст, то:
            newEl->next = top;                    // привязываем к новому элементу самый верхний элемент стека;
            top = newEl;                          // обновляем top, который теперь указывает на новый элемент
        }
    }
};


struct BST {

    // Вспомогательная структура приспособленных для дерева node'ов
    struct BST_node {
        BST_node(const node* const aNode): value(aNode->value) {} // Конструктор, принимает указатель на заранее созданный node
        int value;
        BST_node* parent = nullptr;     // Укзазатель на родителя
        BST_node* left = nullptr;       // Указаталь на левого ребёнка
        BST_node* right = nullptr;      // Указатель на правого ребёнка
    };

    // Конструктор дерева
    BST(const myStack& s1, const myStack& s2) {     // Принимает ссылки на два заранее созданных стека
        node* temp = s1.top;
        while (temp != nullptr) {                   // Проходится по каждому элементу первого стека и добавляет его в дерево
            insert(temp);
            temp = temp->next;
        }
        temp = s2.top;
        while (temp != nullptr) {                   // Проходится по каждому элементу второго стека и добавляет его в дерево
            insert(temp);
            temp = temp->next;
        }
    }

    BST_node* root = nullptr;                   // Указатель на корень дерева

    // Метод(функция) вставки элемента в дерево
    void insert(node* aNode) {                      // Принимает указатель на заранее созданный node, затем:
        BST_node* newEl = new BST_node(aNode);        // на основе этого node'a создаёт BST_node
        if (root == nullptr) {                      // Если корень дерева пуст, значит само дерево пустое
            root = newEl;
        }
        else {                                      // Если корень дерева не пуст, значит ищем подходящее пустое место,
            BST_node* temp = root;                    // куда можно вставить новый элемент, чтобы не нарушить свойства дерева
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

    // Конструктор очереди
    myQueue(const BST& myBST) {                     // Принимает заранее созданное дерево, затем:
        inOrderTraversalSort(myBST.root);       // запускает метод inorderTraversal
    }

    node* tail = nullptr;           // Указатель на хвост (самый последний элемент) очереди

    // Метод(функция) вставки
    void insert(BST::BST_node* el) {            // Принимает указатель на BST_node
        node* temp = new node(el->value);    // Создаёт node на основе значения, которое хранится в BST_node, который мы передали в эту функцию
        temp->next = nullptr;
        if (tail == nullptr) {                  // Если хвост пуст, значит сама очередь пуста
            tail = temp;
        }
        else {                                  // Если хвост не пуст, значит:
            temp->next = tail;                    // привязываем к новому элементу хвост,
            tail = temp;                          // обновляем хвост, который теперь указывает на новый элемент
        }
    }

    // Обход дерева в отсортированном порядке
    void inOrderTraversalSort(BST::BST_node* temp) {    // По сути всегда принимает в качестве параметра корень дерева
        if (temp != nullptr) {
            inOrderTraversalSort(temp->left);
            insert(temp);
            inOrderTraversalSort(temp->right);
        }
    }

    // Выводит элементы очереди от последнего к первому
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