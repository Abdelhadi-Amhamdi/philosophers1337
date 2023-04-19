
#!/bin/bash

filename=$1
nb=$2

for (( i=1; i<=nb; i++ )); do
  echo `cat $filename | grep -w "$i is eating" | wc -l`
done