//
// Created by user on 30.10.2022.
//

#ifndef INC_3_TESTBINARY_H
#define INC_3_TESTBINARY_H
#include "Binary.h"
#include "windows.h"

void testBinary(){
    SetConsoleOutputCP(CP_UTF8);

    string fnameBin;
    string fnameText;
    string country;
    product* record = new product();
    int key;
    string line;
    int code;
    int choice;
    int number;
    do{
        cout<<"1) преобразование тестовых данных из текстового файла в двоичный файл"<<endl;
        cout<<"2) сохранение данных двоичного файла в текстовом"<<endl;
        cout<<"3) вывод всех записей двоичного файла"<<endl;
        cout<<"4) доступ к записи по ее порядковому номеру в файле"<<endl;
        cout<<"5) сформировать текстовый файл о поставках заданной страны"<<endl;
        cout<<"6) добавить новую запись о товаре в конец файла"<<endl;
        cout<<"7) удаление записи с заданным значением ключа"<<endl;

        cin >> choice;
        switch(choice){
            case 1:
                cout << "Введите имя текстового файла:";
                cin >> fnameText;
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                code = stringBinToText(fnameText, fnameBin);
                if(code==-1) cout<<"Файл не открылся";
                break;
            case 2:
                cout << "Введите имя текстового файла:";
                cin >> fnameText;
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                code = stringTextToBin(fnameText, fnameBin);
                if(code==-1) cout<<"Файл не открылся";
                break;
            case 3:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                code = out_bin_file(fnameBin);
                if(code==-1) cout<<"Файл не открылся";
                break;
            case 4:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                cout << "Введите порядковый номер записи";
                cin >> number;
                code = FindRecord(fnameBin, number, *record);
                if(code==-1) cout<<"Файл не открылся";
                else{
                    cout << record->name<<'\t';
                    cout << record->code<<'\t';
                    cout << record->factory<<'\t';
                    cout << record->price<<'\t';
                    cout << record->country;
                }
                break;
            case 5:
                cout << "Введите имя текстового файла:";
                cin >> fnameText;
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                cout<< "Введите страну-поставщика";
                cin>>country;
                code = CreateNewFileFrom(fnameBin, fnameText, country);
                if(code==-1) cout<<"Файл не открылся";
                break;
            case 6:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                cout << "Введите данные\n";
                code = AddToEndFile(fnameBin);
                if(code==-1) cout<<"Файл не открылся";
                break;
            case 7:
                cout << "Введите имя двоичного файла:";
                cin >> fnameBin;
                cout << "Введите ключ:";
                cin>>key;
                code = DelByKey(fnameBin, key);
                if(code==-1) cout<<"Файл не открылся";
                break;
            default:
                break;
        }

        cout<<endl;
    }while (choice!=-1);
    delete record;
}
#endif //INC_3_TESTBINARY_H
