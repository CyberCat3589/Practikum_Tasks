#include "ini.h"
#include <cassert>

using namespace std;

namespace ini
{
    Section& Document::AddSection(std::string name)
    {
        Section new_section;
        sections_[name] = new_section;
        return new_section;
    }

    const Section& Document::GetSection(const std::string& name) const
    {
        assert(sections_.find(name) != sections_.end());
        return sections_.at(name);
    }

    std::size_t Document::GetSectionCount() const
    {
        return sections_.size();
    }

    Document Load(std::istream& input)
    {
        
    }
}