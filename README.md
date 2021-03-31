[![CCI](https://github.com/Kam1runetzLabs/tp_hw_2/actions/workflows/CCI.yml/badge.svg)](https://github.com/Kam1runetzLabs/tp_hw_2/actions/workflows/CCI.yml) [![codecov](https://codecov.io/gh/Kam1runetzLabs/tp_hw_2/branch/development/graph/badge.svg)](https://codecov.io/gh/Kam1runetzLabs/tp_hw_2)

Студент: Шумеев Илья

Группа: АПО-12

Телеграм: @w1ckedente

# Домашнее задание №2 по углубленному программированию на C/C++

Вариант #49 В вашем распоряжении — массив из 33 млн. трехмерных радиус-векторов. Составьте наивный алгоритм определения
среднего значения X-, Y — и Z-координаты, а затем реализуйте параллельный алгоритм с использованием нескольких потоков с
учетом оптимизации работы с кэш-памятью.

На что необходимо обратить внимание:

- основная информация описана в https://park.mail.ru/blog/topic/view/14270/
- параллельная реализация не должна быть осуществлена с помощью процессов, когда требуется реализация с помощью
  потоков (и наоборот);
- компиляция должна происходить с флагами -Wall -Werror -Wpedantic, то есть необработанных ворнингов быть не должно;
- количество потоков/процессов должно быть не захардкожено, а определяться в зависимости от возможностей системы (
  например, в зависимости от количества ядер процессора);
- при разработке обеих библиотек стоит делать общий интерфейс, не раскрывая особенностей реализации;
- библиотеки должны быть взаимозаменяемыми - конкретная реализация (последовательная/параллельная) - использоваться в
  зависимости от конфигурации сборки;
- юнит-тесты должны быть реализованы для обеих реализаций (последовательной/параллельной). Покрытие тестами должно быть
  максимально возможным;
- должны присутствовать стресс-тесты. Они могут быть реализованы внешним образом, запуская две разные программы - одну
  со статической библиотекой с последовательной реализацией, вторую - с динамической библиотекой с параллельной
  реализацией, и сравнивая их выводы друг с другом.
- для организации ввода/вывода больших данных полезно работать с файлами, а в программе - предусмотреть работу с
  универсальными потоками входных/выходных данных (или хотя бы перенаправлять ввод/вывод на уровне их запуска)
- если в задании сказано, что программа должна обрабатывать файлы объёмом 100 Мб – это лишь ориентир, на которых
  программа точно должна работать, и на котором имеет смысл делать замеры производительности и эффективности алгоритмов.
  Поэтому тесты на такой объём должны быть. Однако сама программа должна уметь работать с произвольными размерами
  входных данных
- измерение времени должно осуществляться внешним образом, а не внутри кода библиотек. При этом необходимо делать
  несколько замеров и усреднять. Стоит помнить о том, что clock() в многопоточных приложениях работает не так, как
  ожидается.

# UPD

Время выполнения многопоточного и однопоточного алгоритма отличается на несколько дестяков миллисекунд в пользу
однопоточного, в то время как на моей машине время отличается в 3 раза в пользу многопоточной реализации, я так понимаю
GithubActions запускает пайплайн на одном физическом ядре, и вместо параллельных вычислений мы получаем накладные
расходы на работу с потоками
