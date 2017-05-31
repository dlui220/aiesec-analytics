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

void Table::print_report()
{
  string fileType = ".txt";

  for (unsigned int i = 0; i < data.size(); ++i)
  {
    if (data[i][0].isString()){
      ofstream ofs;
      ofs.open("./members/" + data[i][0].getString() + fileType);
      ofs << "Hey " << data[i][0] << ", " << "\n\n";
      ofs << "Here is your monthly performance report. You have done the following: " << "\n\n";
      ofs << "You have attended " << data[i][1] << " functional meetings, which has helped improve on your functional understanding.\n";
      ofs << "You have attended " << data[i][2] << " GMMs, which has helped improve on your punctuality.\n";
      ofs << "You have attended " << data[i][3] << " conferences, which has helped renew your knowledge and understanding of AIESEC as well as strengthen your AIESEC network. \n";
      if (data[i][4].isBool()) {
        if (data[i][4].getBool()) {
          ofs << "You have completed an integrated experience (IXP), greatly developing your experiential learning. \n";
        } else {
          ofs << "You have not completed an integrated experience (IXP). \n";
        }
      }

      if (tableName == "TM"){
        ofs << "You were in charge of " << data[i][6] << " deliverables." << "\n";
        ofs << "You have accomplished " << data[i][5] << " deliverables, developing your project management skills. " << "\n";

      } else if (tableName == "Finance"){
        ofs << "" << "\n";

      } else if (tableName == "oGV" || tableName == "oGT"){
        ofs << "You were in charge of " << data[i][5] << " EPs, greatly developing your time management skills. \n";
        ofs << "You have contacted " << data[i][6] << " EPs, improving upon your outreach abilities. \n";
        ofs << "You have completed " << data[i][7] << " 1-on-1s, which will develop your consulting skills. \n";
        ofs << data[i][8] << " of your EPs have applied, improving upon your marketing skills. \n";
        ofs << data[i][9] << " of your EPs have been approved, developing both your interpersonal and customer service skills. \n";

      } else if (tableName == "iGT"){
        ofs << "You have sent " << data[i][5] << " emails and made " << data[i][6] << " phone calls, improving upon your professional communication skills. \n";
        ofs << "You have completed " << data[i][7] << " walk-ins, developing your interpersonal skills." << "\n";
        ofs << "You have signed with " << data[i][8] << " companies, which has developed both your persuasive and sales abilities. " << "\n";
      }
      ofs.close();

    }

  }
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
