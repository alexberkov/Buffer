# Buffer
🔌 | 🪡 String processor with threads and sockets

## Краткое описание проекта:

Данный проект состоит из двух программ, взаимодействующих между собой при помощи сокетов. Первая программа создает клиента для отправки результатов 
работы на сервер, а далее запускает два потока. Первый поток проверяет и обрабатывает строку данных, после чего записывает результат в текстовый файл.
Второй поток считывает данные из этого файла, вычисляет результат и отправляет его на сервер. Вторая программа создает сервер, принимает результат первой
программы, проверяет его и выдает соответствующее сообщение

## Программные файлы:

### Buffer.h / .cpp

Класс буфер - основной класс первой программы. содержит поля s (строка данных) и access (модификатор доступа к файлу). Также содержит следующие методы:
- checkString - проверяет, что строка короче 64 символов и состоит только из букв и цифр.
- process - осуществляет пользовательский ввод строки, проверяет ее м помощью метода checkString, сортирует ее по убыванию и заменяет четные элементы 
на символы "KB", послк чего записывает ее в тектовый файл и меняет модификатор доступа, тем самым давая сигнал методу, вычисляющему результат.
- calculate - принимает сокет для взаимодействия со второй программой. Проверяет модификатор доступа и если он открыт, считывает данные из файла,
вычисляет сумму всех числовых значений и оправляет результат на указанный сокет, после чего меняет модификатор доступа обратно.

### main.cpp

Основной файл первой программы. Создает сокет и клиент, привязывет сокет к порту локального сервера, соединяет сокет и клиент. Далее создает объект 
класса Buffer и запускает два потока - один с методом process, другой с методом calculate.

### server.cpp

Основной файл второй программы. Создает объект сервера и сокет для приема сообщений от первой программы. Принимаемое занчение проверяет на минимальный 
размер и кратность 32 и выводит сообщение об ошибке, если проверка не пройдена, в противном случае - сообщение об успешной обработке данных.

## Другие файлы:

### CMakeLists.txt

Стандартный файл сборщика CMake. Подключение дополнительных библиотек не требуется.

### buffer.txt

Файл для хранения данных первой программы.
