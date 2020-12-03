import json
from matplotlib import pyplot as plt
import numpy as np
import itertools
from argparse import ArgumentParser

plt_num = 0
colors = plt.get_cmap("tab10")

def plot_results(args):
    
    data = []
    for idx,filename in enumerate(args.filename):
        # Opening JSON file
        f = open(filename, 'r')
        all_data = json.load(f)
        results = all_data['results']
        for r in results:
            r['file'] = idx
        
        data = data + results

    
    
    keys = np.unique([k for d in data for k in d.keys()])
    series = args.series
    if not series:
        series = []
    series = ['file'] + series


    fig_vars = keys
    fig_vars = fig_vars[fig_vars != args.xvar]
    fig_vars = fig_vars[fig_vars != args.yvar]
    if args.yvar == 'tput' or args.yvar == 'throughput':
        for d in data:
            d['tput'] = (d['samples'] / float(d['time']) ) / 1.0e6
        fig_vars = fig_vars[fig_vars != 'samples']
        fig_vars = fig_vars[fig_vars != 'time']

    for s in series:
        fig_vars = fig_vars[fig_vars != s]

    # go through the fig vars, and if there is only 1 value, then remove it from the fig vars
    fig_vars = [f for f in fig_vars if len(np.unique([d[f] for d in data if f in d])) > 1]


    # if fig_vars == []:
    #     fig_vars = None

    def gen_plot(filt_data, title):
        global plt_num
        plt.figure()
        if args.title:
            plt.title(args.title + ": " + title)
        else:
            plt.title(title)
        plt.xlabel(args.xvar if not args.xlabel else args.xlabel)
        plt.ylabel(args.yvar if not args.ylabel else args.ylabel)


        svals = []
        skeys = []
        for s in series:
            vals = np.unique([d[s] for d in filt_data if s in d])
            if len(vals):
                skeys.append(s)
                svals.append(vals)
            
        lgnd = []
        lgnd_handles = []
        coloridx = 0
        for b in itertools.product(*svals):
            color = colors(coloridx)
            series_filt = filt_data.copy()
            
            lgnd_str = ''
            for cnt,s in enumerate(skeys):
                ll1 = len(series_filt)
                
                series_filt  = [d for d in series_filt if (s not in d) or (s in d and d[s] == b[cnt])]                  
                ll2 = len(series_filt)
                if (ll2 < ll1):
                    if s == 'file' and len(args.filename) == len(args.names):
                        lgnd_str += f'{args.names[b[cnt]]},'
                    else:
                        lgnd_str += f'{s}={b[cnt]},'

                if not any([s in d for d in series_filt]) and list(svals[cnt]).index(b[cnt]) != 0:
                    series_filt = []
                    

            if len(series_filt):
                lgnd_str = lgnd_str[:-1] if lgnd_str[-1] == ',' else lgnd_str
                lgnd.append(lgnd_str)

                x = [float(d[args.xvar]) for d in series_filt]
                y = [float(d[args.yvar]) for d in series_filt]

                x_vals = list(np.unique(x))
                y_mean = []
                for xx in x_vals:
                    idx_at_val = [i for i, a in enumerate(x) if a == xx]
                    for idx in idx_at_val:
                        plt.plot(x[idx], y[idx], color=color,
                                marker=args.marker)

                    y_at_val = [y[i] for i in idx_at_val]
                    y_mean.append(np.mean(y_at_val))

                h, = plt.plot(x_vals, y_mean)
                lgnd_handles.append(h)
                coloridx += 1

        plt.legend(lgnd_handles,lgnd)

        if (args.save):
            plt.savefig( filename + str(plt_num) + ".png")
            plt_num += 1
        else:
            plt.show()
    
    if fig_vars == []:
        gen_plot(data,'')
    else:
        fvals = []
        for s in fig_vars:
            fvals.append(np.unique([d[s] for d in data]))
            
        for b in itertools.product(*fvals):
            fig_filt = data
            
            title_str = ''
            for cnt,s in enumerate(fig_vars):
                fig_filt  = [d for d in fig_filt if d[s] == b[cnt]]                  
                title_str += f'{s}={b[cnt]},'

            if title_str:
                title_str = title_str[:-1] if title_str[-1] == ',' else title_str
            gen_plot(fig_filt, title_str)


def main():
    parser = ArgumentParser(
        description='Plot the results from a single benchmark run')
    parser.add_argument('filename', help='Pathname to json results file',nargs='+')
    parser.add_argument('-x','--xvar', help='Variable to plot on x axis',required=True)
    parser.add_argument('-y','--yvar', help='Variable to plot on y axis',default='tput')
    parser.add_argument('--xlabel', help='X Axis Label')
    parser.add_argument('--ylabel', help='Y Axis Label',default='Throughput (Msps)')
    parser.add_argument('-t','--title', help='Title for plots',default='')
    parser.add_argument('-s','--series', help='Variables to use as data series', nargs='+')
    parser.add_argument('--save', help='Save Plots', action='store_true')
    parser.add_argument('-m','--marker',default='o')
    parser.add_argument('-n','--names',nargs='+')

    args = parser.parse_args()

    plot_results(args)


if __name__ == '__main__':
    main()
