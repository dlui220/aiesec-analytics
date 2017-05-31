#include "Table.hpp"

using namespace std;

const unsigned int NUMTABLES = 5;

int main()
{
    //READ TABLES IN THE ORDER OF TM, FINANCE, OGT, OGV, IGT
    vector<string> functionNames(NUMTABLES);

    functionNames[0] = "TM";
    functionNames[1] = "Finance";
    functionNames[2] = "oGT";
    functionNames[3] = "oGV";
    functionNames[4] = "iGT";

    string fileType = ".txt";

    ifstream ifs;

    cout << boolalpha;
    ifs >> boolalpha;

    vector<Table*> tPtrs(NUMTABLES);

    for (unsigned int i = 0; i < NUMTABLES; ++i)
    {
        ifs.open(functionNames[i] + fileType);
        tPtrs[i] = new Table(ifs);
        ifs.close();
        //tPtrs[i]->printTable();
        tPtrs[i]->print_report();
    }

    //we want to now create output files of each person's information
    //these output files should contain a message about how the member performed
    //this performance can be a percentage, a raw value, etc.
    //present any skills the member has developed
        //example skills are sales, communication, marketing, code, etc.

    for (unsigned int i = 0; i < tPtrs.size(); ++i)
        delete tPtrs[i];

}
