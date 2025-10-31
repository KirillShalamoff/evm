import matplotlib.pyplot as plt

# Ваши данные: (num_fragments, время в тактах)
data = """1 : 5
 2 : 5
 3 : 5
 4 : 5
 5 : 5
 6 : 5
 7 : 9
 8 : 9
 9 : 9
10 : 9
11 : 9
12 : 9
13 : 15
14 : 15
15 : 15
16 : 15
17 : 15
18 : 15
19 : 15
20 : 15
21 : 15
22 : 15
23 : 15
24 : 15
25 : 15
26 : 15
27 : 15
28 : 15
29 : 15
30 : 15
31 : 15
32 : 15"""

# Парсим данные
x = []
y = []
for line in data.strip().splitlines():
    frag, time = line.split(':')
    x.append(int(frag.strip()))
    y.append(int(time.strip()))

# Строим график
plt.figure(figsize=(10, 6))
plt.plot(x, y, marker='o', linestyle='-', color='b', linewidth=2, markersize=5)

# Настройки
plt.title('Время доступа к памяти в зависимости от числа фрагментов', fontsize=14)
plt.xlabel('Число фрагментов', fontsize=12)
plt.ylabel('Время доступа (такты на элемент)', fontsize=12)
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.xticks(range(1, 33))
plt.yticks(sorted(set(y)))  # только уникальные значения времени

# Показываем график
plt.tight_layout()
plt.show()
