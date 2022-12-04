//
// Created by user on 04.12.2022.
//

#ifndef INC_5_BINARYTREE_H
#define INC_5_BINARYTREE_H
#include "iostream"
#include "binaryFile.h"
using namespace std;

struct node {
    int key;
    product info;
    string color;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
};

class TREE {
private:
    node *duk; //Корень дерева.
    void leftRotate(node* &root, node* x);// левая рука
    void rightRotate(node* &root, node* y);// правая рука
    void fixInsertion(node *&root, node *t);
    void removeFixUp(node* &root, node* t, node*parent);
    node* search(node*t, int key);
    void print(node* t);
public:
    TREE() { duk = nullptr; }

    node **GetDuk() { return &duk; }

    void insert(product tInfo);    // Вставляем узел, ключ это значение ключа, внешний интерфейс
    void remove(int key); // Удалить ключевой узел
    node *search(int key);

    void print();
    void Vyvod(node **w, int l);
};

void TREE::insert(product tInfo) {
    node *t = new node;
    t->key = tInfo.code;
    t->info = tInfo;
    t->color = "red";
    if (duk == nullptr) {
        duk = t;
    } else {
        node *p = duk;
        node *q = nullptr;
        while (p != nullptr) { // спускаемся вниз, пока не дойдем до подходящего листа
            q = p;
            if (p->key < t->key) {
                p = p->right;
            } else {
                p = p->left;
            }
        }
        t->parent = q;
        // добавляем новый элемент красного цвета
        if (q->key < t->key) {
            q->right = t;
        } else {
            q->left = t;
        }
    }
    fixInsertion(duk, t); // проверяем, не нарушены ли свойства красно-черного дерева
}

void TREE::fixInsertion(node *&root, node *t) {
    node *parent = t->parent;
    while (t != duk && parent->color == "red") {
        node *gparent = parent->parent;
        if (gparent->left == parent) {
            node *uncle = gparent->right;
            if (uncle != nullptr && uncle->color == "red") {
                parent->color = "black";
                uncle->color = "black";
                gparent->color = "red";
                t = gparent;
                parent = t->parent;
            } else {
                if (parent->right == t) {
                    leftRotate(root, parent);
                    swap(t, parent);
                }
                rightRotate(root, gparent);
                gparent->color = "red";
                parent->color = "black";
                break;
            }
        } else {
            node *uncle = gparent->left;
            if (uncle != nullptr && uncle->color == "red") {
                gparent->color = "red";
                parent->color = "black";
                uncle->color = "black";

                t = gparent;
                parent = t->parent;
            } else {
                if (parent->left == t) {
                    rightRotate(root, parent);
                    swap(parent, t);
                }
                leftRotate(root, gparent);
                parent->color = "black";
                gparent->color = "red";
                break;
            }
        }
    }
    root->color = "black";
}

void TREE::leftRotate(node *&root, node *x) {
    node*y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void TREE::rightRotate(node *&root, node *y) {
    node*x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else {
        if  (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void TREE::remove(int key) {
    node*deletenode = search(duk, key);
    if (deletenode == nullptr){
        return;
    }
    node *child, *parent;
    string color;
    // Левый и правый узлы удаленного узла не пусты (не конечные узлы)
    if (deletenode->left != nullptr && deletenode->right != nullptr)
    {
        node *replace = deletenode;
        // Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
        replace = deletenode->right;
        while (replace->left != nullptr)
        {
            replace = replace->left;
        }
        // Случай, когда удаленный узел не является корневым узлом
        if (deletenode->parent != nullptr)
        {
            if (deletenode->parent->left == deletenode)
                deletenode->parent->left = replace;
            else
                deletenode->parent->right = replace;
        }
            // Ситуация с корневым узлом
        else
            duk = replace;
        // child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
        // Поскольку замена является преемником, он не может иметь левого дочернего узла
        // Аналогично, у узла-предшественника не может быть правого дочернего узла
        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        // Удаленный узел является родительским узлом замещающего узла (repalce)
        if (parent == deletenode)
            parent = replace;
        else
        {
            // Существование дочернего узла
            if (child != nullptr)
                child->parent = parent;
            parent->left = child;

            replace->right = deletenode->right;
            deletenode->right->parent = replace;
        }
        replace->parent = deletenode->parent;
        replace->color = deletenode->color;
        replace->left = deletenode->left;
        deletenode->left->parent = replace;
        if (color == "black")
            removeFixUp(duk, child, parent);

        delete deletenode;
        return;
    }
    // Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
    if (deletenode->left != nullptr)
        child = deletenode->left;
    else
        child = deletenode->right;

    parent = deletenode->parent;
    color = deletenode->color;
    if (child)
    {
        child->parent = parent;
    }
    // Удаленный узел не является корневым узлом
    if (parent)
    {
        if (deletenode == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }
        // Удаленный узел является корневым узлом
    else
        duk = child;

    if (color == "black")
    {
        removeFixUp(duk, child, parent);
    }
    delete deletenode;
}

node *TREE::search(node *t, int key) {

    if (t == nullptr || t->key == key)
        return t;
    else
    if (key > t->key)
        return search(t->right, key);
    else
        return search(t->left, key);
}

void TREE::removeFixUp(node *&root, node *t, node *parent) {
    node*othernode;
    while ((!t) || t->color == "black" && t != duk)
    {
        if (parent->left == t)
        {
            othernode = parent->right;
            if (othernode->color == "red")
            {
                othernode->color = "black";
                parent->color = "red";
                leftRotate(root, parent);
                othernode = parent->right;
            }
            else
            {
                if (!(othernode->right) || othernode->right->color == "black")
                {
                    othernode->left->color="black";
                    othernode->color = "red";
                    rightRotate(root, othernode);
                    othernode = parent->right;
                }
                othernode->color = parent->color;
                parent->color = "black";
                othernode->right->color = "black";
                leftRotate(root, parent);
                t = root;
                break;
            }
        }
        else
        {
            othernode = parent->left;
            if (othernode->color == "red")
            {
                othernode->color = "black";
                parent->color = "red";
                rightRotate(root, parent);
                othernode = parent->left;
            }
            if ((!othernode->left || othernode->left->color == "black") && (!othernode->right || othernode->right->color == "black"))
            {
                othernode->color = "red";
                t = parent;
                parent = t->parent;
            }
            else
            {
                if (!(othernode->left) || othernode->left->color == "black")
                {
                    othernode->right->color = "black";
                    othernode->color = "red";
                    leftRotate(root, othernode);
                    othernode = parent->left;
                }
                othernode->color = parent->color;
                parent->color = "black";
                othernode->left->color = "black";
                rightRotate(root, parent);
                t = root;
                break;
            }
        }
    }
    if (t)
        t->color = "black";
}

node *TREE::search(int key) {
    return search(duk, key);
}

void TREE::print() {
    if (duk == nullptr)
        cout << "empty RBtree\n";
    else
        print(duk);
}

void TREE::print(node *t) {
    if (t == nullptr)
        return;
    if (t->parent == nullptr)
        cout << t->key << "(" << t->color << ") is root" << endl;
    else if(t->parent->left==t)
    {
        cout << t->key << "(" << t->color << ") is "<<t->parent->key<<"'s "<<"left child" << endl;
    }
    else
    {
        cout << t->key << "(" << t->color << ") is " << t->parent->key << "'s " << "right child" << endl;
    }
    print(t->left);
    print(t->right);
}

void TREE::Vyvod(node **w, int l)
// Изображение бинарного дерева, заданного
// указателем *w на экране дисплея.
{
    if (*w != nullptr) {
        Vyvod(&((**w).right), l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << (**w).key << endl;
        Vyvod(&((**w).left), l + 1);
    }
}
#endif //INC_5_BINARYTREE_H
