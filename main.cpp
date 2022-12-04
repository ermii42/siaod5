#include <iostream>
#include "binaryTree.h"
#include "windows.h"
#include<vector>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> nums{ 10,40,30,60,90,70,20,50,80,100};
    TREE tree;
    for (auto num : nums)
        tree.insert(num);
    cout << endl;
    cout << "Найти узел с ключом 30: \n";
    cout << endl<<tree.search(30)->key<<endl;
    cout << "Удалить узел с ключом 100 \n";
    tree.remove(100);
    //tree.preOrder();
    cout << endl;
    cout << "\nКрасные и черные детали дерева: \n";
    tree.print();
    tree.Vyvod(tree.GetDuk(), 0);
    cin.get();
    return 0;
}
