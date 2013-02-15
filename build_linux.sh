#!/bin/bash
rm -rf *~ *.zip *.xpl *.o 
rm CMakeCache.txt

cmake .

make clean
make

cd ..
zip SSG_B748/SSG_B748.zip SSG_B748/*.cpp SSG_B748/*.h SSG_B748/SSG_B748.names SSG_B748/CMakeLists.txt SDK/*/*/*.h SDK/*/*/*.cpp SSG_B748/*.sh  

