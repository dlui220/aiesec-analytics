#include "Table.hpp"

void Row::push_back(TableType &tt)
{
    data.push_back(tt);
}

void Row::pop_back()
{
    data.pop_back();
}

TableType& Row::operator[](unsigned int index)
{
    return data[index];
}

size_t Row::size()
{
    return data.size();
}

TableType& Row::back()
{
    return data.back();
}

Table::Table(unsigned int numCol)
{
    types.resize(numCol);
    
    for (unsigned int i = 0; i < numCol; ++i)
        cin >> types[i];
    
    for (unsigned int i = 0; i < numCol; ++i)
    {
        string junk;
        cin >> junk;
        colNames.push_back(junk);
    }
}

Table::Table(ifstream &ifs)
{
    ifs >> tableName;
    unsigned int numRows, numCols;
    ifs >> numRows >> numCols;

    types.resize(numCols);
    
    for (unsigned int i = 0; i < numCols; ++i)
        ifs >> types[i];
    
    colNames.resize(numCols);
    for (unsigned int i = 0; i < numCols; ++i)
        ifs >> colNames[i];
    
    pushRowsFromFile(ifs, numRows, numCols);

}

void Table::pushRowsFromFile(ifstream &ifs, unsigned int numRows, unsigned int numCols)
{
    for (unsigned int i = 0; i < numRows; ++i)
    {
        Row newRow;
        for (unsigned int j = 0; j < numCols; ++j)
        {
            if (types[j] == 'i')
            {
                int tempInt;
                ifs >> tempInt;
                TableType tableInt(tempInt);
                newRow.push_back(tableInt);
            }
            else if (types[j] == 's')
            {
                string tempString;
                ifs >> tempString;
                TableType tableString(tempString);
                newRow.push_back(tableString);
            }
            else if (types[j] == 'b')
            {
                bool tempBool;
                ifs >> tempBool;
                TableType tableBool(tempBool);
                newRow.push_back(tableBool);
            }
        }
        data.push_back(newRow);
    }
}

void Table::pushRows(unsigned int numRows)
{
    for (unsigned int i = 0; i < numRows; ++i)
    {
        Row newRow;
        for (unsigned int j = 0; j < types.size(); ++j)
        {
            if (types[j] == 'i')
            {
                int tempInt;
                cin >> tempInt;
                TableType tableInt(tempInt);
                newRow.push_back(tableInt);
            }
            else if (types[j] == 's')
            {
                string tempString;
                cin >> tempString;
                TableType tableString(tempString);
                newRow.push_back(tableString);
            }
            else if (types[j] == 'b')
            {
                bool tempBool;
                cin >> tempBool;
                TableType tableBool(tempBool);
                newRow.push_back(tableBool);
            }
        }
        data.push_back(newRow);
    }
}

Row& Table::operator[](unsigned int index)
{
    return data[index];
}

void Table::printTable()
{
    cout << "This table is " << tableName << '\n';
    
    for (unsigned int i = 0; i < colNames.size(); ++i)
        cout << colNames[i] << " ";
    cout << '\n';
    
    
    cout << "The types are " << endl;
    
    for (unsigned int i = 0; i < types.size(); ++i)
        cout << types[i] << " ";
    cout << endl;
    
    
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        for (unsigned int j = 0; j < data[i].size(); ++j)
            cout << data[i][j] << " ";
        cout << '\n';
    }
}

