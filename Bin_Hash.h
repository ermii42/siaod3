//
// Created by user on 20.10.2022.
//

#ifndef INC_3_BIN_HASH_H
#define INC_3_BIN_HASH_H
#include "Binary.h"
#include "Hash.h"

// Прочитать запись из файла и вставить элемент в таблицу
int readAndInsertInHashTable(int number, string filename, HeshTable& t){
    product* record = new product();
    int errorCode;
    errorCode=FindRecord(filename, number, *record);
    if(errorCode == -1) return -1;
    // insertInHeshTable(int code, string name, string factory, int price, string country, HeshTable& t)
    errorCode = insertInHeshTable(record->code, record->name, record->factory,
                                  record->price, record->country, number, t);
    if(errorCode == -1) return -1;
    return 0;
}

// Удалить запись из таблицы при заданном значении ключа и
//соответственно из файла
int deleteRecord(int key, string filename, HeshTable& t){
    int errorCode;
    errorCode=DelByKey(filename, key);
    if(errorCode == -1) return -1;
    errorCode=deletedFromHeshTable(t,key);
    if(errorCode == -1) return -1;
    return 0;
}
//Найти запись в файле по значению ключа (найти ключ в хеш-таблице,
//получить номер записи с этим ключом в файле, выполнить прямой доступ
//к записи по ее номеру)..

int FindByKey(int key, string fileName, HeshTable& t, product& result){
    int errorCode;
    int* coor;
    coor = search(t, key);
    int i=coor[0], j=coor[1];
    int n = t.T[i][j].record_number;
    errorCode = FindRecord(fileName, n, result);
    return errorCode;
}

//???????????????
#endif //INC_3_BIN_HASH_H
