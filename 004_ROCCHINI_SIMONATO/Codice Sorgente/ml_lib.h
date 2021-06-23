/*! \file ml_lib.h
    \brief Header della libreria ml_lib
     *
    Questo file contiene le definizioni di tutte le strutture e delle funzioni che compongono la libreria ml_lib
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*---------------------------------SEZIONE DEFINIZIONI---------------------------------*/

#define ROW 7
#define COL 7

/*! Definizione dei due giocatori esistenti*/
typedef enum {Umano, Ai} id_p; /**/

/*! Definizione dei due possibili gradi della pedina*/
typedef enum {Soldier, Officer} gr;

/*! Definizione della direzione*/
typedef enum {Up, Down} dir;

/*! Rinominazione del tipo struct cella in pedina, per praticità di scrittura*/
typedef struct cella pedina;

/*! Rinominazione del tipo struct punto in point, per praticità di scrittura*/
typedef struct punto point;

/*!Definizione del tipo pedina*/
struct cella{
    id_p id_player; /*!< ID del giocatore proprietario della pedina */  /*BIANCHI = 0, NERI = 1*/
    gr grado; /*!< Grado della pedina *//*SOLDATO = 0, UFFICIALE = 1*/
    pedina *middle; /*!< Puntatore alla pedina di mezzo della colonna */
    pedina *down; /*!< Puntatore alla pedina in fondo alla colonna */
};

/*!Definizione del tipo punto*/
struct punto{
    int x; /*!<Coordinata x */
    int y; /*!<Coordinata y */
};

/*
* ASSUNZIONI LOGICHE FONDAMENTALI:
*     L'utente muove sempre per primo
*     Se il giocatore ha la possibilità di catturare una pedina, è obbligato a farlo
*/


/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

/**
 * \defgroup Ausiliarie Funzioni ausiliarie
 * @{
 */

/*! \fn set_id_player(pedina *p, id_p value)
*   \brief Imposta l'id_player \a value della pedina indicata dal puntatore \a *p
*   \param p puntatore ad una pedina
*   \param value il valore da settare
*
*    Imposta il proprietario della pedina.
*/
void set_id_player(pedina *p, id_p value);

/*! \fn id_p get_id_player(pedina *p);
*   \brief Ritorna \a id_player dalla pedina \a *p specificata
*   \param p puntatore ad una pedina
*
*    Ritorna il proprietario della pedina.
*/
id_p get_id_player(pedina *p);

/*! \fn set_board_value(pedina **board, point p, pedina *value)
*   \brief Imposta la pedina \a value nella posizione \a x , \a y nella scacchiera \a board
*   \param board matrice linearizzata della scacchiera
*    \param p punto in cui si trova la pedina nella scacchiera
*    \param value la pedina da inserire
*
*    Imposta il valore value nella posizione indicata nella scacchiera.
*/
void set_board_value(pedina **board, point p, pedina *value);

/*! \fn get_board_value(pedina **board, point p)
*   \brief Ritorna la \a pedina contenuta nella posizione \a x , \a y di \a board
*   \param board matrice linearizzata della scacchiera
*   \param p punto in cui si trova la pedina nella scacchiera
*
*    Ritorna il puntatore alla pedina nella posizione x,y di board.
*/
pedina* get_board_value(pedina **board, point p);

/*! \fn get_board_value_immediate(pedina **board, int x, int y)
*   \brief Ritorna la \a pedina contenuta nella posizione \a x , \a y di \a board
*   \param board matrice linearizzata della scacchiera
*    \param x coordinata x della cella desiderata
*    \param y coordinata y della cella desiderata
*
*    Ritorna il puntatore alla pedina nella posizione x,y di board.
*/
pedina* get_board_value_immediate(pedina **board, int x, int y);

/*! \fn get_board_value_middle(pedina **board, point p)
*   \brief Ritorna la \a pedina "middle" contenuta nella posizione \a x , \a y di \a board
*   \param board matrice linearizzata della scacchiera
*    \param p punto in cui si trova la pedina nella scacchiera
*
*    Ritorna il valore della pedina middle nella posizione x,y di board.
*/
pedina* get_board_value_middle(pedina **board, point p);

/*! \fn get_board_value_down(pedina **board, point p)
*   \brief Ritorna la \a pedina "down" contenuta nella posizione \a x, \a y di \a board
*   \param board matrice linearizzata della scacchiera
*    \param p punto in cui si trova la pedina nella scacchiera

*    Ritorna il valore della pedina down nella posizione indicata nella scacchiera.
*/
pedina* get_board_value_down(pedina **board, point p);

/*! \fn set_grade(pedina *p,gr value)
*   \brief Imposta il grado \a value della pedina indicata dal puntatore \a p
*   \param p puntatore ad una pedina
*   \param value il valore da settare
*
*   Imposta il grado di una pedina.
*/
void set_grade(pedina *p,gr value);

/*! \fn get_grade(pedina *p)
*   \brief Ritorna il grado \a value della pedina indicata dal puntatore \a p
*   \param p puntatore ad una pedina
*
*    Ritorna il grado di una pedina.
*/
gr get_grade(pedina *p);

/*! \fn is_inside(int x, int y)
*   \brief Indica se \a x, \ay è dentro alla scacchiera
*    \param x coordinata x della cella desiderata
*    \param y coordinata y della cella desiderata
*
*    Indica se la posizione desiderata è dentro alla scacchiera
*/
int is_inside(int x, int y);

/*! \fn right_path(dir direction, gr grade, id_p player)
*   \brief Indica se la direzione è corretta
*    \param direction direzione della pedina (1 il basso, 0 l'alto)
*    \param grade grado della pedina
*    \param player giocatore
*
*    Ritorna 1 se la direzione della pedina è giusta, basandosi sul giocatore e sul grado di essa
*/
int right_path(dir direction, gr grade, id_p player);

/*! \fn is_valid_letter(char input)
*   \brief Verifica che input sia una lettera
*   \param input char da verificare
*
*    Ritorna 1 se input è una lettera da a ad g, altrimenti è 0
*/
int is_valid_letter(char input);

/*! \fn is_valid_number(char input)
*   \brief Verifica che input sia un numero
*   \param input char da verificare
*
*    Ritorna 1 se input è un numero da 1 a 7, altrimenti è 0
*/
int is_valid_number(char input);

/*! \fn is_valid_input(char input[5])
*   \brief Verifica che la stringa in input sia valida
*   \param input stringa da verificare
*
*    Ritorna 1 se la stringa input è un input valido
*/
int is_valid_input(char input[5]);

/*! \fn add_point(point p, point l)
*   \brief Modifica lo stato di un punto
*   \param p Punto da modificare
*    \param l Punto da  aggiungere a p
*
*    Effettua la somma vettoriale di p e l
*/
point add_point(point p, point l);

/**@}*/

/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

/**
 * \defgroup Memoria Funzioni di gestione della memoria
 * @{
 */

/*! \fn **createMatrix()
*   \brief Funzione che crea la matrice della scacchiera
*
*     Ritorna un puntatore di tipo \a pedina** ad una matrice bidimensionale di puntatori a pedina linearizzata.
*/
pedina **createMatrix(void);

/*! \fn cloneMatrix(pedina **board)
*   \brief Clona la matrice contenuta in board nella matrice new_board
*    \param board matrice linearizzata della scacchiera
*
*     Copia il contenuto di board in new_board
*/
pedina** cloneMatrix(pedina **board);

/*! \fn destroyMatrix(pedina **p)
*   \brief Distrugge la matrice della scacchiera
*   \param board matrice linearizzata della scacchiera
*
*    Funzione che dealloca la memoria della matrice della scacchiera.
*/
void destroyMatrix(pedina **board);

/*! \fn fillBoard(pedina **p)
*   \brief Riempie la scacchiera con le pedine
*   \param board matrice linearizzata della scacchiera
*
*    Riempie la scacchiera con le pedine. Il giocatore 1 ( \a Umano) sarà posizionato nella parte bassa della scacchiera.
*/
void fillBoard(pedina **board);

/**@}*/

/*---------------------------------SEZIONE FUNZIONI INPUT---------------------------------*/

/**
 * \defgroup Input Funzioni di input
 * @{
 */

/*! \fn catchInput(int *cord)
*   \brief Legge l'input da tastiera
*    \param cord array contenente le coordinate di partenza e destinazione della pedina
*
*     Legge l'input dall'utente e traduce le coordinate in int, che vengono inseriti in un array apposito.
*/
int catchInput(int *cord);


/*! \fn int getMode(void)
*   \brief Selettore delle due modalità di gioco
*
*     Funzione che chiede di selezionare modalità player vs player oppure player vs CPU
*/
int getMode(void);

/*! \fn getDepth(void)
*   \brief Ritorna il livello di difficolta della CPU
*    Chiede al player di inserire il livello di difficolta della CPU
*/
int getDepth(void);


/**@}*/

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

/**
 * \defgroup Output Funzioni di output
 * @{
 */

/*! \fn printPedina(pedina *p)
*   \brief Stampa una lettera rappresentante la pedina
*    \param p puntatore alla pedina
*
*    Stampa un carattere ASCII identificativo del contenuto della casella p:
*     <ul>
*         <li>b/n se il giocatore è bianco o nero ( \a Umano / \a Ai).</li>
*         <li>maiuscola/minuscola se la pedina è ufficiale/soldato.</li>
*     </ul>
*/
void printPedina(pedina *p);

/*! \fn printMatrix(pedina **p)
*   \brief Stampa la scacchiera
*    \param board matrice linearizzata della scacchiera
*
*    Funzione che stampa la scacchiera con una cornice che definisce le coordinate.
*/
void printMatrix(pedina **board);

/*! \fn printStatus(int turn)
*   \brief Stampa lo stato del gioco
*    \param turn numero dei turni passati
*
*    Stampa lo status del gioco (numero del turno e giocatore che deve muovere).
*/
void printStatus(int turn);

/*! \fn printRules()
*    \brief Stampa le regole del gioco
*
*    Stampa le regole del gioco.
*/
void printRules(void);

/*! \fn victory(id_p winner)
*    \brief Schermata di vittoria
*
*    Stampa il vincitore del gioco.
*/
void victory(id_p winner);

/*! \fn moveError(pedina **board, int cord[4], int turn)
*    \brief Schermata di errore di gioco
*
*    Fornisce informazioni in caso di mossa inserita non corretta.
*/
void moveError(pedina **board, int cord[4], int turn);

/*! \fn inputError(int cord[4])
*    \brief Schermata di errore di input
*
*    Fornisce informazioni in caso di inserimento dati scorretto.
*/
void inputError(int cord[4]);

/**@}*/

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/

/**
 * \defgroup Logiche Funzioni delle logiche di gioco
 * @{
 */
 
 /*! \fn is_same_team(pedina **board, point a, point b)
*   \brief Verifica che due pedine siano della stessa squadra
*   \param board matrice linearizzata della scacchiera
*   \param a prima pedina
*   \param b seconda pedina
*
*     Restituisce 1 se le due pedine a e appartengono alla stessa squadra
*/
int is_same_team(pedina **board, point a, point b);

/*! \fn is_legal_player(pedina **board, point from, int turn)
*   \brief Verifica che il giocatore sia corretto
*   \param board matrice linearizzata della scacchiera
*   \param from punto di partenza della pedina
*   \param turn numero del turno corrente
*
*     Restituisce 1 se il giocatore che muove è abilitato a farlo, 0 altrimenti.
*/
int is_legal_player(pedina **board, point from, int turn);

/*! \fn is_empty(pedina **board, point x)
*   \brief Verifica che casella sia vuota
*   \param board matrice linearizzata della scacchiera
*   \param x punto di arrivo della pedina
*
*     Restituisce 1 se la casella è vuota, 0 altrimenti.
*/
int is_empty(pedina **board, point x);

/*! \fn is_full(pedina **board, point x)
*   \brief Verifica che casella sia piena
*   \param board matrice linearizzata della scacchiera
*   \param x punto di partenza della pedina
*
*     Restituisce 1 se la casella è piena, 0 altrimenti.
*/
int is_full(pedina **board, point x);

/*! \fn is_valid_distance(point from, point to)
*   \brief Verifica che la validità della lunghezza della mossa
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*
*     Restituisce 1 se la distanza della mossa è valida, 0 altrimenti.
*/
int is_valid_distance(point from, point to);

/*! \fn is_valid_move(pedina** board, point from, point to, int turn)
*   \brief Verifica che la mossa selezionata sia legale
*   \param board matrice linearizzata della scacchiera
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*   \param turn numero del turno corrente
*
*     Restituisce 1 se la mossa from->to è valida, 0 altrimenti.
*/
int is_valid_move(pedina** board, point from, point to, int turn);

/*! \fn increase_grade(pedina **board, point soldier)
*   \brief Verifica che la pedina soldier sia sa promuovere
*   \param board matrice linearizzata della scacchiera
*   \param soldier pedina candidata alla promozione
*
*     Se la pedina soldier è nella condizione di essere promossa la promuove
*/
void increase_grade(pedina **board, point soldier);

/*! \fn isWinner(pedina **p, id_p player)
*   \brief Verifica che il giocatore \a player abbia vinto
*   \param board matrice linearizzata della scacchiera
 *   \param player giocatore selezionato
*
 *    Verifica che playertore \a idPlayer abbia vinto.
*    Restituisce 1 se idPlayer ha vinto, altrimenti 0.
*/
int isWinner(pedina **board, id_p player);

/*! \fn isForbiddenCell(point p)
*   \brief Verifica che la cella sia accessibile
*   \param p punto in cui si trova la pedina nella scacchiera
*
*    Restituisce 1 se la cella non è accessibile (si possono usare solo le celle bianche della scacchiera), altrimenti 0.
*/
int isForbiddenCell(point p);

/*! \fn my_move(pedina **p, point from, point to, int turn)
*   \brief Verifica che la mossa selezionata sia legale e la esegue
*   \param board matrice linearizzata della scacchiera
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*   \param turn numero del turno corrente
*
*     Restituisce 1 se la mossa è stata fatta, 0 se non è stato possibile.
*     Le coordinate inserite sono corrette in fase di input (sono all'interno della scacchiera e non sono caselle proibite).
*     Verifica che la distanza ed il grado siano compatibili con la mossa.
*/
int my_move(pedina** board, point from, point to, int turn);

/*! \fn distance(point from, point to)
*   \brief Restituisce un codice che descrive la lunghezza della mossa
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*
*    Restituisce la distanza in modulo tra due punti nella matrice:
*    Se è maggiore di 2, uguale a 0, o la destinazione è in una casella non accessibile restituisce il codice errore -1.
*
*    Le coordinate inserite sono corrette (la destinazione non è una casella proibita).
*/
int distance(point from, point to);

/*! \fn capture(pedina **p, point from, point to)
*   \brief Esegue la cattura delle pedine
*   \param board matrice linearizzata della scacchiera
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*
*     Questa funzione si occupa di catturare le pedine indicate.
*     Si assume la correttezza delle coordinate inserite, la legalità della mossa è verificata nella funzione move().
*/
void capture(pedina **board, point from, point to);

/*! \fn gradeCheck(pedina **board, point form, point to)
*   \brief Verifica che la mossa selezionata sia compatibile con il grado della pedina
*   \param board matrice linearizzata della scacchiera
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*
*    Verifica il grado della pedina mossa:
*    restituisce 1 se la mossa è consentita, 0 se non è consentita.
*/
int gradeCheck(pedina **board, point from, point to);

/*! \fn can_eat(pedina **board, point p)
*   \brief Verifica la possibilità di mangiare
*   \param board matrice linearizzata della scacchiera
*   \param p punto in cui si trova la pedina nella scacchiera
*
*    Verifica la possibilità della pedina in \a x , \a y di mangiare le pedine avversarie intorno a sé
*/
int can_eat(pedina **board, point p);

/*! \fn can_move(pedina **board, point p)
*   \brief Verifica la possibilità di muoversi
*   \param board matrice linearizzata della scacchiera
*   \param p punto in cui si trova la pedina nella scacchiera
*
*    Verifica la possibilità della pedina in \a x , \a y di muoversi nelle caselle adiacenti
*/
int can_move(pedina **board, point p);

/*! \fn int existMandatory(pedina **board, point form, point to)
*   \brief Controlla la presenza di mosse obbligatorie
*   \param board matrice linearizzata della scacchiera
*   \param from punto di partenza della pedina
*   \param to punto di arrivo della pedina
*
*    Verifica se, nel caso di non cattura, esiste una cattura obbligatoria da fare.
*    Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0.
*/
int existMandatory(pedina **board, point from, point to);

/**@}*/
