#!/bin/bash
let i=0
let j=1
let tmp=1

fibonachi () {
  echo $tmp
  let tmp=$i+$j
  let i=$j
  let j=$tmp
  if [ "$tmp" -gt "$1" ]
  then
    return 0
  fi
  fibonachi $1
}

fibonachi $1

echo ende

exit 0
