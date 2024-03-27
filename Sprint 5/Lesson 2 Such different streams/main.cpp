#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

bool FindFlag(const string& str)
{
    return str[0] == '>';
}

// реализуйте эту функцию:
void CreateFiles(const string& config_file)
{
    ifstream fin;
    ofstream fout;
    fin.open(config_file);

    string str;
    string path = "";

    while (!fin.eof())
    {
        str = "";
        getline(fin, str);
        
        if(!FindFlag(str))
        {
            path = str;
        }
        else
        {
            str.erase(str.begin());
            fout.open(path, fstream::app);
            fout << str + "\n";
            fout.close();
        }
    }
    
}

string GetLine(istream& in) 
{
    string s;
    getline(in, s);
    return s;
}

int main() 
{
    ofstream("test_config.txt"s) << "a.txt\n"
                                    ">10\n"
                                    ">abc\n"
                                    "b.txt\n"
                                    ">123"s;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);
    cout << "Test passed!" << endl;
}



//2037665209 116 19897