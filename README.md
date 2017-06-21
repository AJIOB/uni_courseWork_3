# Проект "Библиотека"
[![Build status](https://ci.appveyor.com/api/projects/status/frioxp0k7kr48ysw/branch/master?svg=true)](https://ci.appveyor.com/project/AJIOB/uni-coursework-3/branch/master)  

Курсовой по КПиЯП. 3 семестр.

В проекте реализованы функции каталога книг с использовнием реальных ISBN номеров (происходит проверка на явно несуществующие). Работает только меню администратора. Присутствует возможность использования пользовательской системы.

## Для сборки вам понадобится:
* Microsoft Visual Studio 2010 и выше (проверялось на Microsoft Visual Studio 2010 SP1 Professional)

## Руководство пользователя (для собранной версии)

1. Минимальные системные требования  
* ОС Windows 7, 8, 8.1, 10 любой разрядности (x32 либо x64);  
* ОЗУ: 1 ГБ;  
* клавиатура.  

2. Рекомендуемые системные требования  
* ОС Windows 7, 8, 8.1, 10 любой разрядности (x32 либо x64);  
* ОЗУ: 2 ГБ и более;  
* клавиатура, мышь.  

3. Комплект поставляемого ПО  
В комплекте с поставляемым программным обеспечением (далее — ПО) должны быть:  
* исполняемый файл “library.exe”;  
* файл логов “librarylog.log”, находящийся по пути “<путь размещения программы>/project/logs/”;  
* файлы баз данных, которые размещаются по пути “<путь размещения программы>/project/dbs/”:  
    * copies.db
    * countries.db
    * publications.db
    * user.db
При отсутствии каких-либо файлов, пожалуйста, обратитесь к поставщику данной копии ПО либо свяжитесь с производителем по адресу <aleskandr9809@gmail.com>.

4. Первый запуск программы
Для запуска программы требуется:  
    1) проверить комплект поставляемого ПО;  
    2) запустить файл “library.exe”;  
![Рисунок 5.1 — Папка с программой](https://image.ibb.co/bZGVLa/course3_5_1.png)  
    3) Если после запуска вы увидели окно с текстом, отличным от рисунка ниже, пожалуйста свяжитесь с поставщиком данного ПО.  
![Рисунок 5.2 — Форма авторизации](https://image.ibb.co/fu7FmF/course3_5_2.png)  
    4) В качестве логина и пароля по умолчанию введите «1» (без кавычек). Пример ввода приведен на рисунке ниже;  
Внимание! При вводе любого пароля отображаются символы '*'. Так и должно быть.  
![Рисунок 5.3 — Пример ввода логина и пароля](https://image.ibb.co/cU3XYv/course3_5_3.png)  
    5) Если вы получили уведомление, как на рисунке ниже,  
![Рисунок 5.4 — Ошибочный ввод логина и пароля](https://image.ibb.co/n1p6tv/course3_5_4.png)  
или что-либо отличное от рисунка ниже, пожалуйста, обратитесь к поставщику ПО  
![Рисунок 5.5 — Главное меню](https://image.ibb.co/bUsRtv/course3_5_5.png)  
Внимание! Настоятельно рекомендуется сменить пароль для этого пользователя на какой-либо более защищенный.  

5. Как пользоваться программой
В данном пункте будут показаны некоторые примеры работы с программой.  
    1) Запустите программу из папки или используя ярлык;  
    2) Авторизуйтесь (введите правильные логин и пароль);  
    3) Выберите базу данных, с которой хотите поработать;  
    4) Выберите операцию, которую вы хотите сделать;  
    5) Введите данные, которые требуются для корректного выполнения операции, и подтвердите их;  
    6) Поздравляем, действие выполнено.  

6. «ЧаВо?» (Часто задаваемые вопросы)  
В данном разделе описаны часто задаваемые вопросы (В — вопрос, О — ответ).  

* В: Программа выдает ошибку: «Error when open log file». Что делать?  
О: Создайте файл «librarylog.log» в папке “<путь размещения программы>/project/logs/”;  

* В: Программа выдает ошибку: «Извините, вы ввели несуществующую комбинацию логина и пароля». Что делать?  
О: Возможно, вам сбросили пароль на версию «по умолчанию». В графы «Логин» и «Пароль» введите свой логин. Не забудьте сменить пароль. Если это не помогло, обратитесь к администратору ПО;  

* В: Были забыты/потеряны все пароли от аккаунта администраторов (или вовсе были удалены аккаунты). Что делать?  
О: В этом случае рекомендуется еще раз попробовать вспомнить хоть один пароль от аккаунта администратора. Если это не помогло, напишите об этом распространителю или производителю, и они вышлют вам стандартную версию баз. Внимание! При этом будут утрачены ВСЕ аккаунты, и их невозможно будет восстановить.  

* В: При попытке добавления нового издания появляется ошибка «Ошибка распознавания ISBN номера. Пожалуйста, повторите ввод». Что делать?  
О: Номер нужно вводить в том формате, в котором он дан в издании с соблюдением всех дефисов. Например, 978-985-533-538-3. Программа поддерживает как ISBN-10, так и ISBN-13 стандарты.