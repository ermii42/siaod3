// Цепное хеширование

#ifndef INC_3_HASH_H
#define INC_3_HASH_H

const int c = 1; //c – константа, определяющая шаг перебора, линейного пробирования
const int size2 = 5;

#include <iostream>
using namespace std;

// структура записи
struct typeitem {
    int code=0;      // ключ записи - артикул, шестиразрядное число
    string name="-"; // название
    string factory="-"; // завод изготовитель
    int price = 0; // цена
    string country = "-"; // страна (название)

    //string adress="-"; //адрес по постановке задачи

    bool openORclose=true;     //свободна ли ячейка
    bool deletedORnot=false;    //не удалялась ли ячейка

};

// структура хеш-таблицы
struct HeshTable {
    int L = 19;
    typeitem **T;// таблица, динимачиский массив из объектов по постановке задачи
    int insertedcount;//количество вставленных ключей
    int deletedcount; //количество удаленных ключей
    void createHeshTable() {
        T = new typeitem*[L];
        for (int i=0; i<L; i++){
            T[i] = new typeitem[size2];
        }
        insertedcount = 0;
        deletedcount=0;
    }
    void Resize(int newL){  //увеличение размера таблицы
        for (int i=0; i<L; i++){
            delete[] T[i];
        }
        delete[] T;

        L = newL;

        T = new typeitem*[L];
        for (int i=0; i<L; i++){
            T[i] = new typeitem[size2];
        }
    }
    void Delete(){
        for (int i=0; i<L; i++){
            delete[] T[i];
        }
        delete[] T;
    }
};

//хеш-функция
int hesh(int code, int L) {
    return code % L;
}

//вставка с рехешированием
int insertInHeshTable(int code, string name, string factory, int price, string country, HeshTable& t) {

    // рехеширование
    if(float(t.insertedcount) / t.L >= 0.75){ // коэффициент нагрузки
        HeshTable T2;   // создание новой таблицы и увеличивание ее размера в сравнении с предыдущей вдвое
        T2.createHeshTable();
        T2.Resize(t.L*2);

        // заполнение новой таблицы старыми значениями с учетом нового значения размера (рехеширую)
        for(int i=0; i<t.L; i++){
            for(int j=0; j<size2; j++){
                // добавляю только непустые неудаленные элементы
                if(t.T[i][j].openORclose == false && t.T[i][j].deletedORnot==false){
                    insertInHeshTable(t.T[i][j].code, t.T[i][j].name, t.T[i][j].factory,
                                      t.T[i][j].price, t.T[i][j].country, T2);
                }
            }
        }
        // добавление нового элемента в расширенную таблицу
        insertInHeshTable(code, name, factory, price, country, T2);
        // увеличивание и изменение исходной таблицы
        t.Resize(T2.L);
        swap(T2, t);
        T2.Delete();
        return 0;
    }

    int i = hesh(code, t.L);
    int j=0;
    //разрешение коллизии
    while (j<size2 && t.T[i][j].openORclose == false)
        j += c;
    if (i < t.L)
    {
        t.T[i][j].code = code; t.T[i][j].name = name; t.T[i][j].factory=factory;
        t.T[i][j].price=price; t.T[i][j].country=country;
        t.T[i][j].openORclose = false;
        t.insertedcount++;
        return 0;
    }
    else
        return 1;
}

// вывод хеш-таблицы
void outTable(HeshTable& t) {
    for (int i = 0; i < t.L; i++) {
        for (int j = 0; j < size2; j++) {
            if(t.T[i][j].openORclose == 1 && j>0) break;
            cout << i << '\t' << t.T[i][j].code << "\t" << t.T[i][j].name << "\t" << t.T[i][j].factory<<"\t"
            << t.T[i][j].price << "\t" << t.T[i][j].country << "\t" << t.T[i][j].openORclose << "  "
            << t.T[i][j].deletedORnot << '\n';
        }
    }
}

// поиск
int* search(HeshTable& t, int code) {
    int i = hesh(code, t.L);
    //ищем по кластеру
    int j=0;
    int* result = new int[2];
    result[0]=-1;
    result[1]=-1;

    while (j < size2 && ((t.T[i][j].openORclose == false && t.T[i][j].deletedORnot==false)
                       || (t.T[i][j].openORclose == true && t.T[i][j].deletedORnot == true))
           && t.T[i][j].code != code)
        j++;
    if (not (t.T[i][j].openORclose == true && t.T[i][j].deletedORnot == false)) {
        result[0] = i;
        result[1] = j;
    }
    return result;
}

//удаление
int deletedFromHeshTable(HeshTable& t, int code) {
    int* coor;
    coor = search(t, code);
    int i = coor[0], j = coor[1];
    if (i == -1) return 1;//нет такой записи в таблице
    t.T[i][j].deletedORnot = true;
    t.T[i][j].openORclose = true;
    t.deletedcount++;
    return 0;
}


#endif //INC_3_HASH_H
