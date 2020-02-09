#! /usr/bin/env bash
while true
do
	if [[ -z "$1" ]]
	then
		echo "y"
	else
		A=""
		for i in $@
		do
		A+="$i "
		done
		echo "$A"
	fi
done
