import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import sys
sns.set()

path_archivo = sys.argv[1]
df = pd.read_csv(path_archivo)

# Promedio para cada n
df.groupby('n', as_index=False).mean()

# Nano -> Milli
df['fb'] /= 1000000.0
df['bt'] /= 1000000.0
df['mitm'] /= 1000000.0
df['pd'] /= 1000000.0

ax = df.plot('n', ['fb', 'bt', 'mitm', 'pd'], marker='o', title='Comparación de tiempos')
ax.set_xlabel('N')
ax.set_ylabel('Tiempo (ms)')

plt.show()