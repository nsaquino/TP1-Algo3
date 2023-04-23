#Imports
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

#
##########Comparamos entre random y sorted ascendente y descendente##############
#
df_sort = pd.read_csv("./runtime_tp_random.csv")
df_bucket = pd.read_csv("./runtime_tp_random_bucket.csv")
df_sort['time_bucket'] = df_bucket['time']

#Escala normal
fig, ax = plt.subplots()

ax.scatter(df_sort['n'],df_sort['time'],color='red', label='std sort')
ax.scatter(df_sort['n'],df_sort['time_bucket'],color='blue', label='bucket sort')
plt.xlabel("n")
plt.ylabel("tiempo (s)")
plt.title("Escala normal")
ax.legend()
ax.grid(True)
plt.savefig("./plots_ambos_sort/comparacion_normal_scale")

#Escala logaritmica
fig, ax = plt.subplots()

ax.scatter(np.log(df_sort['n']),np.log(df_sort['time']),color='red')
ax.plot(np.log(df_sort['n']),np.log(df_sort['time']),color='red', label='std sort')
ax.scatter(np.log(df_sort['n']),np.log(df_sort['time_bucket']),color='blue')
ax.plot(np.log(df_sort['n']),np.log(df_sort['time_bucket']),color='blue', label='bucket sort')
plt.xlabel("log_n")
plt.ylabel("log_tiempo (s)")
plt.title("Escala logarítmica")
ax.legend()
ax.grid(True)
plt.savefig("./plots_ambos_sort/comparacion_log_scale")