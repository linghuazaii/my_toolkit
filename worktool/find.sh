#!/bin/sh
#This file is auto-generated.Edit it at your own peril
if [ "$#" -eq 1 ]
then
grep --color=always -n -w -E "$1" --include=*.h --include=*.hpp --include=*.cc --include=*.cpp -r *
elif [ "$#" -eq 2 ]
then 
grep --color=always -n -w -E "$1" --include=*.h --include=*.hpp --include=*.cc --include=*.cpp -r * | grep -E "$2"
fi
