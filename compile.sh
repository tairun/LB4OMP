#!/bin/bash

git pull
cd intel
ml intel/2019a
ml CMake/3.13.3-GCCcore-8.2.0 
cmake -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc -DLIBOMP_HAVE___RDTSC=ON -DLIBOMP_HAVE_X86INTRIN_H=ON ..
make -j8
