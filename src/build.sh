#!/bin/bash

echo "Début de la compilation"

echo " Compilation des outils"
gcc -c utils/error.cpp -o utils/obj/error.o -lboost_regex

echo " Compilation du loader"
gcc -c loader/loader.cpp -o loader/obj/loader.o -lboost_regex

echo " Compilation du coeur"
gcc -c core/cell.cpp -o core/obj/cell.o -lboost_regex
gcc -c core/grid.cpp -o core/obj/grid.o -lboost_regex
gcc -c core/core.cpp -o core/obj/core.o -lboost_regex

echo " construction des librairies statiques"
cp utils/color.h local/color.h
cp core/cell.h local/cell.h
gcc -c core/cell.cpp -o local/cell.o -lboost_regex -fPIC

echo "Compilation de l'interface"
gcc main.cpp core/obj/* loader/obj/* utils/obj/* -lboost_regex -o ACS