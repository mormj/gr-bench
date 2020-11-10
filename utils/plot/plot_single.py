import json
from matplotlib import pyplot as plt
import numpy as np
import itertools
from argparse import ArgumentParser

plt_num = 0
colors = plt.get_cmap("tab10")

def plot_results(args):
    
    filename = args.filename

    # Opening JSON file
    f = open(filename, 'r')
    data = json.load(f)

    data = data['results']
    keys = np.unique([k for d in data for k in d.keys()])

    fig_vars = keys
    fig_vars = fig_vars[fig_vars != args.xvar]
    fig_vars = fig_vars[fig_vars != args.yvar]
    if args.yvar == 'tput' or args.yvar == 'throughput':
        for d in data:
            d['tput'] = (d['samples'] / float(d['time']) ) / 1.0e6
        fig_vars = fig_vars[fig_vars != 'samples']
        fig_vars = fig_vars[fig_vars != 'time']
    for s in args.series:
        fig_vars = fig_vars[fig_vars != s]

    if not fig_vars:
        fig_vars = None

    def gen_plot(filt_data, title):
        global plt_num
        plt.figure()
        if args.title:
            plt.title(args.title + ": " + title)
        else:
            plt.title(title)
        plt.xlabel(args.xvar if not args.xlabel else args.xlabel)
        plt.ylabel(args.yvar if not args.ylabel else args.ylabel)

        if not args.series:
            x = [d[args.xvar] for d in filt_data]
            y = [d[args.yvar] for d in filt_data]
            plt.plot(x, y)

        else:
            svals = []
            for s in args.series:
                svals.append(np.unique([d[s] for d in filt_data]))
                
            lgnd = []
            lgnd_handles = []
            coloridx = 0
            for b in itertools.product(*svals):
                color = colors(coloridx)
                series_filt = filt_data
                
                lgnd_str = ''
                for cnt,s in enumerate(args.series):
                    series_filt  = [d for d in series_filt if d[s] == b[cnt]]                  
                    lgnd_str += f'{s}={b[cnt]},'

                lgnd_str = lgnd_str[:-1] if lgnd_str[-1] == ',' else lgnd_str
                lgnd.append(lgnd_str)

                x = [d[args.xvar] for d in series_filt]
                y = [d[args.yvar] for d in series_filt]

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
    
    if fig_vars == None:
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

            title_str = title_str[:-1] if title_str[-1] == ',' else title_str
            gen_plot(fig_filt, title_str)


def main():
    parser = ArgumentParser(
        description='Plot the results from a single benchmark run')
    parser.add_argument('filename', help='Pathname to json results file')
    parser.add_argument('-x','--xvar', help='Variable to plot on x axis',required=True)
    parser.add_argument('-y','--yvar', help='Variable to plot on y axis',default='tput')
    parser.add_argument('--xlabel', help='X Axis Label')
    parser.add_argument('--ylabel', help='Y Axis Label',default='Throughput (Msps)')
    parser.add_argument('-t','--title', help='Title for plots',default='')
    parser.add_argument('-s','--series', help='Variables to use as data series', nargs='+')
    parser.add_argument('--save', help='Save Plots', action='store_true')
    parser.add_argument('-m','--marker',default='o')

    args = parser.parse_args()

    plot_results(args)


if __name__ == '__main__':
    main()
