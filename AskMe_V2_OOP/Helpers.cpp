#include "Helpers.h"
using namespace std;
#include <sstream>
#include <fstream>
#include <iostream>

vector<string> ReadFileLines(string &path)
{
    vector<string> lines;
    fstream fin(path);
    string line;
    if (fin.fail())
    {
        cout << "Cant open the file :( \n\n";
        return lines;
    }
    while (getline(fin, line))
    {
        if (line.size() == 0) // if the line is empty -> ignore this line :)
            continue;
        lines.push_back(line);
    }
    fin.close();
    return lines;
}

vector<string> SplitString(string &line, string delimiter)
{
    vector<string> fields;
    string field;
    int pos = 0;
    while ((pos = (int)line.find(delimiter)) != -1) // if not exist find() -> returns -1
    {
        field = line.substr(0, pos); // we remove the previous field, so next one we start from index 0
        fields.push_back(field);
        line.erase(0, pos + delimiter.length());
    }
    fields.push_back(line); // after finshing, we need to add last field "ok"
    return fields;
}

void WriteFileLines(string &path, vector<string> &lines) // to do a bool append or overwrite
{
    ofstream fout(path);
    if (fout.fail())
    {
        cout << "\n\nERROR: Can't open the file\n\n";
        return;
    }

    for (auto &line : lines)
        fout << line << "\n";
    fout.close();
}
