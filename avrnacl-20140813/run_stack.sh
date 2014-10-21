#!/bin/bash


TOPDIR=`dirname $0`
PRIMITIVES=`cat $TOPDIR/PRIMITIVES`

. $TOPDIR/config

runstack()
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
  avrdude -cstk500v2 -p $TARGET_DEVICE -P $DEVICE_FILE -U flash:w:$TOPDIR/${IMPLEMENTATION}/test/stack_${PRIMITIVE}.hex -v
  stty -F $DEVICE_FILE raw icanon eof \^d 38400
  echo "===== Starting benchmark of ${IMPLEMENTATION}/${PRIMITIVE} =====" >> $STACKLOGFILE
  cat < $DEVICE_FILE >> $STACKLOGFILE
}

stackimpl()
{
  for i in $PRIMITIVES;do
    runstack $1 $i
  done
}


if [ -e $STACKLOGFILE ]; then
  rm $STACKLOGFILE
fi

if [ -n "$1" ];then
  if [ -n "$2" ];then
    runstack $1 $2
  else
    stackimpl $1
  fi
else
  IMPLEMENTATIONS=`ls -dl $TOPDIR/avrnacl* | grep ^d | sed "s/.*_//"`
  for i in $IMPLEMENTATIONS;do
    stackimpl "$i" 
  done
fi
