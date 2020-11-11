#!/usr/bin/env python3

'''
A Script to iterate over the parameters of a flowgraph for benchmarking

Pass the ranges to iterate over to the --vars argument in colon separated paris
e.g. iterate_flowgraph.py fg_name --vars samples:[100,200,300] rt_prio[True,False]

'''

import itertools
import numpy as np
import argparse
import subprocess
import json
import datetime
import re
import os 
import pathlib

def rangepair(arg):
    pairstr = arg.split(':')
    varname = pairstr[0]
    varvalues = eval(pairstr[1])
    return (varname, varvalues)

parser = argparse.ArgumentParser(description='Run a flowgraph iterating over parameters for benchmarking')
parser.add_argument('operation', choices=['time','migrations','resched','flamegraph'], default='time')
parser.add_argument('pathname', help='Pathname to flowgraph to run')
parser.add_argument('--vars', help='named variables and their associate ranges to iterate over', type=rangepair, nargs='+')
parser.add_argument('--iters', type=int, default=1, help='cpuset to utilize')
parser.add_argument('--cpuset', default='2,3,6,7', help='cpuset to utilize')
parser.add_argument('--userset', default='sdr', help='cpuset to utilize')
parser.add_argument('--python_exe', default='/usr/bin/python3')

args = parser.parse_args()
print(args)

varnames = [y[0] for y in args.vars]
varvalues = [y[1] for y in args.vars]


pattern = r'\[PROFILE_TIME\](.*)\[PROFILE_TIME\]'

params = {}
params['operation'] = args.operation
params['pathname'] = args.pathname
params['vars'] = {v[0]:v[1] for v in args.vars}

json_output = {}
json_output['params'] = params
res = []
json_output['results'] = res

results_path = os.path.join(pathlib.Path(__file__).parent.absolute(),'results')

dtstr = datetime.datetime.today()
results_filename = os.path.join(results_path,f'gr-bench_{os.path.split(params["pathname"])[-1]}_results_{dtstr:%y%d%m_%H%M%S}.json')

for x in itertools.product(*varvalues):
    if (args.operation == "time"):
        shellcmd = ['cset', 'shield', '--userset=sdr', '--exec', '--']
    elif (args.operation == "migrations"):
        shellcmd = ['perf', 'record', '-C', '2,3,6,7', '-o', 'migrations_rt.dat', '-m', '32768', '-e', 'sched:sched_migrate_task' ,'--', 'cset', 'shield', '--userset=sdr', '--exec', '--']

    r = {}

    if (args.pathname.split('.')[-1] == 'py'):
        shellcmd.append(args.python_exe)    
    shellcmd.append(args.pathname)
    for (n,v) in zip(varnames,x):
        r[n] = v
        if (type(v) == bool):
            if (v):
                shellcmd.append('--' + n)
        else:
            shellcmd.append('--' + n)
            shellcmd.append(str(v))
            
    for it in range(args.iters):
        print(' '.join(shellcmd))
        myshell = subprocess.Popen(shellcmd, 
                    stdout=subprocess.PIPE, 
                    stderr=subprocess.STDOUT)
        stdout,stderr = myshell.communicate()
        time = re.search(pattern,str(stdout)).group(1)
        r2 = r.copy()
        r2['time'] = time
        r2['tput'] = r2['samples'] / float(time)
        for l in str(stdout).split('\\n'):
            print(l)

        res.append(r2)
        with open(results_filename, 'w') as json_file:
            json.dump(json_output, json_file)


            # print(str(stdout[0]).split('\\n'))


print('To plot, run: \n ' + 'python3 ' + os.path.abspath(os.path.join(__file__,'..','..','utils','plot','plot_single.py')) + ' ' + os.path.abspath(results_filename) + ' -x nblocks -y tput')
