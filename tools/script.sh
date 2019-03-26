#!/bin/sh

DBNAME="test.db"

PATHNAME="grep.sql"
ARGU_1=$1
ARGU_2=$2
ARGU_3=$3

TARGET="final.dot"

sqlite3 $DBNAME ".output ${PATHNAME}" "SELECT input,output FROM gene WHERE genome_id=${ARGU_3} AND active=1"
#sqlite3 $DBNAME ".output ${PATHNAME}" "SELECT input,output FROM gene WHERE genome_id=${ARGU_3} AND active=0"
#sqlite3 $DBNAME ".output ${PATHNAME}" "SELECT input,output FROM gene WHERE genome_id=${ARGU_3}"

touch $TARGET
rm $TARGET
touch $TARGET

cat pre_values_1.tmp >> $TARGET

INPUTNODE=" "
for i in $(seq 0 $ARGU_1); do
	INPUTNODE=$INPUTNODE" "$i
done
INPUTNODE=$INPUTNODE";"

OUTPUTNODE=" "
for i in $(seq $(($ARGU_1+1)) $(($ARGU_2+$ARGU_1)) ); do
	OUTPUTNODE=$OUTPUTNODE" "$i
done
OUTPUTNODE=$OUTPUTNODE";"

echo $INPUTNODE >> $TARGET
cat pre_values_2.tmp >> $TARGET
echo $OUTPUTNODE >> $TARGET
echo "    }" >> $TARGET

cat pre_values_3.tmp >> $TARGET 

while read p; do
	VALUES=${p//"|"/"->"}
	echo "    "$VALUES >> $TARGET
done < $PATHNAME

echo "    }" >> $TARGET
echo "}" >> $TARGET

dot $TARGET -Tps -o final.ps
