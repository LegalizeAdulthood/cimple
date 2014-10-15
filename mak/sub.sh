#!/bin/bash

SUB_SED=/tmp/sub.sed

### Be sure $SUB_SED exits.

if [ ! -f $SUB_SED ]
then
    echo "$0: $SUB_SED not found"
    exit 1
fi

### Perform substitution on each file.

for i
do
    if [ -f $i ]
    then
	mv $i $i.bak
	sed -f /tmp/sub.sed $i.bak > $i
    else
	echo "$0: warning: $i not found"
    fi
done
