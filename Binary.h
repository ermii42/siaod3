
#ifndef INC_3_BINARY_H
#define INC_3_BINARY_H
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct product{
    int code;
    char name[20];
    char factory[20];
    char price[20];
    char country[20];
};

int stringBinToText(string fileName, string newfileName) /** из текстового в двоичный */
{
    ifstream ft(fileName);
    ofstream fb(newfileName, ios::binary | ios::out);
    if(!ft) return -1;
    if(!fb) return -1;
    product x;
    while (!ft.eof())
    {
        ft >> x.name;	//заполнение Х
        ft >> x.code;
        ft >> x.factory;
        ft >> x.price;
        ft >> x.country;

        fb.write((char *)&x, sizeof(product));
    }
    ft.close();
    fb.close();
    return 0;
}

int stringTextToBin(string fileName, string newfileName) /** из двоичного в текстовый */
{
    ifstream input(fileName, std::ios::binary | std::ios::in);
    ofstream output(newfileName);
    if(!input) return -1;
    if(!output) return -1;
    product x;

    //чтение из файла всей записи
    input.read((char *)&x, sizeof(product));
    output << x.name <<' '<<x.code<<' '<<x.factory<<' '<<x.price<<' '<<x.country;
    while (!input.eof())
    {
        output << endl;
        input.read((char *)&x, sizeof(product));
        output << x.name <<' '<<x.code<<' '<<x.factory<<' '<<x.price<<' '<<x.country;
    }
    input.close();
    output.close();
    return 0;
}

//вывод записей двоичного файла
int out_bin_file(string filename)
{
    fstream fb(filename, ios::out | ios::in | ios::binary);
    if(!fb) return -1;

    product x;
    //чтение из файла всей записи
    fb.read((char *)&x, sizeof(product));
    while (!fb.eof())
    {
        cout << x.name<<'\t';
        cout << x.code<<'\t';
        cout << x.factory<<'\t';
        cout << x.price<<'\t';
        cout << x.country;
        fb.read((char *)&x, sizeof(product));
        cout<<endl;
    }
    fb.close();
    return 0;
}

int FindRecord(string filename, int n){
    product x;
    ifstream file(filename, ios::out | ios::in | ios::binary);
    if(!file) return -1;
    file.seekg(sizeof(product)*(n-1), ios::beg);
    if(file.bad()) return -1;
    file.read((char *)&x, sizeof(product));
    cout << x.name<<'\t';
    cout << x.code<<'\t';
    cout << x.factory<<'\t';
    cout << x.price<<'\t';
    cout << x.country;
    file.close();
    return 0;
}

// создание новго файла из исходного
int CreateNewFileFrom(string filename, string newfilename, string country) {
    fstream file(filename, ios::out | ios::in | ios::binary);
    ofstream newfile(newfilename);

    if(!file) return -1;
    if(!newfile) return -1;

    product x;
    newfile << country;
    file.read((char *)&x, sizeof(product));
    while(!file.eof()){
        if(x.country == country){
            newfile<<endl;
            newfile<<x.name <<' '<<x.code<<' '<<x.factory<<' '<<x.price;
        }
        file.read((char *)&x, sizeof(product));
    }
    file.close();
    newfile.close();
    return 0;
}

int LastRecordIndex(string filename){
    fstream file(filename, ios::out | ios::in | ios::binary);
    if(!file) return -1;
    product x;
    int k=0;
    while(!file.eof()){
        file.read((char *)&x, sizeof(product));
        k++;
    }
    file.close();
    return k;
}

int DelByKey(string filename, int key){
    fstream file(filename, ios::out | ios::in | ios::binary);
    if(!file) return -1;
    product x;
    int index=2;
    while(!file.eof()){
        file.read((char *)&x, sizeof(product));
        if(x.code==key){
            break;
        }
        index++;
    }
    int num=(LastRecordIndex(filename)-2);
    file.seekg(sizeof(product)*num, ios::beg);
    if(file.bad()) return -1;
    file.read((char *)&x, sizeof(product));
    file.seekp(sizeof(product)*(index-2), ios::beg);
    if(file.bad()) return -1;
    file.write((char *)&x, sizeof(product));
    file.close();
    return 0;
}

int AddToEndFile(string filename){
    fstream file(filename, ios::out | ios::in | ios::binary|ios::ate);
    //string line;
    if(!file) return -1;
    product x;

    cin >> x.name>>x.code>>x.factory>>x.price>>x.country;
    //cout<<x.name<< x.code<<x.factory<<x.price<<x.country<<endl;
    file.write((char *)&x, sizeof(product));
    file.close();
    return 0;
}
#endif //INC_3_BINARY_H
