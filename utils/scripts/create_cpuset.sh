#!/bin/bash

echo ### deleting CPU Sets
sudo cset -m set | grep ";" | grep -v root | cut -d ";" -f1 | xargs -n1 sudo cset set --destroy 

echo ### Creating new CPU Sets
# sudo cset shield --sysset=system --userset=sdr --cpu=2,6,3,7 --kthread=on
sudo cset shield --sysset=system --userset=sdr --cpu=6,7,14,15 --kthread=on

# sudo cset shield --sysset=system --userset=sdr --cpu=4,5,6,7 --kthread=on
# echo 0 | sudo tee /sys/devices/system/cpu/cpu12/online
# echo 0 | sudo tee /sys/devices/system/cpu/cpu13/online
# echo 0 | sudo tee /sys/devices/system/cpu/cpu14/online
# echo 0 | sudo tee /sys/devices/system/cpu/cpu15/online

# echo 1 | sudo tee /sys/devices/system/cpu/cpu12/online
# echo 1 | sudo tee /sys/devices/system/cpu/cpu13/online
# echo 1 | sudo tee /sys/devices/system/cpu/cpu14/online
# echo 1 | sudo tee /sys/devices/system/cpu/cpu15/online

# sudo cset shield --sysset=system --userset=sdr --cpu=4,5,6,7,12,13,14,15 --kthread=on

echo ### CPU Sets
sudo cset set

sudo chown -R root:$USER /sys/fs/cgroup/cpuset
sudo chmod -R g+rwx /sys/fs/cgroup/cpuset
