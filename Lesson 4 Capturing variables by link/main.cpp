#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int CountAndAddNewDogs(const vector<string>& new_dogs, const map<string, int>& max_amount,
                       map<string, int>& shelter) {
    //...
   return  count_if(new_dogs.begin(), new_dogs.end(),
    [&shelter, &max_amount](string new_dog)
    {
        int current_amount = shelter[new_dog];
        
        if(current_amount < max_amount.at(new_dog))
        {
            shelter[new_dog] += 1;
            return true;
        }
        else return false;
    }        
    );
}

int main() {
    map<string, int> shelter {
        {"shepard"s, 1},
        {"corgie"s, 3},
    };

    map<string, int> max_amount {
        {"shepard"s, 2},
        {"corgie"s, 3},
        {"shiba inu"s, 1},
    };

    cout << CountAndAddNewDogs({"shepard"s, "shiba inu"s, "shiba inu"s, "corgie"s}, max_amount, shelter) << endl;
}