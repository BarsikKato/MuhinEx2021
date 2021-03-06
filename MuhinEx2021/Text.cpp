// ответы на вопросы

/* Windows HOOK. Назначение и особенности использования.
// Что такое?
Windows HOOK любой код, который перехватывает или подменяет вызовы, сообщения и события производимые системами или приложениями
Техника использования HOOK называется перехват (hooking)
// Зачем?
Перехват может использоваться для отладки или расширения функционала различных функций (KEYLOGGER), так же перхват используется во вредоносном ПО
В пример HOOK можно назвать появление выпадающего меню при нажатии на рабочий стол

За установку HOOK отвечает функция SetWindowsHookEx
При помощи GetMessageW получаем список входящих системных событий (также данная функция заполняет структуру MSG)
*/

/*Актуальность синхронизации потоков при параллельной обработке данных
В случае когда два или более потоков пытаются получить одновременный доступ к какому-либо общему ресурсу (Например К данным в оперативной памяти),
Поведение программа может быть неверным. Значение может быть записано раньше времени или прочитана раньше времени.
Соответсвенно для нормальной работы приложения с ресурсами необходимо синхронизировать действия этих потоков
Синхронную  работу с ресурсами можно обеспечить при помощи критической секции

Критическая секция объявляется следующим образом:
-Создаётся Переменная соответствующего типа CRITICAL_SECTION section = { 0 };
-До начала выполнения потока необходимо инициализировать критическую секцию с помощью соответствующей функции: InitializeCriticalSection(&section);
-Участок кода,  да который контролируется критической секцией должен находиться между инструкциями EnterCriticalSection(&section); и LeaveCriticalSection(&section);
-После окончание работы потоков можно освободить критическую секцию с помощью функции DeleteCriticalSection(&section);
*/

/*Библиотеки DLL. Назначение и использование DLL-библиотек
DLL библиотека представляет из себя скомпилированное хранилище готовых функций,
которые затем могут быть использованны при разработки программ.
В основном они используются для того чтобы эффективно разместить функции, которые могут использоваться в большом кол-ве в различных программ
Также DLL экономит память (из-за того что не нужно писать одинаковые функции несколько раз в разных программах)

Для этого используются три основных шага:
-Подключается DLL. (Создается дескриптор данной библиотеки)
-Импортируется функция из этой библиотеки
-Освобождается память под дескриптор (Отключается библиотека)

Для импорта функции необходимо сначала создать указатель на функцию с сигнатурой.
Далее необходимо иициализировать данную функцию. (присвоив ей значение функции из DLL)

Есть ещё один прикол связанный с импортом библиотеки из WINapi в C# (в принципе всё тоже самое) для этого нужно
Объявить прототип функции. Для этого нужно:
-подключить пространство имён: using System.Runtime.InteropServices;
-Использовать атрибут [DllImport]. У этого атрибута есть несколько параметров, Они передаются внутри скобок ( как у метода)
-Нужно Правильно указать соглашение о вызовах в атрибуте [DllImport] импорт.  Дело в том что по умолчанию считается __stdcall, А у нас в библиотеке __cdecl
-Далее описать сигнатуру вызываемой функции dll. Только нужно заменить типы данных ( те,  те которые используются в Windows, на те, как которые Используются в языке си #)
*/

/* Именованные каналы. Назначение и использование
Каналы - область виртуального пространства,  которое может быть использовано для совместного доступа различными процессами.

Именованные каналы не существуют постоянно и не могут быть созданы как специальные файлы в произвольной доступной для записи файловой системе,
но имеют временные имена (освобождаемые после закрытия последней ссылки на них), которые выделяются в корне файловой системы именованных каналов
(англ. named pipe filesystem, NPFS) и монтируются по специальному пути «\.\pipe» (то есть у канала под названием «foo» полное имя будет «\.\pipe\foo»).
Анонимные каналы, использующиеся в конвейерах, — это на самом деле именованные каналы со случайным именем.

Процесс который создаёт канал это - сервер,  а процессы,  которые подключаются к каналу -  клиенты
Одно из разновидностей каналов является именнованый.
Дескриптор выступает в качестве идентификатора определённого ресурса
В качестве идентификатора именованного канала используются дискриптор и имя в виде строки

Перед работой с каналами нужно чтобы "сервер" создал (CreateNamedPipe ) его и
была проведена проверка на поодключения клиентов (ConnectNamedPipe) со стороны сервера.
*/

/*Линейный односвязный список. Особенности создания и примеры использования
Представляет из себя набор структур содержащих в себе какие либо прикладные значения и так же указатель на следующий эл. списка памяти.
Соответсвенно изменение указателя у одного эл. списка приведёт к изменению последовательности элементов в списке в целом.
Такие списки необходимы для рапределённого  хранение значений в памяти
Т.к. массивы распологают все значения в памяти последовательно, друг за другом в памяти может не всегда имется нужное кол-во неприрывно свободного пространства
Линейный однос. список решает эту проблему.

Поскольку ЛОС хранит только значение след. эл. последовательности, то значение его головного эл. нужно запоминать отдельно
У полседнего э. списка указатель на след. эл. = NULL
*/

/* Массив как тип данных. Особенности использования массивов при разработке программ на си
Данные - это информация, котрую можно приминить.
Тип данных - это то как данные подразделяются.
Одним из типов данных является массив. Фактически массив является указателем на последовательность элементов определенного типа.
Имя массива является указателем на первый элемент.
А объём памяти равен суммарному объему Всех элементов с учетом их типа.

С массивами в СИ можно работать несколькими способами:как с указателями и встроинным в язык методом работы с массивом
Встроенным методом работать проще потомучто при помощи него можно обращаться к любому эл. массива по порядковому номеру.
В таком случае не нужно запоминать голову массива. Однако у такого способа есть недостаток - отсутствует возможность создать массив с динамической размерностью.
Эту проблему решает метод работы с массивом как с указателем. В данном случае на нужное кол-во элементов нужно выделить память (и после использования не забыть её очистить).
*/

/*Многопоточный режим работы компьютера. преимущества использования многопоточности
Поток — это по сути последовательность инструкций (поток в отличие от процесса выполняется на процессоре и использует ресурсы процесса (не знаю зачем это, но живи с этим)).
Многопоточность - состоящее в том, что процесс, порождённый в операционной системе, может состоять из нескольких потоков, выполняющихся «параллельно»,
то есть без предписанного порядка во времени.

Есть два вида многопоточности: временная (когда в один момент времени выполняется только один поток) и одновременная
Т.е. однопроцессорные карлики только эмулируют многопоточность, а по факту там очередь.
Тогда как многопроцессорные звери выполняют несколько действий одновременно из-зи того что очереди 2 или более.

Приемущества:
-экономия времени за счёт распараллеливания задач;
-использование птоками единого адресного пространства для передачи данных между собой (внутри одного процесса);
-разделение ответсвенности за разные задачи между потоками одной программы (при ошмбки не надо перекомпилировать программу заново);
-удобство для рядового пользователя

Подробнее:
https://habr.com/ru/company/otus/blog/549814/
*/

/* Особенности использования строкового типа данных. Массивы строк
Строковые типы данных необходимы в первую очередь пользователю, нежели человеку. Строка – это массив символов, последним элементом которого является закрывающий ноль.
Ну хз, тоже самое что и про массивы (сказанно выше)
Можно добавить что массив состои из однобайтных символов типа char и при инициализации строки можно написать L, т.е. UNICODE (изначально находится в ASCII)
И да в языке СИ нет отдельного строкового типа данных
*/


/*Особенности настройки проекта и использования синтаксиса языка программирования при написании DLL-файла
Настройка:
-Свойство конфигурации / Набор символов / использовать Юникод
-С\С++/Предварительно откомпилированные заголовки / «Не использовать предварительно откомпилированные заголовки
-С\С++/Дополнительно/Компилировать как код С
-Компоновщик/Все параметры/ выставить подсистему Windows
Настроука для DLL:
Всё также кроме того что нужно Компилировать как С++ и во вкладке общие поставить что это Приложение dll

Точка входа у библиотеки своя и выглядит так:
BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}

Всем экспортируемые из DLL функции. Должны иметь специальные соглашения о вызовах _cdecl.
Также функции нужно пометить с помощью оператора: __declspec(dllimport) - для импортируемых и __declspec(dllexport)  - для экспортируемых функций.
Описываются сие приколы в прототипе функции
*/

/*Особенности разработки программ в WinAPI
API - описание способов, которыми одна компьютерная программа может взаимодействовать с другой программой.
WINapi - это такой интерфейс, который предоставляет Windows для выполнения определённых системных задач сторонними программами (т.е. видовс предоставляет нам инструменты для наших нужд).

Для работы с этими функциями нужно подключить библиотеку Windows.h
Далее появляются новые типы данных:
-Тип BYTE обозначает 8-разрядное беззнаковое символьное значение.
-Тип WORD — 16-разрядное беззнаковое короткое целое.
-Тип DWORD — беззнаковое длинное целое.
-Тип UINT — беззнаковое 32-разрядное целое.
-Тип LONG эквивалентен типу long.
-Тип BOOL обозначает целое и используется, когда значение может быть либо истинным, либо ложным.
-Тип LPSTR определяет указатель на строку.
-Тип LPCSTR определяет константный (const) указатель на строку.
-Тип HANDLE обозначает 32-разрядное целое, используемое в качестве дескриптора.
Дескриптор выступает в качестве идентификатора определённого ресурса
Также нужно использовать спец функцию для запуска приложений Windows:
int WINAPI WinMain(HINSTANCE hlnstance. // дескриптор, присваиваемый запущенному приложению
HINSTANCE hPrevInstance, // для совместимости с winl6. в Win32 не используется
LPSTR lpCmdLine. // указатель на командною строку, если приложение так запущено
int nCmdShow); // значение, которое может быть передано в функцию Show Window ()

После выполнение данного кода создаться процесс, который не имеет интерфейса. (для вывода и ввода информации используются файлы, канлы и т.д.)
и да надо настроить сие прикол
*/

/*Особенности разработки программ для работы с системными событиями использования мыши и клавиатуры.
Работа с системными событиями происходит при пмомщи HOOK.

Общие положения для клавиатуры и мыши:
Перед работой нужно создать дескрипторы типа HHOOK. Далее инициализируем их при помощи фугкции SetWindowsHookExW,
в которой нужно указать тип обрабатываемых событий (WH_KEYBOARD_LL - для клавиатуры) и функцию которая будет выполнятся при обработке события (все остальные не так важны)

Потом создаём структуру типа MSG (Содержит сведения о сообщениях из очереди сообщений потока.‎) и цикл while с условием GetMessageW (получает сообщения из текущего потока)
Можно ещё рассказать о TranslateMessage (переводит сообщения виртуальных клавиш в символьные сообщения) и DispatchMessageW (возвращает значение указанное поцедурой window) - хз если честно что это
И да в конце main нужно написть UnhookWindowsHookEx для удаления процедуры перехвата

Далее создаём функции спец вида, которые будут выполнятся при обработке события и в конце которой пишем CallNextHookEx (передаёт инфу след. крючку)

ДЛЯ КЛАВИАТУРЫ:
Особенности работы с клавиатурой заключаются в некоторых функциях и структурах: PKBDLLHOOKSTRUCT, LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0))),
GetKeyNameTextW, MapVirtualKey.

PKBDLLHOOKSTRUCT- содержит инфу о низкоуровневых событиях ввода и вывода
LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0))) - возвращает номер расскладки
MapVirtualKey - получение кода клавиши
GetKeyNameTextW - получение названия клавиши

ДЛЯ МЫШИ:
Особенности работы с мышью заключаются в некоторых  структурах: MSLLHOOKSTRUCT - содержит инфу о низкоуровневых событиях ввода и вывода

*/

/*Подходы к обработке исключений в программах WinAPI, написанных на си
Исключение - это событие, которое произошло во время выполнения программы, в результате совершения которого дальнейшее нормальное выполнение программы становится невозможным.
Обрабо́тка исключи́тельных ситуа́ций — механизм языков программирования, предназначенный для описания реакции программы на ошибки времени выполнения и другие возможные проблемы,
которые могут возникнуть при выполнении программы и приводят к невозможности дальнейшей отработки программой её базового алгоритма.
В WinAPI можно обрабатывать исключения с помощью возвращаемых значений, для этого используется условный оператор и предопределённые значения м библиотеки windows.h
Так же для этого можно использовать оператор switch
Пр:
if (RegGetValueW(HKEY_CURRENT_USER, L"MyParam", L"DwordParam", RRF_RT_ANY, &dataType, &v1, &dataLen) == ERROR_SUCCESS)
{
	printf("цифра %d\n", v1);
}
*/

/*Понятие “системное программирование”. предназначение и специфика системного программирования
Системой называется отношение двух множеств.  множество элементов и множество связей между этими элементами.
Программы называется набор инструкций,  понятных для конечного исполнителя.
Программный код -  это это зашифрованная версия программы; То есть набор инструкций, написанный на языке,  понятном постановщику задачи.
Программирование - Это процесс написания программного кода.
Системные программисты пишут программные коды для функционирования системы

В целом операционная система представляет из себя множество процессов. Каждый процесс это отдельно взятая запущенная программа
В ходе работы процессы потребляют ресурсы. Или, другими словами, ресурс -  это то,  что Необходимо процессу для работы
Для системного программирования часто доступна только ограниченное количество инструментов.
*/

/* Предназначение директив препроцессора и заголовочных файлов
Препроцессор - это программа, которая производит некоторые (иногда весьма значительные) манипуляции с первоначальным текстом программы перед тем, как он подвергается компиляции.
Команды для препроцессора называются директивами. Директивы начинаются с символа «#», в конце не ставится «;».

Список основных директив:
-#include. Вставляет содержимое из текстового файла (заголовочного) в то место, где прописана эта команда. Короче, позволяет использовать какие-то функции из заголовочных файлов в проге.
-#define. Имеет три основных применения:
o Инициализация параметров (Задание флагов). Используется преимущественно для условной компиляции.
o Задание констант. Используется в качестве альтернативы глобальным переменным (постоянные значения, которые ну никак не изменишь)
o Задание макроопределений (макросов) (заранее заданные команды или условия, маленькие функции)
-#undef. Отменяют задание параметра (противоположность define)
-#ifdef - Условие компиляции, если определённый параметр задан (если есть какой-то define)
-#ifndef - Условие компиляции, если определённый параметр не задан (если какого-то define нет)
-#if - Инициализация условной компиляции. Далее необходимо ввести условие, используя другие Директивы препроцессора.
-#elif - Директивы для создания вложенных условий (внутри основного #if)
-#else - Ветка при ложности всех условий. Её нельзя ставить выше, чем #elif
-#error - Внесение искусственной ошибки для компиляции (для теста, например)

Препроцессоры создают входной текст для компиляторов и могут выполнять следующие функции:
-обработку макроопределений;
-включение файлов;
-удаление экранированных символов перевода строки;
-замена строчных и блочных комментариев пустыми строками (с удалением окружающих пробелов и символов табуляции);
-расширение языка.
*/

/*Принципы взаимодействия операционной системы с прикладными программами (в том числе раскрыть понятия “процесс”, “поток”, “дескриптор”)
Дескриптор выступает в качестве идентификатора определённого ресурса
В ходе работы процессы потребляют ресурсы. Или, другими словами, ресурс -  это то,  что Необходимо процессу для работы.
Ресурсы бывают делимые и неделимые.
Неделимые могут быть использованы только одним процессом. Делимые используется несколькими процессами одновременно или параллельно.
Основные ресурсы,  необходимые для работы процессов:
-Потребление процессора.
Метрикой,  который отвечает за потребление процессора является процессор на и время. Процессорное время -  это количество тактов, которые необходимо для завершения процесса.
Однако на практике данные характеристика не является самой существенной. Гораздо важнее отслеживать процент загрузки процессора (Это-то Какое количество процессорного времени потребляет каждый процесс от максимально возможного)
-Потребление оперативной памяти.
Данный показатель измеряется в мегабайтах. С практической точки зрения важно именно количественное соотношение (Это связано с подходами к динамическому выделению памяти).

Процесс можно понимать как некий объект для исполняемого файла.  один и тот же исполняемый файл может быть запущен несколько раз (при этом создаётся несколько процессов).
Вся информация о процессе хранится в оперативной памяти.
Процесс характеризуется неким набором информации. За работу процессор отвечают потоки. Поток рассматривается как последовательный набор инструкций, Который выполняется на процессоре.Каждый процесс имеет хотя бы один поток.
Данный поток называется основным
Процессы могут находиться в одном из следующих состояний:
Выполняется. Основному потоку выделено процессорное время. Количество выполняемых процессов одновременно и не может быть больше,  чем Потоков,  который поддерживает процессор
Состояние готовности к выполнению. Процессу Предоставлены все ресурсы, кроме процессорного времени.
Состояние ожидания. Процессу предоставлены не все ресурсы (Например идёт ввод или вывод данных).
За время своего существования один и тот же процесс может многократно менять свои состояния.

ОС - комплекс взаимосвязанных программ, предназначенных для управления ресурсами компьютера и организации взаимодействия с пользователем.
Прикладная программа - программа, предназначенная для выполнения определённых задач и рассчитанная на непосредственное взаимодействие с пользователем
Прикладные программы запрашивают доступ к ресурсам. Взависимости от и приоретета ОС решает выделить ресурс программе или нет
*/

/*Принципы функционирования системного программного обеспечения
Системное программное обеспечение, в отличие от прикладного, функционирует без непосредственного вмешательства пользователя, на уровне операционной системы.
Такое ПО взаимодействует напрямую с ОС или еще ниже, с процессором и аппаратной составляющей ПК.

К системному ПО относят утилиты, драйвера, программы, встроенные в аппаратное оборудование.
Они, чаще всего, не взаимодействуют с пользователем и содержат инструкции, направленные к самой машине или ОС.
*/

/* Реестр Windows. использование системного реестра программами
Формально реестр представляет из себя базу данных.
Элементами этой базы данных являются параметры. Организация параметров представляет из себя иерархию.
Чаще всего реестр используется для хранения параметров операционной системы или прикладных программ.
Реестр задумывался как ниткой общее хранилище настроек. До этого программы хранили свои настройки в конфигурационных файлах (или файлах инициализации).
Использование конфигурационных файлов имела ряд недостатков:
-Не было централизованного хранилища этих файлов.
-Проблема защиты файлов:
--Текстовые файлы можно было удалить
--Можно было изменить содержимое текстовых файлов по-своему ведому

Сам реестр имеет 5 глобальных веток:
-HKEY CLASSES ROOT— хранится информация о зарегистрированных классах, расширениях документов;
-HKEY CURRENT USER — хранится информация о текущей пользовательской конфигурации, внешнем виде рабочего стола, сетевых настройках;
-HKEY LOCAL MACHINE — хранится информация о системной и аппаратной конфигурации;
-HKEY USERS — хранится информация обо всех зарегистрированных пользователях;
-HKEY_CURRENT_CONFIG — текущая аппаратная конфигурация.

Параметры также имеют свои определенные типы:
-Строковый параметр. Содержит последовательность символов в определенной кодировке. Его идентификатор в системе REG_SZ
-Двоичный параметр. По сути содержит массив байт. Его идентификатор в системе REG_BINARY
-Машинное слово для 32-битных систем. Его идентификатор в системе REG_DWORD
-Машинное слово для 64 разрядной системы. Его идентификатор в системе REG_QWORD
-Мультистроковый параметр.  другими словами массив строк. Его идентификатор в системе REG_MULTI_SZ
-Расширяемый строковый параметр. По сути представляет из себя строку переменной длины. REG_EXPAND_SZ

Программ взаимодействует с реестром при помощи интерфейса WINapi.
Дескрипторов ключа реестра является переменная типа HKEY. Для открытия ключа реестра используется функция RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey)
Она возвращает числовое значение (которое интерпретируется как код). Код успешного завершения этой функции определяется макросом ERROR_SUCCESS
Так же можно удалять создавать записывать данные в параметры различного вида.
*/

/*Системный буфер обмена. особенности взаимодействия программного обеспечения с системным буфером обмена
Системный буфер обмена — это область памяти, предоставляемая операционной системой для временного хранения тех или иных данных.
Несмотря на все удобства,  именованные каналы имеют ряд недостатков:
-Канал не может функционировать без сервера (Если программа сервер завершится,  то канал закроется);
-Доступ к каналу нужно специально организовывать из программного кода.
Одним из решений данной проблемы является использование системного буфер обмена.

По сути буфер обмена можно рассматривать как канал или глобальный указатель,  к которому имеют доступ все прикладные программы.
Однако при работе с буфером следует учитывать и его недостатки:
-Буфер обмена только один в системе.  и любое приложение может его перезаписать. Поэтому нет гарантии целостности получения данных
-Информация не может быть приватной (Во сколько буфер обмена доступен всем)
Буфер обмена на позволяет хранить данные различных типов.  Однако при работе с ним программы учитывают этот контекст.
В зависимости от формата данных в буфере с ним могут взаимодействовать те или иные приложения.
Буфер обмена – это простой способ приложениям обмениваться данными, не записывая их в файлы.

У буфера нет своей заранее выделенной области. Поэтому память выделяется в самой программе.
пр. в у Мухина
*/

/*Создание процессов. Функция запуска. Аргументы командной строки
Процесс можно понимать как некий объект для исполняемого файла. Один и тот же исполняемый файл может быть запущен несколько раз (при этом создаётся несколько процессов).
Вся информация о процессе хранится в оперативной памяти.

При создании процесса в него могут быть переданы аргументы.
Для этого необходимо правильным образом описать функцию запуска
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	for (size_t i = 0; i < argc; i++)
	{
		std::cout << argv[i] << "\n";
	}
}
Аргументы представляет из себя массив строковых значений. В примере показано,  как их вывести на экран.
Первым аргументом ( с индексом 0)  является имя исполняемого файла.

При создании процесса создаётся также его дескриптор,  который является структурой,  содержащий всю необходимую информацию о процессе.
Основной поток в процессе может также порождать и вспомогательные потоки.
Они нужны для параллельного выполнения операций. Желательно,  чтобы данные,  которые используют различные потоки не взаимодействовали между собой.
Создать процесс можно при помощи функции CreateProcess а его закрытие делается с помощью TerminateProcess.

Аргумент командной строки — это информация, которая вводится в командной строке операционной системы вслед за именем программы.
Чтобы принять аргументы командной строки, используются два специальных встроенных аргумента: argc и argv .
В массиве argv помещены аргументы командной строки, а в argc кол-во этих аргументов.
*/

/* Структура системного реестра. Типы данных в системном реестре.
Формально реестр представляет из себя базу данных.
Элементами этой базы данных являются параметры. Организация параметров представляет из себя иерархию.
Реестр задумывался как ниткой общее хранилище настроек.

Сам реестр имеет 5 глобальных веток:
-HKEY CLASSES ROOT— хранится информация о зарегистрированных классах, расширениях документов;
-HKEY CURRENT USER — хранится информация о текущей пользовательской конфигурации, внешнем виде рабочего стола, сетевых настройках;
-HKEY LOCAL MACHINE — хранится информация о системной и аппаратной конфигурации;
-HKEY USERS — хранится информация обо всех зарегистрированных пользователях;
-HKEY_CURRENT_CONFIG — текущая аппаратная конфигурация.

Параметры также имеют свои определенные типы:
-Строковый параметр. Содержит последовательность символов в определенной кодировке. Его идентификатор в системе REG_SZ
-Двоичный параметр. По сути содержит массив байт. Его идентификатор в системе REG_BINARY
-Машинное слово для 32-битных систем. Его идентификатор в системе REG_DWORD
-Машинное слово для 64 разрядной системы. Его идентификатор в системе REG_QWORD
-Мультистроковый параметр.  другими словами массив строк. Его идентификатор в системе REG_MULTI_SZ
-Расширяемый строковый параметр. По сути представляет из себя строку переменной длины. REG_EXPAND_SZ
*/

/*Структуры данных. актуальность использования структур. передача структуры как параметра.
Структура — это объединение нескольких объектов, возможно, различного типа под одним именем, которое является типом структуры.
Структуры позволяют трактовать группу связанных между собой объектов не как множество отдельных элементов, а как единое целое.
Структура представляет собой сложный тип данных, составленный из простых типов.

Структуры предоставляют возможность хранения большого количества различных значений, объединенных одним общим названием.
Это делает программу более модульной, что в свою очередь позволяет легко изменять код, потому что он становится более компактным.
Структуры, как правило, используют тогда, когда в программе есть много данных и их нужно сгруппировать вместе — например, такие данные могут использоваться для хранения записей из базы данных.
ПР: ЛОС, представить строку БД как структуру

Структура как прараметр передаётся как обычная переменная.
*/


/*Типы данных в ОС Windows
Далее появляются новые типы данных:
-Тип BYTE обозначает 8-разрядное беззнаковое символьное значение.
-Тип WORD — 16-разрядное беззнаковое короткое целое.
-Тип DWORD — беззнаковое длинное целое.
-Тип UINT — беззнаковое 32-разрядное целое.
-Тип LONG эквивалентен типу long.
-Тип BOOL обозначает целое и используется, когда значение может быть либо истинным, либо ложным.
-Тип LPSTR определяет указатель на строку.
-Тип LPCSTR определяет константный (const) указатель на строку.
-Тип HANDLE обозначает 32-разрядное целое, используемое в качестве дескриптора.
*/


/*Указатель как тип данных. особенности работы с указателями
Указатель представляет из себя переменную,  значением которой является адрес другой переменной.
Под указатель тоже выделяется место в оперативной памяти. Количество байт = разрядности программы.
Переменные однозначно идентифицируется двумя параметрами: Это её адрес (Номер 1 ячейки памяти) и Количество занимаемых ячеек.

К указателям применима операции сложения и вычитания. Они интерпретируются как сдвиги на определённое количество ячеек памяти.
Шаг равен количество байтов,  на которые ссылается указатель.

Для того чтобы начать работать с указателями нужно выделить память.
Для того чтобы создать указатель нужно поставить звёздочку после типа данных
Чтобы получить указатель от переменной нужно перед ним поставить &
*/

/*Указатель на функцию. Назначение и примеры использования
Указатель представляет из себя переменную,  значением которой является адрес другой переменной.
Указатели можно передавать как аргументы функции.  Также Функция может возвращать указатель
Для создания указателя на функцию нужно прописать: тип (*имя_указателя) (параметры);

Чтобы во время выполнения программы при разных условиях использовалися различные функции

ПР: делегаты
*/

/*Файл как тип данных. Использование файлов в работе программного обеспечения
Под файловым типом данных (файлом) понимается упорядоченная совокупность любого количества компонент одного типа. Понятие файла носит широкий характер.
В качестве файла может выступать обычный файл, который хранится на жестком диске, либо коммуникационный порт компьютера, устройство печати, клавиатура и т.д.

Чаще всего, файлы используются для хранения или обмена данными между разными программами.
Если на файл не наложены ограничения, каждая программа может открыть его, просмотреть данные, записать свои, или удалить их.
*/

/*Функции для работы с файлами WinAPI. Синхронный и асинхронный доступ к файлу.
За создание дескриптора файла отвечает функция Createfile
HANDLE CreateFile(указатель на имя файла (устройства),
параметры доступа (можно ли читать и/или писать),
разделяемый доступ (можно ли вместе читать и/или писать),
безопасность (NULL по умолчанию), описание открытия (открыть готовый, создать новый и т.п.), атрибуты файла (FILE_ATTRIBUTE_NORMAL по умолчанию),
файл шаблона (NULL если он не нужен));

Так же можно записывать данные в файл и считывать данныые из файла

После работы с файлом нужно закрыть открытый объект типа HANDLE (CloseHandle())

При асинхронном доступе к файлу поток продолжит выполнение, даже если чтение или запись в файл еще не закончилась.
Синхронный – наоборот, соответственно, поток продолжит выполнение после того, как взаимодействие с файлом закончится.
Чтобы активировать асинхронный режим нужно во флаге "чтения" или "записи" написать FILE_FLAG_OVERLAPPED
для синхронного NULL
*/
