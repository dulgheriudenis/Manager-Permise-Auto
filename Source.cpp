#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>
#include<commctrl.h>
#include"resource.h"

HWND Permise,Inregistrare_Permis_Nou, Inoire_Permis,Anulare_Permis;
HWND Titlul_main_window, Exit;
HWND Help, hPermise, hAfisare, hEditare_Permis;
HWND Afisare, Gasire_Rapida, Permise_inactive, Categoria_de_Permis;
HWND Editare_Permis, Valabilitate, Puncte_Amenda, Categorie;
HANDLE Fundal;


FILE *OutStream = fopen("afisare_permise.txt", "w");

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct nod
	{
		int key;
		char *nume, *categorie;
		int valabilitate, puncte_amenda;
		int ech;
		nod *left;
		nod *right;

	};

nod *rad;

void afisare_preordine(HWND hwnd, nod *rad)
{
	FILE *OutStream = fopen("permise.txt", "a");
	if (rad != NULL )//&& rad->key != 0)
	{
		fprintf(OutStream, "%d ", rad->key);
		fprintf(OutStream, "%s ", rad->nume);
		fprintf(OutStream, "%d ", rad->valabilitate);		
		fprintf(OutStream, "%d ",rad->puncte_amenda);
		fprintf(OutStream, "%s\n", rad->categorie);
		afisare_preordine(hwnd,rad->left);
		afisare_preordine(hwnd,rad->right);
	}
}

void drum_maxim(nod* p, int &max, int lung)
{
	if (p != NULL)
	{
		drum_maxim(p->right, max, lung + 1);
		if ((p->left == NULL) && (p->right == NULL) && (max<lung))
			max = lung;
		drum_maxim(p->left, max, lung + 1);
	}
}

void calcul_factor_echilibru(nod *p)
{
	int h_left, h_right;
	h_left = 1; h_right = 1;
	if (p->left != NULL)
		drum_maxim(p->left, h_left, 1);
	else
		h_left = 0;
	if (p->right != NULL)
		drum_maxim(p->right, h_right, 1);
	else
		h_right = 0;
	p->ech = h_right - h_left;
}

nod *s_rot_right(nod *&p)
{
	nod *q;
	q = p->left;
	p->left = q->right;
	q->right = p;
	calcul_factor_echilibru(p);
	calcul_factor_echilibru(q);
	p = q;
	return p;
}

nod *s_rot_left(nod *&p)
{
	nod *q;
	q = p->right;
	p->right = q->left;
	q->left = p;
	calcul_factor_echilibru(p);
	calcul_factor_echilibru(q);
	p = q;
	return p;
}

nod *d_rot_right(nod *&p)
{
	p->left = s_rot_left(p->left);
	p = s_rot_right(p);
	return p;
}

nod *d_rot_left(nod *&p)
{
	p->right = s_rot_right(p->right);
	p = s_rot_left(p);
	return p;
}

nod* echilibrare(nod *&p){
	nod *w;
	calcul_factor_echilibru(p);//se calculeaza factorul de echilibru a nodului curent p
	if (p->ech == -2){// daca p nod este critic
		w = p->left; // atunci w este copilul stanga al lui p
		if (w->ech == 1)// si daca acesta are factorul de echilibru 1
			p = d_rot_right(p);// atunci se face dubla rotatie dreapta
		else//altfel se face o simpla rotatie dreapta
			p = s_rot_right(p);
	}
	else
	if (p->ech == 2){//daca p nod este critic
		w = p->right;//w este copilul dreapta al nodului curent p
		if (w->ech == -1)// si acesta are factorul de ech -1
			p = d_rot_left(p);//se face o dubla rotatie stanga
		else//altfel se face o simpla rotatie stanga
			p = s_rot_left(p);
	}
	return p;
}

nod *rezult = NULL;

nod* cautare(nod *p, char *nume)
{
	if (p == NULL)
	{
		return NULL;
	}
	else
	{
		if (strcmp(nume, p->nume) == 0)
		{
			rezult = p;
			return rezult;
		}
		else
		{
			cautare(p->left,nume);
			cautare(p->right, nume);
		}
	}
	return rezult;
}

nod* insereaza(nod *&p, int id, char *nume ,char *categorie,int valabilitate,int puncte_amenda)
{
	if (p == NULL) // daca nodul curent este NULL atunci
	{ 
		p = (nod *)malloc(sizeof(nod)); //se aloca spatiu pentru el in zona heap
		p->nume = (char *)malloc(strlen(nume)*sizeof(char));
		p->categorie = (char *)malloc(strlen(categorie)*sizeof(char));
		strcpy(p->nume, nume);
		strcpy(p->categorie,categorie);
		p->valabilitate = valabilitate;
		p->puncte_amenda = puncte_amenda;
		p->key = id; //informatia devine id
		p->ech = 0; // factorul de echilibru este 0 - nodul este echilibrat 
		p->right = NULL;// nodul se insereaza ca nod frunza
		p->left = NULL; //deci referintele catre copii sai sunt NULL
		return p;
	}
	else {
		if (id<p->key) //daca cheia care se doreste inserata este
			//mai mica ca valoare decat informatia din nodul curent
			p->left = insereaza(p->left, id, nume, categorie, valabilitate, puncte_amenda);// atunci se insereaza in subarborele stang al nodului curent
		else
		if (id>p->key) //altfel daca cheia care se va insera e mai mare decat informatia din nodul curent
			p->right = insereaza(p->right, id, nume, categorie, valabilitate, puncte_amenda); // atunci se va insera in subarborele drept
		else
			printf("Nodul exista deja! \n");
	}
	p = echilibrare(p);// daca intervin cazuri de dezechilibru se va echilibra subarborele sau chiar arborele
}

nod* stergere(nod *&p, int x)
{
	nod *q, *r, *w;
	if (p != NULL)// daca nodul curent este diferit de NULL
	if (x<p->key) //cheia care se doreste stearsa este mai mica decat informatia din nod
		p->left = stergere(p->left, x); // se cauta cheia de sters in subarborele stang al nodului curent
	else
	if (x>p->key) // daca cheia este mai mare
		p->right = stergere(p->right, x);// se cauta in subarborele drept
	else{
		//daca cheia este egala cu informatia din nodul curent
		q = p;//un nod q devine p
		if (q->right == NULL) // daca copilul drept al lui q eate NULL
			p = q->left;// atunci p devine q->stanga
		else
		if (q->left == NULL) //altfel daca copilul stang al lui q este NULL
			p = q->right;// p devine q->dreapta
		else{
			w = q->left;//altfel w este copilul stanga al lui q
			r = q;// r devine q
			if (w->right != NULL)// daca copilul drept al lui w nun este NULL
			{
				while (w->right != NULL){
					r = w;
					w = w->right;
				}
				p->key = w->key;
				q = w;
				r->right = w->left;
				r = p->left;
				w = w->left;
				if (r != NULL)
				while ((r != w) && (r != NULL)){
					r = echilibrare(r);
					r = r->right;
				}
			}
			else{
				p->key = w->key;
				p->left = w->left;
				q = w;
			}
		}
		delete(q);// se sterge q
	}
	if (p != NULL)
		p = echilibrare(p);// se echilibreaza p daca nu este NULL
	return p;
}

///////////////
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//!!!!!!!!!!!!!!!!!!!pentru iesirile din functii!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case IDC_BUTTON1:
			EndDialog(hwnd, IDC_BUTTON1);
			break;
		case IDC_BUTTON20:
			EndDialog(hwnd, IDC_BUTTON20);
			break;
		case IDC_BUTTON32:
			EndDialog(hwnd, IDC_BUTTON32);
			break;

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		case IDC_BUTTON21:
		{

							 char *nume2;
							 int lungime;
							 BOOL flag1;
							 lungime = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT22));
							 if (lungime == 0)
								 MessageBox(hwnd, "Nu ai completat campul!", "Eroare!", MB_OK);
							 else
							 {
								 nume2 = (char*)malloc(lungime + 1);
								 GetDlgItemText(hwnd, IDC_EDIT22, nume2, lungime + 1);



								 if (cautare(rad, nume2) == NULL)
									 MessageBox(hwnd, "Nu exista acest nume in baza de date!", "Eroare!", MB_OK);
								 else{


									 FILE *Stream = fopen("permise.txt", "r");
									 cautare(rad, nume2)->valabilitate = 60;

									 fclose(Stream);

									 afisare_preordine(hwnd,rad);

									 free(nume2);
									
									 EndDialog(hwnd, IDC_BUTTON21);
								 }
							 }
							 break;
		}

		case IDC_BUTTON31:
		{

							 char *nume3;
							 int lungime1;
							 BOOL flag;
							 lungime1 = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT30));
							 if (lungime1 == 0)
								 MessageBox(hwnd, "Nu ai completat campul!", "Eroare!", MB_OK);
							 else
							 {
								 nume3 = (char*)malloc(lungime1 + 1);
								 GetDlgItemText(hwnd, IDC_EDIT30, nume3, lungime1 + 1);

								 if (cautare(rad, nume3) == NULL)
									 MessageBox(hwnd, "Nu exista acest nume in baza de date!", "Eroare!", MB_OK);
								 else{
									 
									 FILE *Stream = fopen("permise.txt", "r");
									 stergere(rad,cautare(rad, nume3)->key);
									 afisare_preordine(hwnd,rad);
									 free(nume3);
									 fclose(Stream);
									 EndDialog(hwnd, IDC_BUTTON21);
								 }
							 }
							 break;
		}

		case IDC_BUTTON2:
		{
							int id1, valabilitate1, puncte_amenda1;
							char *nume1, *categorie1;
							int len1, len2, len3, len4, len5;
							BOOL flag;
							len1 = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT1));
							len2 = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT2));
							len3 = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT3));
							len4 = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT4));
							len5 = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT5));
							if (len1 == 0 || len2 == 0 || len3 == 0 || len4 == 0 || len5 == 0)
								MessageBox(hwnd, "Nu ai completat toate campurile!", "Eroare!", MB_OK);
							else
							{
								nume1 = (char*)malloc(len2 + 1);
								GetDlgItemText(hwnd, IDC_EDIT2, nume1, len2 + 1);
								categorie1 = (char*)malloc(len5 + 1);
								GetDlgItemText(hwnd, IDC_EDIT5, categorie1, len5 + 1);
								id1 = GetDlgItemInt(hwnd, IDC_EDIT1, &flag, FALSE);
								valabilitate1 = GetDlgItemInt(hwnd, IDC_EDIT3, &flag, FALSE);
								puncte_amenda1 = GetDlgItemInt(hwnd, IDC_EDIT4, &flag, FALSE);


								insereaza(rad, id1, nume1, categorie1, valabilitate1, puncte_amenda1);

								FILE *Stream = fopen("permise.txt", "a");
								fprintf(Stream, "%d %s %d %d %s\n", id1, nume1, valabilitate1, puncte_amenda1, categorie1);
								fclose(Stream);

								afisare_preordine(hwnd, rad);



								free(nume1);
								free(categorie1);
								
								MessageBox(hwnd, "Operatiune efectuata cu succes !", "Succes!", MB_OK);
								EndDialog(hwnd, IDC_BUTTON2);
								
							}

		}

			//////////
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void LoadMyImage()
{
	Fundal = LoadImageW(NULL, L"C:\\Users\\Denis Petrisor\\Documents\\Visual Studio 2013\\Projects\\Proiect permise Arbori AVL\\Proiect permise Arbori AVL\\WDF_801327.bmp", IMAGE_BITMAP, 660, 415, LR_LOADFROMFILE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,WPARAM wParam, LPARAM lParam) 
{
	HWND hsti;
	int k = 0;

	FILE *Stream = fopen("permise.txt", "r");
	int id, valabilitate, puncte_amenda;
	char buffer[100], nume[50], categorie[5], *p;

	while (!feof(Stream))
	{
		fgets(buffer, 100, Stream);
		k = 0;
		p = strtok(buffer, " \n");
		while (p)
		{
			switch (k)
			{
			
				case 0:
				{
						  id = atoi(p);
				};  break;
			
				case 1:
				{
						  strcpy(nume, p);
				}; break;
			
				case 4:
				{
						  strcpy(categorie, p);
				}; break;
			
				case 2:
				{
							valabilitate = atoi(p);
				}; break;
			
				case 3:
				{
							puncte_amenda = atoi(p);
				}; break;

			}

			p = strtok(NULL, " \n");
			k++;
		}

		insereaza(rad, id, nume, categorie, valabilitate, puncte_amenda);
		
	}
		FILE *qStream = fopen("permise.txt", "w");
	fclose(Stream);
	fclose(qStream);

	switch (msg) {

	case WM_CREATE:
		{
					  LoadMyImage();
					  hsti = CreateWindowW(L"Static", L"",WS_CHILD | WS_VISIBLE | SS_BITMAP, 0, 0, 660, 450, hwnd, NULL, NULL, NULL);

					  SendMessage(hsti, STM_SETIMAGE,(WPARAM)IMAGE_BITMAP, (LPARAM)Fundal);

					    Permise = CreateWindow("BUTTON", "Permise", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 152, 75, 30, hwnd, (HMENU)0, NULL, NULL);
						Inregistrare_Permis_Nou = CreateWindow("BUTTON", "Inregistrare Permis Nou", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 120, 175, 30, hwnd, (HMENU)1, NULL, NULL);
						Inoire_Permis = CreateWindow("BUTTON", "Inoire Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 157, 115, 30, hwnd, (HMENU)2, NULL, NULL);						
						Anulare_Permis = CreateWindow("BUTTON", "Anulare Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 174, 194, 125, 30, hwnd, (HMENU)4, NULL, NULL);
						

						Afisare = CreateWindow("BUTTON", "Afisare", WS_VISIBLE | WS_CHILD | WS_BORDER, 390, 152, 75, 30, hwnd, (HMENU)10, NULL, NULL);
						Gasire_Rapida = CreateWindow("BUTTON", "Gasire Rapida", WS_VISIBLE | WS_CHILD | WS_BORDER, 482, 115, 125, 30, hwnd, (HMENU)11, NULL, NULL);
						Permise_inactive = CreateWindow("BUTTON", "Permise Inactive", WS_VISIBLE | WS_CHILD | WS_BORDER, 482, 152, 125, 30, hwnd, (HMENU)12, NULL, NULL);
						Categoria_de_Permis = CreateWindow("BUTTON", "Categorie Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 482, 189, 125, 30, hwnd, (HMENU)13, NULL, NULL);

						Editare_Permis = CreateWindow("BUTTON", "Editare Permis", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 300, 115, 30, hwnd, (HMENU)20, NULL, NULL);
						Valabilitate = CreateWindow("BUTTON", "Valabilitate", WS_VISIBLE | WS_CHILD | WS_BORDER, 188, 263, 90, 30, hwnd, (HMENU)21, NULL, NULL);
						Puncte_Amenda = CreateWindow("BUTTON", "Puncte-Amenda", WS_VISIBLE | WS_CHILD | WS_BORDER, 175, 300, 120, 30, hwnd, (HMENU)22, NULL, NULL);
						Categorie = CreateWindow("BUTTON", "Categorie", WS_VISIBLE | WS_CHILD | WS_BORDER, 191, 337, 80, 30, hwnd, (HMENU)22, NULL, NULL);

						Exit = CreateWindow("BUTTON", "Iesire", WS_VISIBLE | WS_CHILD | WS_BORDER, 390, 300, 65, 30, hwnd, (HMENU)9999, NULL, NULL);

						ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
						ShowWindow(Inoire_Permis, SW_HIDE);
						ShowWindow(Anulare_Permis, SW_HIDE);

						ShowWindow(Gasire_Rapida, SW_HIDE);
						ShowWindow(Permise_inactive, SW_HIDE);
						ShowWindow(Categoria_de_Permis, SW_HIDE);

						ShowWindow(Valabilitate, SW_HIDE);
						ShowWindow(Puncte_Amenda, SW_HIDE);
						ShowWindow(Categorie, SW_HIDE);
	}; break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		 {
			case ID_HELP_PERMISE:
				MessageBox(hwnd, "Inregistrare Permis Nou - In data de baza se va insera un nou permis (nod) .\n\nAnulare Permis - Permisul se va elimina din data de baza din cauza unei infractiuni (stergerea nodului) .\n\nInoire Permis - La o anumita perioada se va reinoi deoarece expira perioada de valabilitate (o anumita caracteristica a nodului se va modifica) .", "Help - Permise", MB_OK);
			  break;

			case ID_HELP_AFISARE:
				MessageBox(hwnd, "Gasire Rapida - Se va afisa permisul (nodul cautat) impreuna cu toate caracteristicile acestuia : \n\t\t\t->numarul permisului;\n\t\t\t->valabilitatea (exprimata in luni);\n\t\t\t->numarul de puncte-amenda;\n\t\t\t->categoria.\n\nPermise Inactive - Se afiseaza permisele (nodurile) care nu mai sunt valide (care au valabilitatea egala cu 0 ) .\n\nCategorie Permis - Se afiseaza permisele (nodurile) dupa o anumita categorie .", "Help - Afisare", MB_OK);
				break;

			case ID_HELP_EDITAREPERMIS:
				MessageBox(hwnd, "Valabilitatea - Prin aceasta optiune se va accesa permisul (nodul) si se va modifica valabilitatea acestuia.\n\nPuncte-Amenda - Prin aceasta optiune se va accesa permisul (nodul) si se va modifica numarul de puncte-amenda.\n\nCategorie - Prin aceasta optiune se va accesa permisul (nodul) si se va modifica Categoria acestuia.\n\n", "Help - Editare Permis", MB_OK);
				break;
			case 9999:
			{
						int rezult = MessageBox(hwnd, "Esti sigur?", "~ Iesire din aplicatie ~", MB_YESNO);
						if (rezult == IDYES)
						ExitProcess(0);
						
			}; break;

			case 0:
			{
					  ShowWindow(Inregistrare_Permis_Nou, SW_SHOW);
					  ShowWindow(Inoire_Permis, SW_SHOW);
					  ShowWindow(Anulare_Permis, SW_SHOW);
			}; break;

			 case 1:
			 {
				int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc);
				if (ret == -1)
					MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			 
				 ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
				 ShowWindow(Inoire_Permis, SW_HIDE);
				 ShowWindow(Anulare_Permis, SW_HIDE);
			 }; break;

					
			 case 2:
			 {
					   int ret1 = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, AboutDlgProc);
					   if (ret1 == -1)
						   MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
					   
					   ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
					   ShowWindow(Inoire_Permis, SW_HIDE);
					   ShowWindow(Anulare_Permis, SW_HIDE);
			 }; break;

			 case 4:
			 {
					   int ret2 = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, AboutDlgProc);
					   if (ret2 == -1)
						   MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
					   ShowWindow(Inregistrare_Permis_Nou, SW_HIDE);
					   ShowWindow(Inoire_Permis, SW_HIDE);
					   ShowWindow(Anulare_Permis, SW_HIDE);
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
	fclose(OutStream);
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
	wc.lpszMenuName = (LPCWSTR) MAKEINTRESOURCE(IDR_MENU1);
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