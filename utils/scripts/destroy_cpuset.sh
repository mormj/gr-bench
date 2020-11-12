#!/bin/bash

echo ### deleting CPU Sets
sudo cset -m set | grep ";" | grep -v root | cut -d ";" -f1 | xargs -n1 sudo cset set --destroy 
