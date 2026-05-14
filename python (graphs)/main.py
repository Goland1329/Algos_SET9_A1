# Cтроит графики по файлу text.txt


import matplotlib.pyplot as plt
import re

with open('text.txt', 'r', encoding='utf-8') as f:
    lines = f.readlines()

data = []
for line in lines:
    line = line.strip()
    if not line or '-' in line or 'Алгоритм' in line:
        continue
    parts = re.split(r'\s{2,}', line)
    if len(parts) == 5:
        data.append(parts)

stats = {}
for row in data:
    algo, arr_type, size, time_ms, comps = row
    if arr_type not in stats:
        stats[arr_type] = {}
    if algo not in stats[arr_type]:
        stats[arr_type][algo] = {'size': [], 'time': [], 'comps': []}
    
    stats[arr_type][algo]['size'].append(int(size))
    stats[arr_type][algo]['time'].append(float(time_ms))
    stats[arr_type][algo]['comps'].append(int(comps))

for arr_type, algos in stats.items():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    
    for algo, metrics in algos.items():
        ax1.plot(metrics['size'], metrics['time'], label=algo)
    ax1.set_title(f'{arr_type}: Время')
    ax1.set_xlabel('Размер массива')
    ax1.set_ylabel('Время (мс)')
    ax1.grid(True, alpha=0.3)
    ax1.legend()

    for algo, metrics in algos.items():
        ax2.plot(metrics['size'], metrics['comps'], label=algo)
    ax2.set_title(f'{arr_type}: Сравнения')
    ax2.set_xlabel('Размер массива')
    ax2.set_ylabel('Кол-во операций')
    ax2.set_yscale('log')
    ax2.grid(True, alpha=0.3)
    ax2.legend()

    plt.tight_layout()
    plt.show()
