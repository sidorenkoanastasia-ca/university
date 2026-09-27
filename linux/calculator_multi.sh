#!/bin/bash
result=$1

if ! [[ "$result" =~ ^[0-9]+$ ]]
then
echo "Enter number"
exit 1
fi

shift 1

while [ $# -ge 2 ]
do

if ! [[ "$2" =~ ^[0-9]+$ ]]
then
echo "Enter number"
exit 1
fi

case $1 in
"+") result=$(echo "scale=6; $result+$2" | bc);;
"-") result=$(echo "scale=6; $result-$2" | bc);;
"x"|"X") result=$(echo "scale=6; $result*$2" | bc);;
"/") if [ $(echo "scale=6; $2==0" | bc) -eq 1 ];
then
echo 'Error: division by zero'
exit 1
fi
result=$(echo "scale=6; $result/$2" | bc);;
*) echo 'Unknown operation'
exit 1;;
esac

shift 2
done

echo $results