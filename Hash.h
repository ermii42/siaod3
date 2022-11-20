// Цепное хеширование

#ifndef INC_3_HASH_H
#define INC_3_HASH_H

const int c = 1; //c – константа, определяющая шаг перебора, линейного пробирования

#include <iostream>
using namespace std;
#include <list>

// структура записи
struct typeitem {
    int code=0;                 // ключ записи - артикул, шестиразрядное число
    string name="-";            // название
    string factory="-";         // завод изготовитель
    int price = 0;              // цена
    string country = "-";       // страна (название)
    int record_number;          // порядковый номер записи

    typeitem *next = nullptr;   // указатель на следующую запись с таким же ключом
    bool openORclose=true;      // свободна ли ячейка
    bool deletedORnot=false;    // не удалялась ли ячейка

};

// структура хеш-таблицы
struct HeshTable {
    int L = 19;
    typeitem *T;// таблица, динимачиский массив из объектов по постановке задачи
    int insertedcount;//количество вставленных ключей
    int deletedcount; //количество удаленных ключей
    void createHeshTable() {
        T = new typeitem[L];
        insertedcount = 0;
        deletedcount=0;
    }
    void Resize(int newL){  //увеличение размера таблицы
        delete[] T;
        L = newL;
        T = new typeitem[L];
    }
    void Delete(){
        delete[] T;
    }
};

//хеш-функция
int hesh(int code, int L) {
    return code % L;
}

//вставка с рехешированием
int insertInHeshTable(int code, string name, string factory, int price, string country, int record_number, HeshTable& t) {

    // рехеширование
    if(float(t.insertedcount) / t.L >= 0.75){ // коэффициент нагрузки
        HeshTable T2;   // создание новой таблицы и увеличивание ее размера в сравнении с предыдущей вдвое
        T2.createHeshTable();
        T2.Resize(t.L*2);
        typeitem *nxt;
        // заполнение новой таблицы старыми значениями с учетом нового значения размера (рехеширую)
        for(int i=0; i<t.L; i++){
            nxt = &(t.T[i]);
            while(nxt != nullptr){
                // добавляю только непустые неудаленные элементы
                if(nxt->openORclose == false && nxt->deletedORnot==false){
                    insertInHeshTable(nxt->code, nxt->name, nxt->factory,
                                      nxt->price, nxt->country, nxt->record_number, T2);
                }
                nxt = nxt->next;
            }
        }
        // добавление нового элемента в расширенную таблицу
        insertInHeshTable(code, name, factory, price, country, record_number, T2);
        // увеличивание и изменение исходной таблицы
        t.Resize(T2.L);
        swap(T2, t);
        T2.Delete();
        return 0;
    }

    int i = hesh(code, t.L);
    typeitem *nxt = &(t.T[i]);
    //разрешение коллизии
    if(nxt->next == nullptr && nxt->openORclose == true){
        nxt->code=code; nxt->name=name; nxt->country=country;
        nxt->factory=factory; nxt->price=price; nxt->record_number=record_number;
        nxt->openORclose=false;
        return 0;
    }
    while (nxt->next != nullptr)
        nxt = nxt->next;
    if (i < t.L)
    {
        typeitem* newElem = new typeitem();

        newElem->code = code; newElem->name = name; newElem->factory=factory;
        newElem->price=price; newElem->country=country; newElem->record_number = record_number;
        newElem->openORclose = false;
        nxt->next=newElem;
        t.insertedcount++;
        return 0;
    }
    else
        return -1;
}

// вывод хеш-таблицы
void outTable(HeshTable& t) {
    typeitem *nxt;
    for (int i = 0; i < t.L; i++) {
        nxt = &(t.T[i]);
        while(nxt!= nullptr) {
            cout << i << '\t' << nxt->code << "\t" << nxt->name << "\t" << nxt->factory<<"\t"
            << nxt->price << "\t" << nxt->country << "\t" << nxt->openORclose << "  "
            << nxt->deletedORnot << '\n';
            nxt = nxt->next;
        }
    }
}

// поиск
int search(HeshTable& t, int code) {
    int i = hesh(code, t.L);
    //ищем по кластеру
    int result;
    typeitem *nxt;
    nxt = &(t.T[i]);

    while (nxt!= nullptr && ((nxt->openORclose == false && nxt->deletedORnot==false)
                       || (nxt->openORclose == true && nxt->deletedORnot == true))
           && nxt->code != code)
        nxt =nxt->next;
    if (not (nxt->openORclose == true && nxt->deletedORnot == false)) {
        result = i;
    }
    return result;
}

//удаление
int deletedFromHeshTable(HeshTable& t, int code) {
    int i;
    i = search(t, code);
    if (i == -1) return 1;//нет такой записи в таблице
    t.T[i].deletedORnot = true;
    t.T[i].openORclose = true;
    t.deletedcount++;
    return 0;
}


#endif //INC_3_HASH_H
