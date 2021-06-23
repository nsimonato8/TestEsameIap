/*! \file ml_autoplay.h
    \brief Header del componenete Autoplay della libreria ml_lib
     *
    Questo file contiene le definizioni di le astrazioni e funzioni che compongono Autoplay
*/

#include<stdio.h>
#include<limits.h>
#include"ml_lib.h"

#define NUMERO_PEDINE 7
#define MOSSE 8

/*! Definizione struttura t_node*/
typedef struct s_node t_node;

/*! Definizione struttura lista t_node_list*/
typedef struct s_node_list *t_node_list;

/*! Definizione valore valutazione pedina*/
typedef enum mod {MIN, MAX} mode;

/*alfa -> [-1,1]*/

/*! Definizione tipo coppia valore, mossa*/
struct s_node { /*coppia valore,mossa*/
    point start;
    point end;
    int value;
};

/*! Definizione tipo lista di t_node*/
struct s_node_list {
    t_node data;
    t_node_list next;
};

/*! \fn catchInput_Autoplay(pedina **board, int turn, int depth)
*   \brief Acquisice input modalità Player vs CPU
*   \param board matrice linearizzata della scacchiera
*   \param turn numero del turno corrente
*   \param depth difficoltà della CPU
*
*    Ritorna il valore della funzione "my_move": 1 mossa riuscita, 0 altrimenti.
*/
int catchInput_Autoplay(pedina **board, int turn, int depth);

/*! \fn can_be_eaten(pedina **board, point p)
*   \brief Verifica se pedina può essere mangiata
*   \param board matrice linearizzata della scacchiera
*   \param p in cui si trova la pedina nella scacchiera
*
*    Verifica se pedina può essere mangiata
*/
int can_be_eaten(pedina **board, point p);

/*! \fn evaluate(pedina **board)
*   \brief Esegue una valutazione euristica del valore di minmax
*   \param board matrice linearizzata della scacchiera
*
*    Esegue una valutazione euristica del valore di minmax
*/
int evaluate(pedina **board);

/*! \fn print_t_node(t_node t)
*   \brief Esegue una stampa dell'oggetto in input
*   \param t struttura coppia valore, mossa
*
*    Esegue una stampa dell'oggetto in input
*/
void print_t_node(t_node t);

/*! \fn print_list(t_node_list i)
*   \brief Esegue una stampa della lista in input
*   \param i struttura coppia valore, mossa
*
*    Esegue una stampa della lista in input
*/
void print_list(t_node_list i);

/*! \fn prepend(t_node_list *l, t_node val)
*   \brief Esegue un'aggiunta di un elemento in testa
*   \param l lista di t_node
*   \param val oggetto da aggiungere alla lista
*
*    Esegue un'aggiunta di un elemento in testa
*/
int prepend(t_node_list *l, t_node val);

/*! \fn destroy_list(t_node_list l)
*   \brief Esegue la distruzione della lista
*   \param l lista di t_node
*
*    Esegue la distruzione della lista
*/
void destroy_list(t_node_list l);

/*! \fn append(t_node_list *l, t_node val)
*   \brief Esegue un'aggiunta di un elemento in coda
*   \param l lista di t_node
*   \param val oggetto da aggiungere alla lista
*
*    Esegue un'aggiunta di un elemento in coda
*/
int append(t_node_list *l, t_node val);

/*! \fn get_from_list(t_node_list l, mode x)
*   \brief Ottiene l'elemento che ha valore x
*   \param l struttura coppia valore, mossl
*   \param x elemento con valore MAX o MIN
*
*    Ottiene l'elemento che ha valore x
*/
t_node get_from_list(t_node_list l, mode x);

/*! \fn get_dir(void)
*   \brief Ritorna la direzione della pedina
*
*   Ritorna la direzione della pedina
*/
point* get_dir(void);

/*! \fn get_moves(pedina **board, int turn)
*   \brief Ritorna una lista con le possibili mosse
*   \param board matrice linearizzata della scacchiera
*   \param turn numero del turno corrente

*
*   Ritorna una lista con le possibili mosse
*/
t_node_list get_moves(pedina **board, int turn);

/*! \fn minimax(pedina **board, t_node move, int depth, int turn)
*   \brief Ritorna una lista con le possibili mosse
*   \param board matrice linearizzata della scacchiera
*   \param move mossa da valutare
*   \param depth profondità/difficoltà della CPU
*   \param turn numero del turno corrente
*
*   Ritorna una lista con le possibili mosse
*/
int minimax(pedina **board, t_node move, int depth, int turn);
