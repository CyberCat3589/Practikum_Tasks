#include <fstream>
#include <string>

#include "log_duration.h"

using namespace std;

int main() 
{
    
    {
        LOG_DURATION("Using endl"s);
        ofstream out_file("ballad.txt"s);
        for (int i = 0; i < 50000; ++i) 
        {
            out_file << "С любимыми не расставайтесь"s << endl;
        }
    }

    {
        LOG_DURATION("Using \\n"s);
        ofstream out_file("ballad.txt"s);
        for (int i = 0; i < 50000; ++i) 
        {
            out_file << "С любимыми не расставайтесь \n"s;
        }
    }
    

    throw;
}