#!/bin/sh

g++ -O3 extractDBLP.cpp -o run -std=c++0x
./run
python3 rearrange.py
python3 toJson.py
# please check the python version, use python 3+
rm dblp_au_relation3.txt
rm dblp_authors3.txt
rm dblp.temporal2.txt
