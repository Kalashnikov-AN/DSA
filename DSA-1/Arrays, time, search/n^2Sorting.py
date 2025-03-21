import matplotlib.pyplot as plt
import seaborn
plt.figure(figsize = (15, 8)) #устанавливаем размер графика
plt.title("Среднее время работы") #название графика
plt.plot([0, 1_00_000, 500_000, 1_000_000], [0, 22.45, 766.842, 2341.414], 'o--', label = "bubble sort")
plt.plot([0, 1_00_000, 5_00_000, 1_000_000], [0, 3.4, 84.794, 340.880], 'o--', label = "insertion sort")
plt.grid(True) #добавляем линии сетки
plt.legend(loc = 'best') #добавляем легенду
plt.ylabel('Время (секунды)') #подписываем ось у
plt.xlabel('Размер массива') #подписываем ось х
plt.show()
