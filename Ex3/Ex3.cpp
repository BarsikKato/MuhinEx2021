#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

#define READPATH L"Users.csv"
#define WRITEPATH L"../Debug/Result.csv"
#define SIZE_BUFFER 100500

#define SEARCH L"Иван"

struct User
{
    LPWSTR f;
    LPWSTR i;
    LPWSTR o;
    DWORD vozr;
};
typedef struct User U;


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

DWORD LpwstrToDword(LPWSTR str)
{
	DWORD dw = 0;
	for (size_t i = 0; i < wcslen(str); i++)
	{
		dw += (str[i] - '0');
		dw *= 10;
	}
	return dw / 10;
}

DWORD CountUsers(LPWSTR str)
{
	DWORD count = 0;
	for (size_t i = 0; i < wcslen(str); i++)
		if (str[i] == L'\n') count++;
	return count;
}

LPWSTR FileRead(LPWSTR path)
{
	HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD byteRead = 0;
	LPWSTR str = calloc(SIZE_BUFFER, sizeof(WCHAR));
	if (ReadFile(hFile, str, SIZE_BUFFER * sizeof(WCHAR), &byteRead, NULL))
	{
		str[byteRead / 2] = '\0';
		if (byteRead == 0)
			MessageBox(NULL, L"Файл пустой или не существует.", L"Ошибка", MB_ICONERROR);
	}
	else
		MessageBox(NULL, L"Ошибка при чтении данных.", L"Ошибка", MB_ICONERROR);
	if (str != NULL)
	{
		CloseHandle(hFile);
		return str;
	}
	CloseHandle(hFile);
	return NULL;
}

DWORD AverageAge(U* users)
{
	int summ = 0, n = 0;
	while (users[n].vozr != NULL)
	{
		summ += users[n].vozr;
		n++;
	}
	DWORD average = summ / n;
	return average;
}

U* CreateUsersArray(LPWSTR path, LPDWORD count)
{
	LPWSTR str = FileRead(path);
	TCHAR* sn = L"\n";
	TCHAR* razd = L";";
	int n = CountUsers(str), k = 0;
	*count = n;
	U* data = calloc(n, sizeof(U));
	if (n != 0)
	{
		LPWSTR istr = calloc(n + 1, sizeof(WCHAR));
		LPWSTR token = wcstok(str, sn, istr);
		while (token != NULL && k < n)
		{
			LPWSTR strT = calloc(wcslen(token) + 1, sizeof(WCHAR));
			wcscpy(strT, token);
			LPWSTR jstr = calloc(wcslen(token) + 1, sizeof(WCHAR));
			LPWSTR tokenJ = wcstok(strT, razd, jstr);
			data[k].f = calloc(wcslen(tokenJ) + 1, sizeof(WCHAR));
			wcscpy(data[k].f, tokenJ);
			tokenJ = wcstok(NULL, razd, jstr);
			data[k].i = calloc(wcslen(tokenJ) + 1, sizeof(WCHAR));
			wcscpy(data[k].i, tokenJ);
			tokenJ = wcstok(NULL, razd, jstr);
			data[k].o = calloc(wcslen(tokenJ) + 1, sizeof(WCHAR));
			wcscpy(data[k].o, tokenJ);
			tokenJ = wcstok(NULL, L"\r", jstr);
			data[k].vozr = tokenJ != NULL ? LpwstrToDword(tokenJ) : 0;
			token = (LPWSTR)wcstok(NULL, sn, istr);
			free(strT);
			free(jstr);
			k++;
		}
		free(token);
		free(istr);
		return data;
	}
	return NULL;
}

U* SearchForUsers(LPWSTR search, U* userArr, DWORD k)
{
	int n = 0;
	U* foundUsers = calloc(k, sizeof(U));
	for (int i = 0; i < k; i++)
	{
		if (wcsstr(userArr[i].f, search))
		{
			foundUsers[n].f = calloc(wcslen(userArr[i].f) + 1, sizeof(WCHAR));
			wcscpy(foundUsers[n].f, userArr[i].f);
			foundUsers[n].i = calloc(wcslen(userArr[i].i) + 1, sizeof(WCHAR));
			wcscpy(foundUsers[n].i, userArr[i].i);
			foundUsers[n].o = calloc(wcslen(userArr[i].o) + 1, sizeof(WCHAR));
			wcscpy(foundUsers[n].o, userArr[i].o);
			foundUsers[n].vozr = userArr[i].vozr;
			n++;
		}
	}
	HANDLE hFile = CreateFile(WRITEPATH, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	TCHAR bufferStr[SIZE_BUFFER];
	LPWSTR writeStr = calloc(SIZE_BUFFER, sizeof(WCHAR));
	swprintf(bufferStr, SIZE_BUFFER, TEXT("%s;%s;%s;%d\r\n"), foundUsers[0].f, foundUsers[0].i, foundUsers[0].o, foundUsers[0].vozr);
	wcscpy(writeStr, bufferStr);
	for (int i = 1; i < n; i++)
	{
		swprintf(bufferStr, SIZE_BUFFER, TEXT("%s;%s;%s;%d\r\n"), foundUsers[i].f, foundUsers[i].i, foundUsers[i].o, foundUsers[i].vozr);
		wcscat(writeStr, bufferStr);
	}
	if (writeStr != NULL)
	{
		swprintf(bufferStr, SIZE_BUFFER, TEXT("Средний возраст пользователей: %d\n"), AverageAge(foundUsers));
		wcscat(writeStr, bufferStr);
		DWORD byteWrite = 0;
		WriteFile(hFile, writeStr, wcslen(writeStr) * sizeof(TCHAR), byteWrite, NULL);
	}
	CloseHandle(hFile);
	return foundUsers;
}


int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD n = 0;
	U* users = CreateUsersArray(READPATH, &n);
	U* finded = SearchForUsers(SEARCH, users, n);
	return 0;
}

