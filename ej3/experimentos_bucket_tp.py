#Imports
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

#Leemos los resultados del experimento (random) y creamos el dataframe
fig = plt.figure()
df = pd.read_csv("./runtime_tp_random_bucket.csv")
df['cota'] = df['n']  #Vemos la correlación de nuestras medidas con la cota teórica que estimamos
                      #Cota teorica: O(n)
#Dibujamos el grafico con escala normal
ax1 = sns.lmplot(x='time', y='cota', data=df)
plt.xlabel("tiempo (s)")
plt.ylabel("cota teorica")
plt.title("Escala normal")
plt.savefig("./plots_bucket/plt_random.png")

#Hacemos lo mismo ahora con escala logaritmica para que se vea mejor
df['log_time'] = np.log(df['time'])
df['log_cota'] = np.log(df['cota'])

ax1 = sns.lmplot(x='log_time', y='log_cota', data=df)
plt.xlabel("log_tiempo (s)")
plt.ylabel("log_cota")
plt.title("Escala logarítmica")
#Acomodo el titulo porque cuando se guardaba se cortaba el titulo en el .png
plt.tight_layout()
plt.subplots_adjust(top=0.94)
plt.savefig("./plots_bucket/plt_random_logScale.png")

#
##########Comparamos entre random y sorted ascendente y descendente##############
#
df_sorted = pd.read_csv("runtime_tp_sorted_bucket.csv")
df_unsorted = pd.read_csv("runtime_tp_unsorted_bucket.csv")
df['time_sorted'] = df_sorted['time']
df['time_unsorted'] = df_unsorted['time']

#Escala normal
fig, ax = plt.subplots()

ax.scatter(df['n'],df['time'],color='yellow', label='random')
ax.scatter(df['n'],df['time_sorted'],color='blue', label='sorted asc')
ax.scatter(df['n'],df['time_unsorted'],color='red', label='sorted desc')
plt.xlabel("n")
plt.ylabel("tiempo (s)")
plt.title("Escala normal")
ax.legend()
ax.grid(True)
plt.savefig("./plots_bucket/comparacion_normal_scale")

#Escala logaritmica
fig, ax = plt.subplots()

ax.scatter(np.log(df['n']),np.log(df['time']),color='yellow')
ax.plot(np.log(df['n']),np.log(df['time']),color='yellow', label='random')
ax.scatter(np.log(df['n']),np.log(df['time_sorted']),color='blue')
ax.plot(np.log(df['n']),np.log(df['time_sorted']),color='blue', label='sorted asc')
ax.scatter(np.log(df['n']),np.log(df['time_unsorted']),color='red')
ax.plot(np.log(df['n']),np.log(df['time_unsorted']),color='red', label='sorted desc')
plt.xlabel("log_n")
plt.ylabel("log_tiempo (s)")
plt.title("Escala logarítmica")
ax.legend()
ax.grid(True)
plt.savefig("./plots_bucket/comparacion_log_scale")