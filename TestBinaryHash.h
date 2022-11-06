//
// Created by user on 31.10.2022.
//

#ifndef INC_3_TESTBINARYHASH_H
#define INC_3_TESTBINARYHASH_H
#include "Bin_Hash.h"
#include "windows.h"

void testBinaryHash(){
    SetConsoleOutputCP(CP_UTF8);

    HeshTable T;
    T.createHeshTable();
    string fnameBin;
    string fnameText;
    string country;
    product* record = new product();
    int key;
    string line;

    int choice;
    int number;
    int errorcode;
    do{
        cout<<"1) Прочитать запись из файла и вставить элемент в таблицу\n";
        cout<<"2) Удалить запись из таблицы при заданном значении ключа и соответственно из файла\n";
        cout<<"3) Найти запись в файле по значению ключа \n";
        cout<<"4) Вывести хеш-таблицу \n";
        cout<<"5) Вывести файл \n";
        cin >> choice;
        switch(choice){
            case 1:
                cout<<"Введите имя файла и номер записи:";
                cin >> fnameBin >> number;
                errorcode=readAndInsertInHashTable(number, fnameBin, T);
                if(errorcode==-1) cout<<"Error";
                break;
            case 2:
                cout<<"Введите имя файла и ключ:";
                cin >> fnameBin >> key;
                errorcode = deleteRecord(key, fnameBin, T);
                if(errorcode==-1) cout<<"Error";
                break;
            case 3:
                cout<<"Введите имя файла и ключ:";
                cin >> fnameBin >> key;
                errorcode = FindByKey(key, fnameBin, T, *record);
                if(errorcode==-1) cout<<"Error";
                else {
                    cout << record->name<<'\t';
                    cout << record->code<<'\t';
                    cout << record->factory<<'\t';
                    cout << record->price<<'\t';
                    cout << record->country;
                    cout << endl;
                }
                break;
            case 4:
                outTable(T);
                break;
            case 5:
                cout<<"Введите имя файла:";
                cin>>fnameBin;
                errorcode= out_bin_file(fnameBin);
                if(errorcode==-1) cout<<"Error";
                break;
            default:
                break;
        }
    }
    while(choice != -1);
};

#endif //INC_3_TESTBINARYHASH_H
