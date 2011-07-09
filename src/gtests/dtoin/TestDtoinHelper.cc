#include "gtests/dtoin/TestDtoinHelper.hh"

string TestDtoinHelper::getMachineData(){
    return string("4 \
 \
0 \
0 \
30 400 \
16 80 \
0 1 4 5 \
 \
0 \
0 \
10 240 \
8 160 \
1 0 3 4 \
 \
1 \
1 \
15 100 \
12 80 \
4 3 0 2 \
 \
1 \
2 \
10 100 \
8 80 \
5 4 2 0");
}

string TestDtoinHelper::getRessourceData(){
    return string("2 \
 \
1 \
100 \
 \
0 \
10");
}

string TestDtoinHelper::getServiceData(){
    return string("2 \
 \
2 \
0 \
 \
1 \
1 \
0 \
 \
3 \
0 \
12 10 \
1000 \
 \
0 \
10 20 \
100 \
 \
1 \
6 200 \
1");
}

