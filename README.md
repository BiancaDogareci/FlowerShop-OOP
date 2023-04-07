## Nume proiect: Bianca's Flower Shop
## Tema aleasa: Magazin Online
## Clase:
* Product: fiecare obiect al acestei clase reprezinta o floare si contine datele despre floarea respectiva (nume,id-ul produsului, pret, numarul de fire ramase)
* Customer: fiecare obiect al acestei clase stocheaza date despre client (nume, prenume, email)
* ShoppingCart: obiectele acestei clase contin doi vectori alocati dinamic. Unul unde sunt stocate preturile pe care trebuie sa le plateasca clientul in functie de produsele alese si de numarul de fire ales pentru fiecare floare si alt vector alocat dinamic in care se afla pointeri catre obiecte de tip Product (pentru a putea accesa numele produselor alese si a le afisa in meniul interactiv)
* Adress: obiectele acestei clase contin date despre adresa clientului (tara, orasul, strada, numarul)
* CreditCard: obiectele acestei clase contin informatiile de pe card in cazul in care plata se face cu cardul (numar card, data de expirare, numele, CVC)
* Order: obiectele acestei clase prezinta informatiile necesare pentru comanda unui anumit client. Astfel in ea se afla variabile de tipul Adress, CreditCard si ShoppingCart (fiind si ele obiecte la randul lor)
* feedback: obiectele clasei contin cate un vector alocat dinamic ce are stocat in el nota introdusa de la tastatura pentru un anumit serviciu. Fiecare obiect de acest tip corespunde unui anumit serviciu (interactiunea cu floraria, varietatea produselor si pentru preturile produselor)

## Functionalitatile proiectului: (descriere a meniului interactiv si a metodelor existente)
* arata meniul cu functia "show_menu"
* clientul poate introduce codul unui produs cu ajutorul functiei "get_code", iar daca acel cod introdus este gresit se afiseaza mesajul "Cod gresit! Introduceti altul:" si se poate adauga altul pentru orice produs
* cand clientul adauga in cos un numar de fire de un anumit tip, se apeleaza si functia "minus_product", care scade acel numar de fire din totalul de fire ramase de la respectivul produs. In cazul in care clientul vrea mai multe fire decat are floraria, produsul nu se adauga la cos si se transmite mesajul "Nu mai exista destule fire! Reveniti in zilele urmatoare."
* de fiecare data cand se adauga ceva in cos clientul este intrebat daca vrea sa aleaga un cod pentru alt produs pentru a ii vedea detaliile, ulterior pentru a-l putea adauga in cos
* daca utilizatorul nu vrea sa adauge alte produse in cos, el poate sa aleaga daca sa plaseze comada cu podusele alese anterior
* cand comanda este plasata, se calculeaza totalul de plata cu o reducere aplicata cu ajutorul funtiei statice "sale" si clientul trebuie sa introduca anumite informatii: nume, prenume, email, detalii de card (optional), tara, orasul, strada, numarul
* la final se cer note in legatura cu serviciile oferite
#
#### Dogareci Bianca-Alexandra
