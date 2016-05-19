#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>
#include <commctrl.h>

HWND Permise,Inregistrare_Permis_Nou, Inoire_Permis, Suspendarea_Permisului, Anulare_Permis;
HWND Titlul_main_window, Exit;
HWND Help, hPermise, hAfisare, hEditare_Permis;
HWND Afisare, Gasire_Rapida, Permise_inactive, Categoria_de_Permis;
HWND Editare_Permis, Valabilitate, Puncte_Amenda, Categorie;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,WPARAM wParam, LPARAM lParam) 
{

	switch (msg) {

	case WM_CREATE:
		{
					    Permise = CreateWindow("BUTTON", "Permise", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 152, 75, 30, hwnd, (HMENU)0, NULL, NULL);
						Inregistrare_Permis_Nou = CreateWindow("BUTTON", "Inregistrare Permis Nou", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 100, 175, 30, hwnd, (HMENU)1, NULL, NULL);
						Inoire_Permis = CreateWindow("BUTTON", "Inoire Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 137, 115, 30, hwnd, (HMENU)2, NULL, NULL);
						Suspendarea_Permisului = CreateWindow("BUTTON", "Suspendare Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 165, 174, 145, 30, hwnd, (HMENU)3, NULL, NULL);
						Anulare_Permis = CreateWindow("BUTTON", "Anulare Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 175, 211, 125, 30, hwnd, (HMENU)4, NULL, NULL);
						
						Titlul_main_window = CreateWindow("STATIC", TEXT("Manager Permise-Auto"), WS_CHILD | WS_VISIBLE | SS_LEFT, 250, 35, 175, 30,hwnd, NULL, NULL, NULL);
						
						Help = CreateWindow("BUTTON", "Help", WS_VISIBLE | WS_CHILD | WS_BORDER, 390, 300, 65, 30, hwnd, (HMENU)30, NULL, NULL);
						hPermise = CreateWindow("BUTTON", "Permise", WS_VISIBLE | WS_CHILD | WS_BORDER, 485, 263, 80, 30, hwnd, (HMENU)31, NULL, NULL);
						hAfisare = CreateWindow("BUTTON", "Afisare", WS_VISIBLE | WS_CHILD | WS_BORDER, 485, 300, 80, 30, hwnd, (HMENU)32, NULL, NULL);
						hEditare_Permis = CreateWindow("BUTTON", "Editare Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 465, 337, 120, 30, hwnd, (HMENU)33, NULL, NULL);

						Afisare = CreateWindow("BUTTON", "Afisare", WS_VISIBLE | WS_CHILD | WS_BORDER, 390, 152, 75, 30, hwnd, (HMENU)10, NULL, NULL);
						Gasire_Rapida = CreateWindow("BUTTON", "Gasire Rapida", WS_VISIBLE | WS_CHILD | WS_BORDER, 482, 115, 125, 30, hwnd, (HMENU)11, NULL, NULL);
						Permise_inactive = CreateWindow("BUTTON", "Permise Inactive", WS_VISIBLE | WS_CHILD | WS_BORDER, 482, 152, 125, 30, hwnd, (HMENU)12, NULL, NULL);
						Categoria_de_Permis = CreateWindow("BUTTON", "Categorie Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 482, 189, 125, 30, hwnd, (HMENU)13, NULL, NULL);

						Editare_Permis = CreateWindow("BUTTON", "Editare Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 300, 115, 30, hwnd, (HMENU)20, NULL, NULL);
						Valabilitate = CreateWindow("BUTTON", "Valabilitate", WS_VISIBLE | WS_CHILD | WS_BORDER, 188, 263, 90, 30, hwnd, (HMENU)21, NULL, NULL);
						Puncte_Amenda = CreateWindow("BUTTON", "Puncte-Amenda", WS_VISIBLE | WS_CHILD | WS_BORDER, 175, 300, 120, 30, hwnd, (HMENU)22, NULL, NULL);
						Categorie = CreateWindow("BUTTON", "Categorie", WS_VISIBLE | WS_CHILD | WS_BORDER, 191, 337, 80, 30, hwnd, (HMENU)22, NULL, NULL);

						Exit = CreateWindow("BUTTON", "Iesire", WS_VISIBLE | WS_CHILD | WS_BORDER, 270, 400, 80, 30, hwnd, (HMENU)9999, NULL, NULL);

						ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
						ShowWindow(Inoire_Permis, SW_HIDE);
						ShowWindow(Suspendarea_Permisului, SW_HIDE);
						ShowWindow(Anulare_Permis, SW_HIDE);

						ShowWindow(Gasire_Rapida, SW_HIDE);
						ShowWindow(Permise_inactive, SW_HIDE);
						ShowWindow(Categoria_de_Permis, SW_HIDE);

						ShowWindow(Valabilitate, SW_HIDE);
						ShowWindow(Puncte_Amenda, SW_HIDE);
						ShowWindow(Categorie, SW_HIDE);

						ShowWindow(hPermise, SW_HIDE);
						ShowWindow(hAfisare, SW_HIDE);
						ShowWindow(hEditare_Permis, SW_HIDE);
					
	}; break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

			case 9999:
			{
						int rezult = MessageBox(hwnd, "Esti sigur?", "~Iesire din aplicatie~", MB_YESNO);
						if (rezult == IDYES)
						ExitProcess(0);
						
			}; break;

			case 0:
			{
					  ShowWindow(Inregistrare_Permis_Nou, SW_SHOW);
					  ShowWindow(Inoire_Permis, SW_SHOW);
					  ShowWindow(Suspendarea_Permisului, SW_SHOW);
					  ShowWindow(Anulare_Permis, SW_SHOW);
			}; break;

			 case 1:
			 {
				 MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Incarcare permis", MB_OK);
				 ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
				 ShowWindow(Inoire_Permis, SW_HIDE);
				 ShowWindow(Suspendarea_Permisului, SW_HIDE);
				 ShowWindow(Anulare_Permis, SW_HIDE);
			 }; break;
					
			 case 2:
			 {
					   MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Inoire permis", MB_OK);
					   ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
					   ShowWindow(Inoire_Permis, SW_HIDE);
					   ShowWindow(Suspendarea_Permisului, SW_HIDE);
					   ShowWindow(Anulare_Permis, SW_HIDE);
			 }; break;

			 case 3:
			 {
					   MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Suspenda permis", MB_OK);
					   ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
					   ShowWindow(Inoire_Permis, SW_HIDE);
					   ShowWindow(Suspendarea_Permisului, SW_HIDE);
					   ShowWindow(Anulare_Permis, SW_HIDE);
			 }; break;

			 case 4:
			 {
					   MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Anulare permis", MB_OK);
					   ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
					   ShowWindow(Inoire_Permis, SW_HIDE);
					   ShowWindow(Suspendarea_Permisului, SW_HIDE);
					   ShowWindow(Anulare_Permis, SW_HIDE);
			 }; break;

			 case 30:
			 {
						ShowWindow(hPermise, SW_SHOW);
						ShowWindow(hAfisare, SW_SHOW);
						ShowWindow(hEditare_Permis, SW_SHOW);
			 }; break;

			 case 31:
			 {
						MessageBox(hwnd, "Inregistrare Permis Nou - In data de baza se va insera un nou permis (nod) .\n\nAnulare Permis - Permisul se va elimina din data de baza din cauza unei infractiuni (stergerea nodului) .\n\nInoire Permis - La o anumita perioada se va reinoi deoarece expira perioada de valabilitate (o anumita caracteristica a nodului se va modifica) .\n\nSuspendarea Permisului - La acumularea unui anumit numar de puncte permisul devine inactiv (se elimina temporar dar se retine intr-un nod intermediar ,pana la trecerea unei perioade de timp ,urmand sa se reintroduca la validare ).", "Help - Permise", MB_OK);
						ShowWindow(hPermise, SW_HIDE);
						ShowWindow(hAfisare, SW_HIDE);
						ShowWindow(hEditare_Permis, SW_HIDE);
			 }; break;

			 case 32:
			 {
						MessageBox(hwnd, "Gasire Rapida - Se va afisa permisul (nodul cautat) impreuna cu toate caracteristicile acestuia : \n\t\t\t->numarul permisului;\n\t\t\t->valabilitatea (exprimata in luni);\n\t\t\t->numarul de puncte-amenda;\n\t\t\t->categoria.\n\nPermise Inactive - Se afiseaza permisele (nodurile) care nu mai sunt valide (care au valabilitatea egala cu 0 ) .\n\nCategorie Permis - Se afiseaza permisele (nodurile) dupa o anumita categorie .", "Help - Afisare", MB_OK);
						ShowWindow(hPermise, SW_HIDE);
						ShowWindow(hAfisare, SW_HIDE);
						ShowWindow(hEditare_Permis, SW_HIDE);
			 }; break;

			 case 33:
			 {
						MessageBox(hwnd, "Valabilitatea - Prin aceasta optiune se va accesa permisul (nodul) si se va modifica valabilitatea acestuia.\n\nPuncte-Amenda - Prin aceasta optiune se va accesa permisul (nodul) si se va modifica numarul de puncte-amenda.\n\nCategorie - Prin aceasta optiune se va accesa permisul (nodul) si se va modifica Categoria acestuia.\n\n", "Help - Editare Permis", MB_OK);
						ShowWindow(hPermise, SW_HIDE);
						ShowWindow(hAfisare, SW_HIDE);
						ShowWindow(hEditare_Permis, SW_HIDE);
			 }; break;




			 case 10:
			 {
						ShowWindow(Gasire_Rapida, SW_SHOW);
						ShowWindow(Permise_inactive, SW_SHOW);
						ShowWindow(Categoria_de_Permis, SW_SHOW);
			 }; break;

			 case 11:
			 {
					   MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Gasire Rapida", MB_OK);
					   ShowWindow(Gasire_Rapida, SW_HIDE);
					   ShowWindow(Permise_inactive, SW_HIDE);
					   ShowWindow(Categoria_de_Permis, SW_HIDE);
			 }; break;

			 case 12:
			 {
						MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Permise Inactive", MB_OK);
						ShowWindow(Gasire_Rapida, SW_HIDE);
						ShowWindow(Permise_inactive, SW_HIDE);
						ShowWindow(Categoria_de_Permis, SW_HIDE);
			 }; break;

			 case 13:
			 {
						MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Categorie Permis", MB_OK);
						ShowWindow(Gasire_Rapida, SW_HIDE);
						ShowWindow(Permise_inactive, SW_HIDE);
						ShowWindow(Categoria_de_Permis, SW_HIDE);
			 }; break;

			 case 20:
			 {					
						ShowWindow(Valabilitate, SW_SHOW);
						ShowWindow(Puncte_Amenda, SW_SHOW);
						ShowWindow(Categorie, SW_SHOW);
			 }; break;

			 case 21:
			 {
						MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Valabilitate", MB_OK);
						ShowWindow(Valabilitate, SW_HIDE);
						ShowWindow(Puncte_Amenda, SW_HIDE);
						ShowWindow(Categorie, SW_HIDE);
			 }; break;

			 case 22:
			 {
						MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Puncte Amenda", MB_OK);
						ShowWindow(Valabilitate, SW_HIDE);
						ShowWindow(Puncte_Amenda, SW_HIDE);
						ShowWindow(Categorie, SW_HIDE);
			 }; break;
			 
			 case 23:
			 {
				 MessageBox(hwnd, "Ne pare rau ,dar aceasta functie inca nu este implementata !", "Categorie Permis", MB_OK);
				 ShowWindow(Valabilitate, SW_HIDE);
				 ShowWindow(Puncte_Amenda, SW_HIDE);
				 ShowWindow(Categorie, SW_HIDE);
			 }; break;

		}

	}; break;

	case WM_DESTROY:


		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	MSG  msg;
	HWND hwnd;
	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Window";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName, L"Manager Permise-Auto",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 680, 480, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {

		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}