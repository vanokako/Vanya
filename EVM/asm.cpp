#include <iostream>
#include <wchar.h>
int main()
{
	wchar_t s1[81], s2[81] = L"";
	std::cout << "Программа для удаления латинских букв и цифр из строки, разработал Медведев И.С." << std::endl;
	std::cout << "Введите строку:" << std::endl;
	fgetws(s1, 81, stdin);
	_asm {
		lea esi, s1
		lea edi, s2
		cycle :
			lodsw
			cmp ax, L'0'
			jl body
			cmp ax, L'9'
			jle end_cycle
			cmp ax, L'A'
			jl body
			cmp ax, L'z'
			jg body
			cmp ax, L'a'
			jge end_cycle
			cmp ax, L'Z'
			jle end_cycle
		body :

		    	stosw

		end_cycle :
			cmp ax, L'\0'
			loopnz cycle
	}
	wprintf(L"%s\n", s2);
	return 0;
}
