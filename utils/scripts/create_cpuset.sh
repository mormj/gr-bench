#!/bin/bash

NCORES=${1:-"4"}
MAX_CPUFREQ=${2:-"0"}

echo ### deleting CPU Sets
sudo cset -m set | grep ";" | grep -v root | cut -d ";" -f1 | xargs -n1 sudo cset set --destroy 

echo ### Creating new CPU Sets
# sudo cset shield --sysset=system --userset=sdr --cpu=2,6,3,7 --kthread=on

if [ $NCORES == "2" ]
then
  sudo cset shield --sysset=system --userset=sdr --cpu=6,14 --kthread=on
  if [ $MAX_CPUFREQ != "0" ]
  then
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu6/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu14/cpufreq/scaling_max_freq
  fi
elif [ $NCORES == "3" ]
then
  sudo cset shield --sysset=system --userset=sdr --cpu=4,7,15 --kthread=on
  if [ $MAX_CPUFREQ != "0" ]
  then
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu7/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu15/cpufreq/scaling_max_freq
  fi
elif [ $NCORES == "4" ]
then
  sudo cset shield --sysset=system --userset=sdr --cpu=6,7,14,15 --kthread=on
  # sudo cset shield --sysset=system --userset=sdr --cpu=4,5,6,7 --kthread=on
  if [ $MAX_CPUFREQ != "0" ]
  then
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu6/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu7/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu14/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu15/cpufreq/scaling_max_freq
  fi

elif [ $NCORES == "8" ]
then
  sudo cset shield --sysset=system --userset=sdr --cpu=4,5,6,7,12,13,14,15 --kthread=on
  if [ $MAX_CPUFREQ != "0" ]
  then
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu5/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu6/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu7/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu12/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu13/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu14/cpufreq/scaling_max_freq
    echo $MAX_CPUFREQ | sudo tee /sys/devices/system/cpu/cpu15/cpufreq/scaling_max_freq
  fi
fi

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
