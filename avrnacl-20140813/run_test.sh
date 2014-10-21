#!/bin/bash

TOPDIR=`dirname $0`
PRIMITIVES=`cat $TOPDIR/PRIMITIVES`

. $TOPDIR/config

runtest()
{
  IMPLEMENTATION=avrnacl_$1
  if ! [ -d $TOPDIR/$IMPLEMENTATION ];then
    echo "Error: implementation $1 (directory $TOPDIR/$IMPLEMENTATION) does not exist"
    exit -1
  fi
  PRIMITIVE=$2
  if ! grep $PRIMITIVE $TOPDIR/PRIMITIVES 2>&1 > /dev/null ;then
    echo "Error: primitive $PRIMITIVE does not exist (see file $TOPDIR/PRIMITIVES for a list of supported primitives)"
    exit -1
  fi

  avrdude -cstk500v2 -p $TARGET_DEVICE -P $DEVICE_FILE -U flash:w:$TOPDIR/${IMPLEMENTATION}/test/test_${PRIMITIVE}.hex -v
  stty -F $DEVICE_FILE raw icanon eof \^d 38400
  echo "===== Starting test of ${IMPLEMENTATION}/${PRIMITIVE} =====" >> $TESTLOGFILE
  TESTOUT=`cat < $DEVICE_FILE`

  echo $TESTOUT >> $TESTLOGFILE
  if echo $TESTOUT | grep -q Checksum;then
    CHECKSUM=`echo $TESTOUT | grep Checksum | sed "s/Checksum:\ //g"`
    if echo $CHECKSUM | diff - $TOPDIR/test/checksums/${PRIMITIVE} >/dev/null;then 
      printf "Checksum OK\n" >> $TESTLOGFILE
    else
      echo "ERROR: wrong checksum" >> $TESTLOGFILE
    fi
  fi
}

testimpl()
{
  for i in $PRIMITIVES;do
    runtest $1 $i
  done
}


if [ -e $TESTLOGFILE ]; then
  rm $TESTLOGFILE
fi

if [ -n "$1" ];then
  if [ -n "$2" ];then
    runtest $1 $2
  else
    testimpl $1
  fi
else
  IMPLEMENTATIONS=`ls -dl $TOPDIR/avrnacl* | grep ^d | sed "s/.*_//"`
  for i in $IMPLEMENTATIONS;do
    testimpl "$i" 
  done
fi
