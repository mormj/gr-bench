# gr-bench

Tools for comparative benchmarking of GNU Radio flowgraphs

## Purpose

The goal of this project is to provide comparative benchmarking tools for arbitrary GNU Radio flowgraphs, so that changes to the hardware, accelerated blocks, scheduler can be analyzed as variables are changed.  

There have been several projects focused on gathering benchmarking info from running GNU Radio flowgraphs.  

## Dependencies

Same as any other GR OOT module with the addition of

```
cpuset
matplotlib
```

## Prior Work / References

https://github.com/osh/gr-benchmark

https://github.com/bastibl/gr-sched

Bastian Bloessl, Marcus Müller and Matthias Hollick, “Benchmarking and Profiling the GNU Radio Scheduler,” Proceedings of 9th GNU Radio Conference (GRCon 2019), Huntsville, AL, Sep 2019.

Hitefield, Seth David. A Defense-In-Depth Security Architecture for Software Defined Radio Systems. Diss. Virginia Tech, 2020.

## Usage

Below is the basic usage to obtain a plot

1. Shield a set of CPUs (edit the script to suit your hardware)
```bash
./utils/scripts/create_cpuset.sh
```

2. Iterate over a benchmarking flowgraph
```bash
apps/iterate_flowgraph.py time /share/git/gr-bench/bench/bm_copy.py --iters 10 --vars samples:[1000000000,] nblocks:[4,8,16,32,64,128,256]
```

3. Plot the results

```bash
python3 utils/plot/plot_single.py apps/results/bm_copy.py_results_200212_184320.json -x nblocks -y tput
```
