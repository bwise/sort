#include "testmulti.h"
#include <omp.h>

#include <iostream>
#include <thread>
using namespace std;


testMulti::testMulti()
{
//#pragma omp parallel num_threads(2)

   //#pragma omp parallel for
    for(int i =0; i<4000; i++){
        //cout<<omp_get_max_threads();
}
}

