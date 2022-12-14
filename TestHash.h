//
// Created by user on 30.10.2022.
//

#ifndef INC_3_TESTHASH_H
#define INC_3_TESTHASH_H

#include "Hash.h"

void testHash() {
    HeshTable T;
    T.createHeshTable();
    insertInHeshTable(123, "name1", "factory1", 1, "country1", 1, T);  // 9
    insertInHeshTable(12, "name2", "factory2", 2, "country2", 2, T);   //12
    insertInHeshTable(19, "name3", "factory3", 3, "country3", 3, T);   //0
    insertInHeshTable(9, "name4", "factory4", 4, "country4", 4, T);    //(9) 10 коллизия
    insertInHeshTable(28, "name5", "factory5", 5, "country5", 5, T);   //(9) 11 коллизия
    cout << "Table:\n";
    outTable(T);
    cout << endl;
    typeitem* r;

    int i = search(T, 9, r);

    if (i != -1) {
        cout << r->code << ' ' << r->name << endl;
    } else
        cout << "record is not" << '\n';


    i = deletedFromHeshTable(T, 28);
    if (i == 0)cout << "record is deleted\n";
    else
        cout << "record is not\n" << '\n';
    cout << "Table:\n";
    outTable(T);

    i = search(T, 9, r);
    if (i != -1) {
        cout << r->code << ' ' << r->name << endl;
    } else
        cout << "record is not" << '\n';
    i = search(T, 28, r);
    if (i != -1) {
        cout << r->code << ' ' << r->name << endl;
    } else
        cout << "record is not" << '\n';


    cout << "---------------------------------------------";
    // добиваюсь рехеширования 15 / 19 =0,789473684210526, что больше 0.75
    insertInHeshTable(1, "name6", "factory6", 6, "country6", 6, T);     // 1
    insertInHeshTable(2, "name7", "factory7", 7, "country7", 7, T);     //2
    insertInHeshTable(3, "name8", "factory8", 8, "country8", 8, T);     //3
    insertInHeshTable(4, "name9", "factory9", 9, "country9", 9, T);     //4
    insertInHeshTable(5, "name10", "factory10", 10, "country10", 10, T);     //5
    insertInHeshTable(6, "name11", "factory11", 11, "country11", 11, T);     // 6
    insertInHeshTable(7, "name12", "factory12", 12, "country12", 12, T);     //7
    insertInHeshTable(8, "name13", "factory13", 13, "country13", 13, T);     //8
    insertInHeshTable(10, "name14", "factory14", 14, "country14", 14, T);    //10 (тк мы удаляли элемент)
    insertInHeshTable(11, "name15", "factory15", 15, "country15", 15, T);   //(11) 13 коллизия
    insertInHeshTable(13, "name16", "factory16", 16, "country16", 16,
                      T);   //а здесь уже требуется рехеширование тк кол-во элементов достигло 15

    cout << "\nTable:\n";
    outTable(T);
}

#endif //INC_3_TESTHASH_H
