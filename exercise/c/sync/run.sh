#! /bin/sh
echo "starting subscribers..."
for i in `seq 10` ; do
    ./syncSub &
done
echo "Starting publisher..."
./syncPub
