#!/bin/sh
#This file is auto-generated.Edit it at your own peril
if [ "$#" -eq 1 ]
then
grep --color=always -n -w -P "$1" --include=*.h --include=*.hpp -r *
elif [ "$#" -eq 2 ]
then 
grep --color=always -n -w -P "$1" --include=*.h --include=*.hpp -r * | grep -P "$2"
fi
