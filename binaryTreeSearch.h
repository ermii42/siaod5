//
// Created by user on 04.12.2022.
//

#ifndef INC_5_BINARYTREESEARCH_H
#define INC_5_BINARYTREESEARCH_H
#include "iostream"
#include "binaryFile.h"
using namespace std;

struct node2 {
    int key;
    product info;
    node2 *left = nullptr;
    node2 *right = nullptr;
    node2 *parent;
};

class TREE_SEARCH {
private:
    node2 *duk; //Корень дерева.
public:
    TREE_SEARCH() { duk = nullptr; }
    node2 **GetDuk() { return &duk; }

    void insert(product tInfo);    // Вставляем узел, ключ это значение ключа, внешний интерфейс
    int remove(int key); // Удалить ключевой узел
    node2 *search(int key, node2* root);
    void Vyvod(node2 **w, int l);
};

void TREE_SEARCH::insert(product tInfo) {
    node2 *t = new node2;
    t->key = tInfo.code;
    t->info = tInfo;
    if(duk == nullptr){
        duk = t;
        return;
    }
    node2* pointer = duk;
    while(pointer != nullptr){
        if(pointer->key >= t->key){
            if(pointer->left == nullptr){
                pointer->left = t;
                pointer->right->parent = pointer;
                return;
            }
            else{
                pointer = pointer->left;
            }
        }
        else{
            if(pointer->right == nullptr){
                pointer->right = t;
                pointer->right->parent = pointer;
                return;
            }
            else{
                pointer = pointer->right;
            }
        }
    }
}

int TREE_SEARCH::remove(int key) {
    node2 * curr = duk;
    node2 * parent = nullptr;
    while (curr && curr->key != key)
    {
        parent = curr;
        if (curr->key > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (!curr)
        return 0;
    if (curr->left == nullptr)
    {
        // Вместо curr подвешивается его правое поддерево
        if (parent && parent->left == curr)
            parent->left = curr->right;
        if (parent && parent->right == curr)
            parent->right = curr->right;
        delete curr;
        return 0;
    }
    if (curr->right == nullptr)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        delete curr;
        return 0;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    node2 * replace = curr->right;
    while (replace->left)
        replace = replace->left;
    int replace_value = replace->key;
    curr->key = replace_value;
}

node2 *TREE_SEARCH::search(int key, node2* root) {
    if (root == nullptr)
        return nullptr;
    if (key == root->key)
        return root;
    if (key < root->key)
        return search(key, root->left);
    if (key > root->key)
        return search(key, root->right);
}

void TREE_SEARCH::Vyvod(node2 **w, int l)
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
#endif //INC_5_BINARYTREESEARCH_H
