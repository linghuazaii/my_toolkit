#!/bin/sh
#This file is auto-generated.Edit it at your own peril
if [ "$#" -eq 1 ]
then
grep --color=always -n -w -P "$1" --include=*.h --include=*.hpp --include=*.cc --include=*.cpp --include=*.c -r *
elif [ "$#" -eq 2 ]
then 
grep --color=always -n -w -P "$1" --include=*.h --include=*.hpp --include=*.cc --include=*.cpp --include=*.c -r * | grep -P "$2"
fi
