#ifndef Table_hpp
#define Table_hpp

#include <iostream>
#include <vector>
#include <string>
#include "TableType.h"
#include <fstream>

using namespace std;

class Row
{
private:

    vector<TableType> data;

public:

    Row() { }

    void push_back(TableType &tt);
    void pop_back();
    TableType &operator[](unsigned int index);
    size_t size();
    TableType &back();

};

class Table
{
private:
    vector<Row> data;
    vector<string> colNames;
    vector<char> types;
    string tableName;

public:

    void print_report();
    Table() { }
    Table(unsigned int numCol);
    Table(ifstream &ifs);
    void pushRowsFromFile(ifstream &ifs, unsigned int numRows, unsigned int numCols);

    void pushRows(unsigned int numRows);
    Row &operator[](unsigned int index);

    void printTable();
};

#endif /* Table_hpp */
