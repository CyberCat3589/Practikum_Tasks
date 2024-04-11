#include "libstat.h"

#include <iostream>
using namespace std;

int main() {
    TestStatAggregSum();
    TestStatAggregMax();
    TestStatAggregMean();
    TestStatAggregStandardDeviation();
    TestStatAggregMode();
    TestStatAggregPrinter();

    cout << "Test passed!"sv << endl;
}