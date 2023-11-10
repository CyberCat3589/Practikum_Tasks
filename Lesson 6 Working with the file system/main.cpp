#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) 
{
    return path(data, data + sz);
}

// напишите эту функцию
void PrintTree(ostream& dst, const path& p, int32_t level)
{
    string lead(level*2, ' ');
    dst << lead << p.filename().string() << "\n";
    vector<path> paths;
    
    for(const path& entry : filesystem::directory_iterator(p))
    {
        paths.push_back(entry);
    }

    sort(paths.begin(), paths.end(), 
    [](path p1, path p2)
    {
        return filesystem::status(p1).type() > filesystem::status(p2).type() || 
        (filesystem::status(p1).type() == filesystem::status(p2).type() && (p1.filename().string() > p2.filename().string()));
    });

    string lead_((level +1)*2, ' ');

    for(const path& item : paths)
    {
        if(filesystem::status(item).type() == filesystem::file_type::directory)
        {
            PrintTree(dst, item, level + 1);
        }
        else
        {
            dst << lead_ << item.filename().string() << "\n";
        }
    }
}

void PrintTree(ostream& dst, const path& p)
{
    PrintTree(dst, p, 0);
}

int main() 
{
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"s
    );
}