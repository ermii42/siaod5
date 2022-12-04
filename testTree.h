//
// Created by user on 04.12.2022.
//

#ifndef INC_5_TESTTREE_H
#define INC_5_TESTTREE_H
#include "binaryTree.h"
#include "binaryFile.h"

void testTree(){
    SetConsoleOutputCP(CP_UTF8);

    string fnameBin;
    string fnameText;
    string country;
    product *record = new product();
    TREE tree;
    int key;
    string line;
    int code;
    int choice;
    int number;
    do {
        cout << "1) преобразование тестовых данных из текстового файла в двоичный файл" << endl;
        cout << "2) сохранение данных двоичного файла в текстовом" << endl;
        cout << "3) вывод всех записей двоичного файла" << endl;
        cout << "4) добавление записи в дерево по ее порядковому номеру в файле" << endl;
        cout << "5) добавление всех записей файла в дерево" << endl;
        cout << "6) вывод дерева" << endl;
        cout << "7) удаление записи с заданным значением ключа" << endl;

        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Введите имя текстового файла:";
                cin >> fnameText;
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                code = stringBinToText(fnameText, fnameBin);
                if (code == -1) cout << "Файл не открылся";
                break;
            case 2:
                cout << "Введите имя текстового файла:";
                cin >> fnameText;
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                code = stringTextToBin(fnameText, fnameBin);
                if (code == -1) cout << "Файл не открылся";
                break;
            case 3:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                code = out_bin_file(fnameBin);
                if (code == -1) cout << "Файл не открылся";
                break;
            case 4:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                cout << "Введите порядковый номер записи";
                cin >> number;
                code = FindRecord(fnameBin, number, *record);
                if (code == -1) cout << "Файл не открылся";
                else {
                    tree.insert(*record);
                    cout << record->name << '\t';
                    cout << record->code << '\t';
                    cout << record->factory << '\t';
                    cout << record->price << '\t';
                    cout << record->country;
                }
                break;
            case 5:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                number = 1;
                code = FindRecord(fnameBin, number, *record);
                while(code != -1 && number < getCount(fnameBin)){
                    tree.insert(*record);
                    number++;
                    code = FindRecord(fnameBin, number, *record);
                }
                if (code == -1 && number == 0) cout << "Файл не открылся";
                else{
                    tree.insert(*record);
                }
                break;
            case 6:
                tree.print();
                tree.Vyvod(tree.GetDuk(), 0);
                break;
            case 7:
                cout << "Введите ключ:";
                cin >> key;
                tree.remove(key);
                break;
            default:
                break;
        }

        cout << endl;
    } while (choice != -1);
    delete record;
};
#endif //INC_5_TESTTREE_H
