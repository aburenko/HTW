#!/bin/bash

#check
if ! [ $# -eq 1 ] || ! [ $1 -gt 1 ]
then
	echo "need one argument, that is > 1" 
	exit -1
fi

#main
for((i=0;i<$1;i++))
do
	let arr[$i]=$i+2;
	#echo "${arr[i]}"
done

for((i=0;i<$1;i++))
do
	if [ ${arr[$i]} -ne 0 ]
	then
		for((j=i+1;j<$1;j++))
		do
		    tmp=`echo "${arr[j]} % ${arr[i]}" | bc`
		 	#echo $tmp
			if test $tmp -eq 0
			then
				arr[j]=0
			fi	
		done
	fi
done

for((i=0;i<$1-1;i++))
do
	if [ ${arr[i]} -ne 0 ]
	then
		echo ${arr[i]}
	fi
done


exit 0
