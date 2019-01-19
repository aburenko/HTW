#!/bin/bash
javac -d ./bin/ ./src/UDPtransfer.java
javac -cp ./bin/ -d ./bin ./src/Server.java
javac -cp ./bin/ -d ./bin ./src/Client.java

#clean all previous tries
rm alice1*.txt 2>/dev/null

echo compile successide

exit 0
