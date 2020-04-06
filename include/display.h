#ifndef _display_h
#define _display_h

/**
 * @file	display.h
 * @author	Radoslaw Krupka
 * @date	06-04-2020
 * @brief	Modul warstwy abstrakcji wyswietlacza.
 * @details	Modul stanowi wrapper biblioteki X11 ktora zostala wykorzystana w projekcie w celu dostarczenia zobrazowania
 *          uzytkownika. Utworzenie tego typu warstwy abstrakcji pozwala na zostosowaniu wysciowej formy biblioteki
 *          do aktualnych potrzeb projektowych oraz przyzwyczajen oraz nawykow programisty.
**/

/**
 * @brief	Utworzenie nowego okna
 * @param	size_x Rozmiar okna w plaszczyznie x.
 * @param	size_y Rozmiar okna w plaszczyznie y.
 * @param	name Nazwa okna.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu utworzenia nowego okna. Metoda tworzy nowa mape, kontekst oraz dokonuje ustawienia
 *          czcionki okna, oraz czysci wewnetrzna kolejke eventow. Metoda zostala zaczerpnieta z ogolnodostepnych
 *          zrodel internetowych.
**/
void d_open(int size_x, int size_y, const char * name);

/**
 * @brief	Ustawienie aktualnego koloru rysowania.
 * @param	r Wartosc skladowej R palety RGB.
 * @param	g Wartosc skladowej G palety RGB.
 * @param	b Wartosc skladowej B palety RGB.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu ustawienia aktualnego koloru (foreground). Zgodnie z zalozeniami biblioteki
 *          kolor staje sie kolorem aktywnym, i wszystko co zostanie narysowane po wywolaniu metody przedstawione jest w tym
 *          samym kolorze.
**/
void d_color(int r, int g, int b);

/**
 * @brief	Narysowanie pojedynczego pixela.
 * @param	pos_x Polozenie rysowanego pixela na plaszczyznie XY.
 * @param	pos_y Polozenie rysowanego pixela na plaszczyznie XY.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu narysowania pojedynczego pixela.
**/
void d_pixel(int pos_x, int pos_y);

/**
 * @brief	Narysowanie linni na ekranie wyswietlacza.
 * @param	start_x Wspolrzedna X punktu poczatkowego rysowanej linii.
 * @param	start_y Wspolrzedna Y punktu poczatkowego rysowanej linii.
 * @param	end_x Wspolrzedna X punktu koncowego rysowanej linii.
 * @param	end_y Wspolrzedna Y punktu koncowego rysowanej linii.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu narysowania linni na ekranie wyswietlacza.
**/
void d_line(int start_x, int start_y, int end_x, int end_y);

/**
 * @brief	Narysowanie bloku na ekranie wyswietlacza.
 * @param	start_x Wspolrzedna X lewego gornego punktu rysowanego bloku.
 * @param	start_y Wspolrzedna Y lewego gornego punktu rysowanego bloku.
 * @param	size_x Rozmiar bloku w osi X.
 * @param	size_y Rozmiar bloku w osi Y.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu narysowania kwadratu na ekranie wyswietlacza.
**/
void d_square(int start_x, int start_y, int size_x, int size_y);

/**
 * @brief	Wydrukowanie tekstu na ekranie wyswietlacza.
 * @param	pos_x Wspolrzedna X pola tekstowego.
 * @param	pos_y wspolrzedna Y pola tekstowego.
 * @param	test wskaznik na tablice znakow.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu narysowania pola tekstowego z tekstem uzytkownika.
**/
void d_text(int pos_x, int pos_y, const char * text);

/**
 * @brief	Pobranie wcisnietego klawisza.
 * @return	Znak wcisniety na klawiaturze.
 * @details	Wykorzystanie biblioteki X11 w celu otrzymania eventu wcisniecia klawisza podczas gdy
 *          okno aplikacji jest aktywne. 
**/
char d_input_wait();

/**
 * @brief	Wyczyszczenie zadanego obszaru.
 * @param	start_x Wspolrzedna X lewego gornego punktu czyszonego obszaru.
 * @param	start_y Wspolrzedna Y lewego gornego punktu czyszonego obszaru.
 * @param	size_x Rozmiar obszaru w osi X.
 * @param	size_y Rozmiar obszaru w osi Y.
 * @return	
 * @details	Wykorzystanie biblioteki X11 w celu wyczyszczenia zadanego obszaru wyswietlacza.
**/
void d_clear(int start_x, int start_y, int size_x, int size_y);

/**
 * @brief	
 * @return	
 * @details	
**/
void d_flush();

/**
 * @brief	Zatwierdzenie wszystkich wprowadzonych zmian na wyswietlaczu.
 * @return	
 * @details	Ze wzgledu na wystepowanie efektu "przeskakiwania" elementow rysowanych na wyswietlaczu 
 *          pomiedzy cyklami jego odswiezania (ang. tearing), wiekszosc wyswietlaczy wspiera technologie
 *          podwojnego buforowania. Podczas gdy wyswietlacz fizycznie odswiezany jest w tzw. frontbuffera,
 *          wszelkie dokonywane przez uzytkownika zmiany wykonywane sa na tzw. backbufferze (co wprowadza
 *          swego rodzaju buforowanie na wejsciu wyswietlacza). W momencie wywolania metody d_flush(),
 *          bufory zostaja zamienione miejscami (frontbuffer <-> backbuffer), i wszelkie zmiany zostaja
 *          przeslane do wyswietlacza w jednym momencie. 
**/
void d_close();

/**
 * @brief	Zawieszenie watku na okreslony czas.
 * @param   ms Ilosc czasu do odczekania w [ms].
 * @return	
 * @details	Wrapper do metody usleep().
**/
void d_sleep(int ms);

#endif /* define: display_h */