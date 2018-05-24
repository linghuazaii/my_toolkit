#!/bin/sh
#This file is auto-generated.Edit it at your own peril
sdiff -l $1 $2 | cat -n | grep -v -e '($'
