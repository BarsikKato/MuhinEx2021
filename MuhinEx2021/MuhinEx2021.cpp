#define _CRT_SECURE_NO_WARNINGS
#include "UserHeader.h"

//Пропущено 7, 16, 17, 22

//1. Запись и считывание строковых параметров в системный реестр
void StringReestr()
{
    HKEY hKey = NULL;
    if (RegCreateKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)
        return 1;
    else
        MessageBox(NULL, L"Ключ успешно создан.", L"Ок", MB_OK);

    if (RegSetValueExW(hKey, L"Mykeystring", NULL, REG_SZ, L"Я строковый параметр на экзамене", 33 * sizeof(WCHAR)) == ERROR_SUCCESS)
        MessageBox(NULL, L"Ключ успешно создан и ему присвоено значение", L"Ок", MB_OK);
    else
        MessageBox(NULL, L"Ошибка создания значения.", L"Не ок", MB_OK);

    LPWSTR DWValue = malloc(512);
    DWORD DataType = 0;
    DWORD DataLen = 512;
    if (RegGetValueW(hKey, NULL, L"Mykeystring", RRF_RT_ANY, &DataType, DWValue, &DataLen) == ERROR_SUCCESS)
        MessageBox(NULL, DWValue, L"Значение параметра", MB_OK);
    else
        MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
    free(DWValue);
}

//2. Запись и считывание числовых параметров в системный реестр
void DwordReestr()
{
    HKEY hKey = NULL;
    if (RegCreateKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)
        return 1;
    else
        MessageBox(NULL, L"Ключ успешно создан.", L"Ок", MB_OK);

    DWORD num = 2812;
    if (RegSetValueExW(hKey, L"Mykeydword", NULL, REG_DWORD, &num, sizeof(num)) == ERROR_SUCCESS)
        MessageBox(NULL, L"Ключ успешно создан и ему присвоено значение", L"Ок", MB_OK);
    else
        MessageBox(NULL, L"Ошибка создания значения.", L"Не ок", MB_OK);

    DWORD DWValue = 0;
    DWORD DataType = 0;
    DWORD DataLen = 512;
    if (RegGetValueW(hKey, NULL, L"Mykeydword", RRF_RT_ANY, &DataType, &DWValue, &DataLen) == ERROR_SUCCESS)
    {
        LPWSTR OutputString = malloc(16);
        swprintf(OutputString, 8, TEXT("%d"), DWValue);
        MessageBox(NULL, OutputString, L"Значение параметра", MB_OK);
        free(OutputString);
    }
    else
        MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
}

//3. Использование системного буфера обмена для передачи строковых значений между процессами
int ClipboardInputText(LPWSTR buffer)
{
    DWORD len;
    HANDLE hMem;
    len = wcslen(buffer) + 1;

    hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
    memcpy(GlobalLock(hMem), buffer, len * sizeof(LPWSTR));
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    return 0;
}

int ClipboardOutputText()
{
    LPWSTR mess = NULL;
    OpenClipboard(NULL);
    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
    mess = (LPWSTR)GlobalLock(hClipboardData);
    GlobalUnlock(hClipboardData);
    CloseClipboard();
    MessageBox(NULL, mess, L"Содержимое буффера обмена", MB_OK);
    return 0;
}

//LPWSTR message = L"Очередной текст";
//ClipboardInputText(message);
//ClipboardOutputText();

//4. Использование условных блоков для анализа значений, возвращаемых системной функцией
void BlockAnalysis()
{
    HKEY hKey = NULL;
    if (RegCreateKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)
        MessageBox(NULL, L"Не удалось создать ключ 1.", L"Ок", MB_OK);
    else
        MessageBox(NULL, L"Ключ 1 успешно создан.", L"Ок", MB_OK);

    if (RegCreateKeyW(HKEY_CURRENT_USER, NULL, NULL) != ERROR_SUCCESS)
        MessageBox(NULL, L"Не удалось создать ключ 2.", L"Ок", MB_OK);
    else
        MessageBox(NULL, L"Ключ 2 успешно создан.", L"Ок", MB_OK);
}

//5. Обработка нажатия клавиши мыши в системе(выписать в messagebox какая клавиша нажата и сколько раз)
DWORD lbC = 0, rbC = 0, mbC = 0, wsU = 0, wsD = 0;

LRESULT CALLBACK mouseProc(int iCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_LBUTTONDOWN)
    {
        lbC++;
        LPWSTR word = malloc(sizeof(WCHAR) * 64);
        wsprintf(word, L"Левая кнопка мыши нажата %d раз", lbC);
        MessageBox(NULL, word, L"Информация", MB_OK);
        free(word);
    }
    else if (wParam == WM_RBUTTONDOWN)
    {
        rbC++;
        LPWSTR word = malloc(sizeof(WCHAR) * 64);
        wsprintf(word, L"Правая кнопка мыши нажата %d раз", rbC);
        MessageBox(NULL, word, L"Информация", MB_OK);
        free(word);
    }
    else if (wParam == WM_MBUTTONDOWN)
    {
        mbC++;
        LPWSTR word = malloc(sizeof(WCHAR) * 64);
        wsprintf(word, L"Средняя кнопка мыши нажата %d раз", mbC);
        MessageBox(NULL, word, L"Информация", MB_OK);
        free(word);
    }
    else if (wParam == WM_MOUSEWHEEL)
    {
        MSLLHOOKSTRUCT* mouseInfo = (MSLLHOOKSTRUCT*)lParam;
        LPWSTR word = malloc(sizeof(WCHAR) * 64);
        if (HIWORD(mouseInfo->mouseData) < 32768)
        {
            wsU++;
            wsprintf(word, L"Колесико повернуто вверх %d раз", wsU);
            MessageBox(NULL, word, L"Информация", MB_OK);
        }
        else
        {
            wsD++;
            wsprintf(word, L"Колесико повернуто вниз %d раз", wsD);
            MessageBox(NULL, word, L"Информация", MB_OK);
        }
        free(word);
    }

    return CallNextHookEx(NULL, iCode, wParam, lParam);
}

void FifthMain()
{
    HHOOK hHook = SetWindowsHookExW(WH_MOUSE_LL, mouseProc, NULL, NULL);
    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hHook);
    return 0;
}

//6. Отправка и получение данных из именованного канала
int Client()
{
    system("chcp 1251");
    LPSTR  lpszPipeName = "\\\\.\\pipe\\MyPipe";	 

    BOOL flag_otvet = TRUE;
    char message[SIZE_BUFFER];
    DWORD size_buffer = SIZE_BUFFER;
    DWORD actual_written;
    LPSTR buffer;
    DWORD actual_readen;
    BOOL SuccessRead;
    while (TRUE)
    {

        char message[SIZE_BUFFER];
        HANDLE hNamedPipe = CreateFileA(
            lpszPipeName, GENERIC_READ | GENERIC_WRITE,
            0, NULL, OPEN_EXISTING, 0, NULL);
        DWORD dwMode = PIPE_READMODE_MESSAGE;
        BOOL isSuccess = SetNamedPipeHandleState(hNamedPipe, &dwMode, NULL, NULL);
        if (!isSuccess)
        {
            printf("сервер не отвечает\n");
            flag_otvet = TRUE;
        }
        else
        {	
            if (flag_otvet)
            {
                printf("введите сообщение для сервера:\n");
                gets(message);
                buffer = &message;
                WriteFile(hNamedPipe, buffer, size_buffer, &actual_written, NULL);
                flag_otvet = FALSE;
            }
            buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
            SuccessRead = ReadFile(hNamedPipe, buffer, SIZE_BUFFER, &actual_readen, NULL);
            if (SuccessRead)
            {
                printf("\nСервер пишет: ");
                printf(buffer);
                printf("\n");
                flag_otvet = TRUE;
            }
        }
        Sleep(100);
        CloseHandle(hNamedPipe);
    }

}

int Server()
{
    system("chcp 1251");
    HANDLE hNamedPipe;
    LPWSTR  lpszPipeName = "\\\\.\\pipe\\MyPipe";
    DWORD size_buffer = SIZE_BUFFER;
    LPSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
    char message[SIZE_BUFFER];
    BOOL Connected;
    DWORD actual_readen;
    BOOL SuccessRead;
    DWORD d = 0;
    while (TRUE)
    {
        hNamedPipe = CreateNamedPipeA(
            lpszPipeName,
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            SIZE_BUFFER,
            SIZE_BUFFER,
            INFINITE,
            NULL);
        Connected = ConnectNamedPipe(hNamedPipe, NULL);
        if (Connected)
        {
            SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
            if (SuccessRead)
            {
                printf("\nКлиент пишет: ");
                printf(buffer);
                printf("\n");
                printf("\nвведите сообщение для клиента:\n");
                gets(message);
                buffer = &message;
                WriteFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
            }
        }
        else
        {
            printf("\nКлиент отключился от сервера\n");
        }
        CloseHandle(hNamedPipe);
    }
}

//7. Получение кода клавиши в формате ASCII и использованием Windows HOOK
LRESULT CALLBACK GetKeyCode(int iCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN)
    {
        PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
        WORD KeyLayout = LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0)));
        DWORD iKey = MapVirtualKey(pHook->vkCode, NULL) << 16;
        if (!pHook->vkCode <= 1 << 5)
            iKey |= 0x1 << 24;
        WCHAR text[16];
        wsprintf(text, L"%d", pHook->vkCode);
        MessageBoxW(NULL, text, L"ok", MB_OK);
    }
    return CallNextHookEx(NULL, iCode, wParam, lParam);
}

void SixthMain()
{
    HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, GetKeyCode, NULL, NULL);
    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hHook);
    return 0;
}

//8. Получение названия клавиши с использованием функции GetKeyNameText(Windows HOOK)
#define SIZE_STR 20
#define RUS 1049
#define ENG 1033
#define PATH L"writefile.txt"

VOID WriteToFile(LPWSTR wstr)
{
    FILE* f = NULL;
    if (!_wfopen_s(&f, PATH, L"ab"))
    {
        fwrite(wstr, sizeof(WCHAR), wcslen(wstr), f);
        fclose(f);
    }
}

WCHAR EnToRus(WCHAR c)
{
    switch (c)
    {
    case L'q': return L'й'; break;
    case L'w': return L'ц'; break;
    case L'e': return L'у'; break;
    case L'r': return L'к'; break;
    case L't': return L'е'; break;
    case L'y': return L'н'; break;
    case L'u': return L'г'; break;
    case L'i': return L'ш'; break;
    case L'o': return L'щ'; break;
    case L'p': return L'з'; break;
    case L'[': return L'х'; break;
    case L']': return L'ъ'; break;
    case L'a': return L'ф'; break;
    case L's': return L'ы'; break;
    case L'd': return L'в'; break;
    case L'f': return L'а'; break;
    case L'g': return L'п'; break;
    case L'h': return L'р'; break;
    case L'j': return L'о'; break;
    case L'k': return L'л'; break;
    case L'l': return L'д'; break;
    case L';': return L'ж'; break;
    case L'\'': return L'э'; break;
    case L'z': return L'я'; break;
    case L'x': return L'ч'; break;
    case L'c': return L'с'; break;
    case L'v': return L'м'; break;
    case L'b': return L'и'; break;
    case L'n': return L'т'; break;
    case L'm': return L'ь'; break;
    case L',': return L'б'; break;
    case L'/': return L'.'; break;
    case L' ': return L' '; break;
    case L'`': return L'ё'; break;
    case L'\\': return L'\\'; break;
    case L'@': return L'\"'; break;
    case L'#': return L'№'; break;
    case L'$': return L';'; break;
    case L'^': return L':'; break;
    case L'&': return L'?'; break;
    case L'|': return L'/'; break;
    case L'Q': return L'Й'; break;
    case L'W': return L'Ц'; break;
    case L'E': return L'У'; break;
    case L'R': return L'К'; break;
    case L'T': return L'Е'; break;
    case L'Y': return L'Н'; break;
    case L'U': return L'Г'; break;
    case L'I': return L'Ш'; break;
    case L'O': return L'Щ'; break;
    case L'P': return L'З'; break;
    case L'{': return L'Х'; break;
    case L'}': return L'Ъ'; break;
    case L'A': return L'Ф'; break;
    case L'S': return L'Ы'; break;
    case L'D': return L'В'; break;
    case L'F': return L'А'; break;
    case L'G': return L'П'; break;
    case L'H': return L'Р'; break;
    case L'J': return L'О'; break;
    case L'K': return L'Л'; break;
    case L'L': return L'Д'; break;
    case L':': return L'Ж'; break;
    case L'"': return L'Э'; break;
    case L'Z': return L'Я'; break;
    case L'X': return L'Ч'; break;
    case L'C': return L'С'; break;
    case L'V': return L'М'; break;
    case L'B': return L'И'; break;
    case L'N': return L'Т'; break;
    case L'M': return L'Ь'; break;
    case L'<': return L'Б'; break;
    case L'>': return L'Ю'; break;
    case L'.': return L'.'; break;
    case L'№': return L'#'; break;
    case L'?': return L','; break;
    default: return c; break;
    }
}

BOOL IsCaps(void)
{
    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
        return TRUE;
    return FALSE;
}

LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN)
    {
        PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
        WORD KeyLayout = LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0)));
        DWORD iKey = MapVirtualKey(pHook->vkCode, NULL) << 16;
        if (!pHook->vkCode <= 1 << 5)
            iKey |= 0x1 << 24;
        LPWSTR KeyString = (LPWSTR)calloc(SIZE_STR + 1, sizeof(WCHAR));
        GetKeyNameText(iKey, KeyString, SIZE_STR);
        if (wcslen(KeyString) > 1)
        {
            WriteToFile(L"[");
            WriteToFile(KeyString);
            WriteToFile(L"]");
        }
        else
        {
            if (!IsCaps())
                KeyString[0] = tolower(KeyString[0]);
            if (KeyLayout == ENG)
            {

            }
            else if (KeyLayout == RUS)
            {
                KeyString[0] = EnToRus(KeyString[0]);
            }
            WriteToFile(KeyString);
        }
        free(KeyString);
    }
    return CallNextHookEx(NULL, iCode, wParam, lParam);
}

void SeventhMain()
{
    HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LogKey, NULL, NULL);
    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hHook);
    return 0;
}

//9. Программа для записи строки в системный буфер обмена
int ClipboardInputText2(LPWSTR buffer)
{
    DWORD len;
    HANDLE hMem;
    len = wcslen(buffer) + 1;

    hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
    memcpy(GlobalLock(hMem), buffer, len * sizeof(LPWSTR));
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    return 0;
}

//10. Программа для преобразования строки в число. Строка хранится в виде указателя LPWSTR
void LpwstrToFloat()
{
    LPWSTR str = L"356.14";
    char s[16];
    wcstombs(s, str, 16);
    double f = atof(s);
    printf("%f", f);
}

//11. Программа для преобразования числа в строку и склейки двух строк
void FloatToStr()
{
    system("chcp 1251>nul");
    double a = 156.371;
    
    char str1[16] = "Получено число:";
    char str2[16];
    sprintf(str2, "%.3f", a);

    int l1 = 0, l2 = 0;

    int len = strlen(str1) + (str2);
    char* fstr = malloc(len * sizeof(char));

    strcpy(fstr, str1);
    strcat(fstr, str2);

    printf("%s", fstr);
    free(fstr);
}

//12. Программа для считывания данных из системного буфера обмена
int ClipboardOutputText2() 
{
    LPWSTR mess = NULL;
    OpenClipboard(NULL);
    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
    mess = (LPWSTR)GlobalLock(hClipboardData);
    GlobalUnlock(hClipboardData);
    CloseClipboard();
    MessageBox(NULL, mess, L"Содержимое буффера обмена", MB_OK);
    return 0;
}

//13. Программа для считывания и записи строкового значения с использованием текстового файла
void ReadAndWriteFile()
{
    FILE* kvadrFile = fopen("read.txt", "r");
    FILE* answerFile = fopen("write.txt", "w");
    while (!feof(kvadrFile))
    {
        char str[64];
        if (fscanf(kvadrFile, "%s", &str) != 0)
        {
            fprintf(answerFile, "%s ", str);
        }
    }
    fclose(kvadrFile);
    fclose(answerFile);
}

//14. Программа для считывания нескольких числовых значений из строки и из записи в числовой массив(разделитель - пробел)
void ReadAndWriteFromString()
{
    float arr[16];
    char str[16] = "15 12 17 13 23";
    char* sep;
    sep = strtok(str, " ");
    int i = 0;
    while (sep != NULL)
    {
        arr[i] = atof(sep);
        sep = strtok(NULL, " ");
        i++;
    } 

    for (int j = 0; j < i; j++)
    {
        printf("%f\n", arr[j]);
    }
}

//15. Программа для считывания числового значения из файла(с сохранением его в числовом формате)
void ReadAndWriteNumbers()
{
    float arr[50];
    FILE* kvadrFile = fopen("read.txt", "r");
    int i = 0;
    while (!feof(kvadrFile))
    {
        float chislo;
        if (fscanf(kvadrFile, "%f", &chislo) != 0)
        {
            arr[i] = chislo;
        }
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        printf("%f\n", arr[j]);
    }
    fclose(kvadrFile);
}

//16. Программа с импортом функции из файла DLL

//17. Программа с использованием нескольких программных модулей(каждый модуль должен располагаться в отдельном файле.cpp)

//18. Программа с использованием пользовательских файлов заголовков
void HeaderTest()
{
    HelloWorld();
}

//////////////////////////////////////////////////////////////////////////
//19. Разработка программы для вычисления факториала в отдельном потоке.
#define N 15

DWORD WINAPI FACTORIAL1()
{
    long f = 1;
    for (int i = 1; i < N; i++)
    {
        f *= i;
        printf("[1] Факториал числа %d равен %d\n", i, f);
    }
    ExitThread(0);
}

DWORD WINAPI FACTORIAL2()
{
    long f = 1;
    for (int i = 1; i < N; i++)
    {
        f *= i;
        printf("[2] Факториал числа %d равен %d\n", i, f);
    }
    ExitThread(0);
}

VOID FactorialMain(VOID)
{
    system("chcp 1251<nul");
    HANDLE fThread[2];
    fThread[0] = CreateThread(NULL, 0, FACTORIAL1, NULL, 0, 0);
    fThread[1] = CreateThread(NULL, 0, FACTORIAL2, NULL, 0, 0);
    WaitForMultipleObjects(2, fThread, TRUE, INFINITE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//20. Разработка программы - секундомера. В одном потоке идет отсчет времени, а в другом осуществляется управление секундомером

int time[3] = { 0, 0 };

DWORD WINAPI WatchSec(LPVOID param)
{
    int m, s;
    while (1)
    {
        m = time[0];
        s = time[1];
        if (s < 60)
        {
            time[1]++;
        }
        if (s == 60 && m < 60)
        {
            time[0]++;
            time[1] = 0;
        }
        system("cls");
        printf("%02d %02d\n", m, s);
        Sleep(1000);
    }
    ExitThread(0);
}

DWORD WINAPI WatchButtonPressing(LPVOID param)
{
    int isWorking = 1;
    while (1)
    {
        switch (_getch())
        {
        case 'p':
            if (isWorking == 1)
            {
                SuspendThread(param);
                isWorking = 0;
            }
            else
            {
                ResumeThread(param);
                isWorking = 1;
            }
            break;
        case 's':
            ExitThread(0);
            break;
        case 'o':
            time[0] = 0;
            time[1] = 0;
            system("cls");
            break;
        }
    }
    ExitThread(0);
}

VOID SecMain(VOID)
{
    HANDLE Watch[2];
    Watch[0] = CreateThread(NULL, 0, WatchSec, time, 0, 0);
    Watch[1] = CreateThread(NULL, 0, WatchButtonPressing, Watch[0], 0, 0);
    WaitForMultipleObjects(2, Watch, TRUE, INFINITE);
}

/////////////////////////////////////////////////////////////////////////
//21. Cоздание и настройка проекта WinAPI. Вывод сообщения в messagebox

/*int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, L"Hello, world!", L"Сообщение", MB_OKCANCEL);
}*/

////////////////////////////////////
//22. Cоздание и отладка файла DLL


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//23. Cоздание консольной утилиты, которая печатает список переданных ей аргументов из командной строки

//E:\vsprojects\MuhinEx2021\Debug\MuhinEx2021.exe hello world examine 2021

int nemain(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);
    system("pause");
}

/////////////////////////////////////////////////////////////
//24. Cоздание линейного односвязного списка из n элементов//
/////////////////////////////////////////////////////////////
struct Element
{
    int a;
    struct Element* next;
};

typedef struct Element el;

//el* list = create(5);
//show(list);
//delete(list);

el* create(int n)
{
    el* start = malloc(sizeof(el));
    start->a = 1;
    start->next = NULL;
    el* currentEl, * nextEl;
    currentEl = start;
    for (size_t i = 0; i < n - 1; i++)
    {
        nextEl = malloc(sizeof(el));
        nextEl->a = currentEl->a + 1;
        currentEl->next = nextEl;
        currentEl = nextEl;
    }
    currentEl->next = NULL;
    return start;
}

void show(el* list)
{
    while (list)
    {
        printf("%d ", list->a);
        list = list->next;
    }
    printf("\n");
}

void delete(el* list)
{
    el* wList = list;
    while (wList)
    {
        wList = list->next;
        free(list);
        list = wList;
    }
}

///////////////////////////////////////////////
//25. Cоздание программы с критической секцией
CRITICAL_SECTION section = { 0 };
int chislo = 0;

DWORD WINAPI CritSection(LPVOID param)
{
    EnterCriticalSection(&section);
    for (size_t i = 0; i < 10; i++)
    {
        chislo++;
        printf("Поток - %d, значение - %d\n", *(int*)param, chislo);
    }
    LeaveCriticalSection(&section);
}

VOID Crit(VOID)
{
    system("chcp 1251>nul");
    HANDLE Threads[3];
    int t1 = 1, t2 = 2;
    InitializeCriticalSection(&section);
    Threads[0] = CreateThread(NULL, 0, CritSection, &t1, 0, 0);
    Threads[1] = CreateThread(NULL, 0, CritSection, &t2, 0, 0);
    WaitForMultipleObjects(2, Threads, TRUE, INFINITE);
    DeleteCriticalSection(&section);
}

/////////////////////////////////////////////////////////////////////////
//26. Cоздание функции, аргументом которой является указатель на функцию
int Slozh(int a, int b)
{
    int c = a + b;
    return(c);
}

int Vychet(int a, int b)
{
    int c = a - b;
    return(c);
}

void PointedFunc(int a, int b, int (*f)(int, int))
{
    printf("Выполняю...\n\n\n");
    printf("В результате сложных операций над %d и %d был получен ответ: %d\n", a, b, f(a, b));
    system("pause");
}

void FuncWithPointer()
{
    system("cls");
    system("chcp 1251>nul");
    int a, b, otv;
    void (*f)(int, int, int(int, int));
    int (*n)(int, int);
    f = PointedFunc;
    printf("Введите а: \n");
    scanf_s("%d", &a);
    printf("Введите b: \n");
    scanf_s("%d", &b);
    printf("1. Сложить a и b.\n2. Вычесть a и b.\n");
    scanf_s("%d", &otv);
    if (otv == 1)
        n = Slozh;
    else
        n = Vychet;
    printf("А теперь, за меня все сделает другая функция!\n\n\n");
    f(a, b, n);
}

///////////////////////
///       MAIN      ///
///////////////////////
int main()
{
    SixthMain();
}



