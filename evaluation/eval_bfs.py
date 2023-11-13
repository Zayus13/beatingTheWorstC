import os
import pandas as pd

if __name__ == '__main__':
    path = ('C:\\Users\\sven_\\Desktop\\Beating the Worst '
            'Case\\praktikum_beating_the_worst_case_framework\\instances\\networks\\bfssolver_output')
    files = os.listdir(path)
    df = pd.DataFrame(columns=['instance', "n", "m", 'average_uni', 'average_bi'])
    # import csv files one after the other, calculate the average and write it into a dataframe
    for file in files:
        if file.endswith('.csv'):
            with open(path + '\\' + file, 'r', encoding='utf-8-sig') as f:
                file_name = file.split('.')[0]
                line = f.readline()
                params = line.split(',')
                line = f.readline()
                sum_one = 0
                for i in line.strip().split(','):
                    sum_one += int(i)
                line = f.readline()
                sum_two = 0
                for i in line.strip().split(','):
                    sum_two += int(i)
                average_one = sum_one / len(line.split(','))
                average_two = sum_two / len(line.split(','))
                df.loc[len(df)] = {'instance': file_name, 'n': int(params[0]), 'm': int(params[1]),
                                   'average_uni': average_one,
                                   'average_bi': average_two}
df.to_csv('C:\\Users\\sven_\\Desktop\\Beating the Worst Case\\praktikum_beating_the_worst_case_framework\\evaluation\\bfs.csv', index=False)
# find the best instances, where average_bi diveded by average_uni is the smallest
df['ratio'] = df['average_bi'] / df['average_uni']
df = df.sort_values(by='ratio')
df = df.reset_index(drop=True)
df = df["instance"]
df = df.head(200)
df.to_csv('C:\\Users\\sven_\\Desktop\\Beating the Worst Case\\praktikum_beating_the_worst_case_framework\\evaluation\\bfs_best.csv', index=False)



