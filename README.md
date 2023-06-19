# elevator02

W projekcie korzystamy jedynie z pliku main.cpp

DZIAŁANIE PROGRAMU:
W projekcie znajduje się winda, poruszająca się między czterema piętrami. 
Za pomocą przycisków na interfejsie użytkowanika możemy dodawać ludzi chcących przemieścić się na konkretne piętro (na każdym piętrze mamy przyciski z wyborem piętra, na które postać chce się przemieścić)
Dodatkowo na dole windy znajduje się informacja o masie obecnych w windzie pasażerów (każdy pasażer waży 70 kg, a maksymalny udźwig windy to 600 kg. W związku z czym maksymalnie 8 osób wejdzie do windy)
Jeżeli winda zatrzyma się na pustym piętrze i nie będzie żadnych przywołań, to po odczekaniu 5 sekund zjedzie na dół.

OPIS PROJEKTU:
W projekcie korzystamy z biblioteki gdi+. Tworzymy okno, a następnie przy użyciu funkcji wspomnianej biblioteki odtwarzamy kształt windy, przycisków oraz obecnych w niej postaci. 
Cały program działa pod wpływem komend użytkownika. Gdy klikamy przycisk przywołania windy do 2 wektorów dodawane są dane.
Do wektora Calls, dzięki któremu kolejkowane są nasze przywołania i który (w wypadku, gdy nie mamy nikogo w windzie) jest naszym wyznacznikiem dokąd winda powinna się poruszać.
Oraz do jednego z wektorów first/second/third/fourthfloorpeople (w którym zbierane są informacje na które piętro chce jechać dana postać, dzięki temu winda będzie wiedziała czy jadąc ze sobą
ma zabierać daną osobę, czy nie (gdy będzie jechać do góry zabierze osoby chcące jechać do góry))
Poruszanie się windy następuje pod wpływem zmiany danej goTo (uzależnionej od kierunku postaci obecnych windzie, lub od pierwszego elementu wektora Calls), która przyjmuje odpowiednio wartość 1, 2, 3 lub 4 (numr piętra, na która winda ma pojechać).
Dopóki winda się porusza (nie osiągnie poziomu na który jedzie) drukowane jest nowe okno z nową pozycją windy.
Postaci w windzie zbierane są w wektorze inElevator i od jego rozmiaru uzależnione jest czy dana postać wejdzie do windy (czy zmieści się w ograniczeniu wagowym). Na jego podstawie również wyświetlana jest masa obecnych w windzie osób (70*rozmiar wektora)
Funkcja czekania 5 sekund i jazdy w dół gdy winda jest pusta zaimplementowana jest za pomocą funkcji GetTickCount() (dzięki niej zbieramy informację o czasie rozpoczęcia odliczania) oraz zmiennej startCounting. W trakcie trwania programu odliczany jest czas i jeżeli zmienna startCounting wciąż ma wartość true (nie pojawiło się żadne przywołanie), a wartość czasu obecnego - wartość czasu od rozpoczęcia odliczania = 5000 (ms), to zmienia się wartość goTo na 1 i winda zjeżdża w dół