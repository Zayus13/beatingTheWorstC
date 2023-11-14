import os
import pandas as pd
import matplotlib.pyplot as plt

if __name__ == '__main__':
    path = ('C:\\Users\\sven_\\Desktop\\Beating the Worst '
            'Case\\praktikum_beating_the_worst_case_framework\\instances\\networks\\vc_domination_output')
    files = os.listdir(path)
    df = pd.DataFrame(columns=['instance', "n", "m", "kernel_size", "rounds"])
    # import csv files one after the other, calculate the average and write it into a dataframe
    for file in files:
        if file.endswith('.csv'):
            with open(path + '\\' + file, 'r', encoding='utf-8-sig') as f:
                results = f.readline().strip().split(',')
                file_name = file.split('.')[0]
                df.loc[len(df)] = {'instance': file_name, 'n': int(results[0]), 'm': int(results[1]),
                                   'kernel_size': int(results[2]), 'rounds': int(results[3])}

    df.to_csv('C:\\Users\\sven_\\Desktop\\Beating the Worst '
              'Case\\praktikum_beating_the_worst_case_framework\\evaluation\\vc.csv', index=False)

    #plot each instance as a point in a scatter plot based on the kernel size, x axis is the instance number, y axis is the kernel size
    plt.scatter(df['n'], df['kernel_size'])
    plt.xlabel('n')
    plt.ylabel('kernel_size')
    df["ratio"] = df["kernel_size"] / df["n"]

    df = df.sort_values(by=['ratio'], ascending=True)
    df = df.head(200)
    plt.scatter(df['n'], df['kernel_size'])
    plt.savefig('C:\\Users\\sven_\\Desktop\\Beating the Worst '
                'Case\\praktikum_beating_the_worst_case_framework\\evaluation\\vc_all.png')
    df = df.drop(columns=['n', 'm', 'kernel_size', 'rounds'])
    df.sort_values(by=['instance'], inplace=True)
    df.to_csv('C:\\Users\\sven_\\Desktop\\Beating the Worst Case\\praktikum_beating_the_worst_case_framework\\evaluation\\vc_best.csv', index=False)
