#!/bin/sh

echo "Compilation de la librairie"
export HOSTYPE=Testing
make re
ls -l libft_malloc.so

echo "Export des fonctions"
nm libft_malloc.so
