#include "libstat.h"

#include <iostream>
using namespace std;

int main() 
{
    statistics::tests::AggregSum();
    statistics::tests::AggregMax();
    statistics::tests::AggregMean();
    statistics::tests::AggregStandardDeviation();
    statistics::tests::AggregMode();
    statistics::tests::AggregPrinter();

    cout << "Test passed!"sv << endl;
}