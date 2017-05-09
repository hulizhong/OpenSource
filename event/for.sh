#!/bin/bash


for (( ii=1; ii<=40; ii++))
do
    var='str'
    for (( i=1; i<175; i++))
    do
        var=${var}'A'
        echo ${var} > /home/OSPL/event/event.fifo
        sleep 0.001
    done
done
