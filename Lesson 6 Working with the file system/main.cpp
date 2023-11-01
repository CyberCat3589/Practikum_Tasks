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

void PrintTreeRec(const path& p, vector<path>& paths)
{
    for(const auto& dir_entry : filesystem::directory_iterator(p))
    {
        filesystem::file_status path_status = filesystem::status(dir_entry);
        paths.push_back(dir_entry);
        if(path_status.type() == filesystem::file_type::directory)
        {
            PrintTreeRec(dir_entry, paths);   
        }
    }
}

// напишите эту функцию
void PrintTree(ostream& dst, const path& p)
{
    vector<path> paths;
    PrintTreeRec(p, paths);

    sort(paths.rbegin(), paths.rend());

    for(path p : paths)
    {
        dst << p.filename().string() << endl;
    }
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

    //ostringstream out;
    PrintTree(cout, "test_dir"_p);
    // assert(out.str() ==
    //     "test_dir\n"
    //     "  b\n"
    //     "    f2.txt\n"
    //     "    f1.txt\n"
    //     "  a\n"
    //     "    f3.txt\n"s
    // );
}