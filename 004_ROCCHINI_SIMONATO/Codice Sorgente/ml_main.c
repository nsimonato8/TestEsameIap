/*! \file ml_main.c
*   \brief MiniLaska
*
*    Questo file contiene il programma del gioco MiniLaska, che utilizza la libreria ml_lib
*/

#include <stdio.h>
#include <stdlib.h>
#include "ml_autoplay.h"

pedina **board = NULL; /*!< La scacchiera */

point *moves; /*!< Array di appoggio per calcoli logici. Contiene tutti i possibili movimenti di una pedina*/

int coordinate[4]; /*!< Array contenente le coordinate di partenza e di arrivo di ogni mossa */

int success_move = 1; /*!< Flag che verifica la legalità di una mossa */

int success_input = 1; /*!< Flag che verifica la correttezza dell'input */

int Turn = 0; /*!< Contatore del turno corrente */

int Mode;  /*!< Modalità di gioco*/

int Depth; /*!< Difficoltà della CPU*/

point From; /*!< Segnaposto del punto di partenza di ogni mossa */

point To; /*!< Segnaposto del punto di arrivo di ogni mossa */

/*! \fn main()
*
*    Funzione principale del gioco
*/
int main(){

    moves = get_dir();

    board = createMatrix();

    fillBoard(board);

    /**/
    
    do{
        Mode=getMode();
        
        if(Mode == 1){/*1vs1*/
            do{
                do{
                    int i;

                    printStatus(Turn); /*Status giocatore + n°Turno */
                    printMatrix(board); /*Status scacchiera */

                    if(!success_move)
                        moveError(board,coordinate,Turn);
                    if(!success_input)
                        inputError(coordinate);

                    success_input = catchInput(coordinate);
                    
                    From.x = coordinate[1];
                    From.y = coordinate[0];
                    To.x = coordinate[3];
                    To.y = coordinate[2];
                    
                    printf("%d\n",success_input);
                    for(i = 0; i < 4; i++)
                        printf("%d ",coordinate[i]);
                    
                    printf("\n");
                    success_move = my_move(board,From,To,Turn);
                    
                }while(!(success_input && success_move));/*Inserimento dati e mossa*/
                Turn++;
            }while(!(isWinner(board,Umano)||isWinner(board,Ai))); /*Controllo esistenza vincitore*/

            if(isWinner(board,Umano))
                victory(Umano);
            else
                victory(Ai);
                
        }else if(Mode == 2){/*1vsCPU*/
            
            Depth = getDepth();
            
            do{
                do{
                    
                    printStatus(Turn); /*Status giocatore + n°Turno */
                    printMatrix(board); /*Status scacchiera */

                    if(!success_move)
                        moveError(board, coordinate,Turn);
                    if(!success_input)
                        inputError(coordinate);
                    
                    if(Turn%2){
                        success_move = catchInput_Autoplay(board, Turn, Depth); /*Input autoplay*/
                    }
                    else{
                        success_input = catchInput(coordinate);
                        From.x = coordinate[1];
                        From.y = coordinate[0];
                        To.x = coordinate[3];
                        To.y = coordinate[2];
                    
                        success_move = my_move(board,From,To,Turn);
                    }
                        
                }while(!(success_input && success_move));/*Inserimento dati e mossa*/
                Turn++;
            }while(!(isWinner(board,Umano)||isWinner(board,Ai))); /*Controllo esistenza vincitore*/

            if(isWinner(board,Umano))
                victory(Umano);
            else
                victory(Ai);
            
        }else if(Mode == 3){
            printRules();
        }
        else{
            /*Exit*/
            printf("Esco...\n");
        }
        
    }while(Mode != 4);
    
    /*Liberazione memoria*/
    destroyMatrix(board);
    free(moves);

    return 0;
}
