#include "ini.h"

using namespace std;

namespace ini
{
    Section& Document::AddSection(std::string name)
    {
        return sections_[name];
    }

    const Section& Document::GetSection(const std::string& name) const
    {
        static Section static_empty;
        if(sections_.find(name) == sections_.end()) return static_empty;
        return sections_.at(name);
    }

    std::size_t Document::GetSectionCount() const
    {
        return sections_.size();
    }

    Document Load(std::istream& input)
    {
        Document result;
        Section* section = nullptr;
        for (string line; getline(input, line);)
        {
            auto pos = line.find_first_not_of(' ', 0);
            if (pos == line.npos)
            {
                continue;
            }
            line = line.substr(pos);
            if (line[0] == '[')
            {
                string section_name = line.substr(1, line.find(']') - 1);
                section = &result.AddSection(section_name);
            }
            else
            {
                pos = line.find('=');
                string unit_name = line.substr(0, line.find_last_not_of(' ', pos - 1) + 1);
                line = line.substr(line.find_first_not_of(' ', pos + 1));
                string unit_value = line.substr(0, line.find_last_not_of(' ') + 1);
                section->insert({unit_name, unit_value});
            }
        }
        return result;
    }
}