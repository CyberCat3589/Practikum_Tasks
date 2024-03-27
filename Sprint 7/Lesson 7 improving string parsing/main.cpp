#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

using namespace std;

class Translator
{
  public:
    Translator() = default;

    void Add(string_view source, string_view target)
    {
        if (source.empty() || target.empty())
            return;
        forward_[static_cast<string>(source)] = target;
        backward_[static_cast<string>(target)] = source;
    }

    string_view TranslateForward(string_view source) const
    {
        if(forward_.count(static_cast<string>(source)))
        {
            return forward_.at(static_cast<string>(source));
        }
        else return "";
    }

    string_view TranslateBackward(string_view target) const
    {
        if (backward_.count(static_cast<string>(target)))
        {
            return backward_.at(static_cast<string>(target));
        }
        else return "";
    }

  private:
    map<string, string> forward_;
    map<string, string> backward_;
};

void TestSimple()
{
    Translator translator;
    translator.Add(string("okno"s), string("window"s));
    translator.Add(string("stol"s), string("table"s));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
}

int main()
{
    TestSimple();
}