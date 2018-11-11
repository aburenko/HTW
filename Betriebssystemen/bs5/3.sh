#!/bin/bash
a () 
{
  scp $1 $2
  if [ $? -eq 0 ]
  then
    echo success
    return 0
  else
    echo failed
    return 1 
  fi    
}
    
r=$(a $1 $2)
echo :$r
exit
