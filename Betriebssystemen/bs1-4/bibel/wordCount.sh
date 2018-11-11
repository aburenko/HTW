#!/bin/bash
read -p "Your word: " word
read -p "Where to search? " text
echo "There are so many $word in file '$text': "
grep $word $text | wc
