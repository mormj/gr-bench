#!/usr/bin/python3
import argparse
import csv
import json
import sys

def build_header(obj, columns):
    header = []
    for col in columns:
        temp = '{:s}={:s}'.format(col, str(obj[col]))
        header.append(temp)
    return ';'.join(header)

def main():
    print('JSON-2-CSV\n', file=sys.stderr)
    
    desc = 'Convert JSON output from iterate_flowgraph.py script to CSV'
    parser = argparse.ArgumentParser(description=desc)
    parser.add_argument('--col_vars', help='column var(s)', nargs='+', 
                        default=['samples', 'nblocks', 'veclen'])
    parser.add_argument('--row_var', help='row vars', default='time')
    parser.add_argument('filepath', help='input filepath')
    parser.add_argument('out_filepath', help='output filepath')
    args = parser.parse_args()

    # Read in the JSON document
    json_doc = None
    with open(args.filepath) as infile:
        json_doc = json.load(infile)
    
    # Iterate over the JSON objects in 'results' and build columns
    headers = {}
    data = {}    
    for obj in json_doc['results']:
        header = build_header(obj, args.col_vars)
        if header not in data:
            data[header] = []
        data[header].append(obj[args.row_var])
    
    # Convert from column based to row based data and write out CSV file. 
    # NOTE: there is an implicit assumption here that each column is the same
    # length.
    first_key = list(data.keys())[0]
    length = len(data[first_key])
    with open(args.out_filepath, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(sorted(data.keys()))
        for idx in range(length):
            row = []
            for header in sorted(data.keys()):
                row.append(data[header][idx])
            writer.writerow(row)
    
if __name__ == '__main__':
    sys.exit(main())
