#include<stdio.h>
#include<stdlib.h>
#include "ml_lib.h"

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

/* Imposta l'id_player della pedina indicata dal puntatore*/
void set_id_player(pedina *p, id_p value){
    p->id_player = value;
}

/* Ritorna il p->id_player della pedina specificata */
id_p get_id_player(pedina *p){
    return p->id_player;
}

/* Imposta il valore value nella posizione indicata nella scacchiera*/
void set_board_value(pedina **board, point p, pedina *value){
    board[p.y * COL + p.x] = value;
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value(pedina **board, point p){
    return board[p.y * COL + p.x];
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value_immediate(pedina **board, int x, int y){
    return board[y * COL + x];
}

/* Ritorna il valore della pedina middle nella posizione indicata nella scacchiera*/
pedina* get_board_value_middle(pedina **board, point p){
    if(!board[p.y * COL + p.x])
        return 0;
    else
        return board[p.y * COL + p.x]->middle;
}

/* Ritorna il valore della pedina down nella posizione indicata nella scacchiera*/
pedina* get_board_value_down(pedina **board, point p){
    if(!board[p.y * COL + p.x])
        return NULL;
    else
        return board[p.y * COL + p.x]->down;
}

/* Imposta il grado di una pedina*/
void set_grade(pedina *p,gr value){
    p->grado = value;
}

/* Ritorna il grado di una pedina*/
gr get_grade(pedina *p){
    return p->grado;
}

/*Ritorna 1 se x,y è dentro la scacchiera, 0 altrimenti*/
int is_inside(int x, int y){
    return (x >= 0) && (x <= 6) && (y >= 0) && (y <= 6);
}

/*Ritorna 1 la direzione della pedina è giusta*/
int right_path(dir direction, gr grade, id_p player){
    return grade || !(direction^player);
}

/*Ritorna 1 se input è una lettera da a ad g, altrimenti è 0*/
int is_valid_letter(char input){
    return ((input >= 'a') && (input <= 'g'));
}

/*Ritorna 1 se input è un numero da 1 a 7, altrimenti è 0*/
int is_valid_number(char input){
    return (input >= 49) && (input <= 55);
}

/*Ritorna 1 se l'input da tastiera è valido, altrimenti è 0*/
int is_valid_input(char input[5]){
    return is_valid_letter(input[0]) && is_valid_number(input[1]) && is_valid_letter(input[2]) && is_valid_number(input[3]);
}

/*Somma i valori di due punti*/
point add_point(point p, point l){
    p.x += l.x;
    p.y += l.y;
    return p;
}

/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

/*
 * Funzione che crea la matrice della scacchiera
*/
pedina **createMatrix(){

    pedina** board = (pedina **) malloc(COL*ROW*sizeof(pedina *));

    if(!board){
        printf("createMatrix failed malloc");
        return 0;
    }
    else
        return board;
}

pedina** cloneMatrix(pedina **board){
    point i;
    
    pedina **new_board = createMatrix();
    
    
    for(i.y = 0; i.y < ROW; i.y++){
        for(i.x = 0; i.x < COL; i.x++)
            if(get_board_value(board,i)){
                pedina *app = (pedina*)malloc(sizeof(pedina));
                set_board_value(new_board,i,app);
                set_grade(app, get_grade(get_board_value(board, i)));
                set_id_player(app, get_id_player(get_board_value(board, i)));
                app->middle=get_board_value_middle(board, i);
                app->down=get_board_value_down(board, i);
                
            } else {
                set_board_value(new_board,i,get_board_value(board,i));
            }
    }
    if(!new_board)
        printf("cloneMatrix failed malloc");
    
    return new_board;
}

/*
 * Funzione che distrugge la matrice della scacchiera
 *
 * TODO: rivedere la free su ogni cella della scacchiera se non ancora fatta
 *
*/
void destroyMatrix(pedina **board){
    free(board);
}

/*
 * Restituisce 1 se la cella non è accessibile (si possono usare solo le celle bianche della scacchiera), altirmenti 0
*/
int isForbiddenCell(point p){
    if((p.x % 2 && !(p.y % 2)) || (!(p.x % 2) && (p.y % 2)))
        return 1;
    else
        return 0;
}

/*
 * Riempie la scacchiera
 * Modifica giovanni: set_board_value nell'if se forbiddenCell e j==3, IL VALUE MESSO È 0, ma la
 * funzione vuole il tipo pedina;
*/

void fillBoard(pedina** board){

    int i,j;
    point p;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            p.x = j;
            p.y = i;
            if(isForbiddenCell(p) || i == 3){
                set_board_value(board,p,0);
            }
            else{
                pedina *a = NULL;
                a = (pedina*) malloc(sizeof(pedina));
                set_grade(a,Soldier);
                a->down=NULL;
                a->middle=NULL;

                if(i < 3)
                    set_id_player(a, Ai);
                else{
                    set_id_player(a, Umano);
                }
                set_board_value(board,p,a);
            }
        }
    }
}

/*---------------------------------SEZIONE FUNZIONI INPUT---------------------------------*/

/*
 * FUNZIONE CHE PRENDE IN INPUT CORDINATE PER LO SPOSTAMENTO DELLA PEDINA
 * controllo aggiuntivo per non inserire coordinate di start su cella a null.
 * per la destinazione non posso mettere questo controllod
*/
int catchInput(int cord[4]){
    char input[5];
    int success = 0;
    do{
        printf("\nInserisci le coordinate della mossa [LETTERA-NUMERO-LETTERA-NUMERO]: \n\t");
        
        success = scanf("%s",input);
                
        if(success && is_valid_input(input)) /*Controllo validità input*/
            printf("\n");
        else
            printf("\t\t[Input Error] Coordinate inserite non valide \n");
    }while(!success);
    
    cord[0] = input[0] - 'a';
    cord[1] = input[1] - '0' - 1;
    cord[2] = input[2] - 'a';
    cord[3] = input[3] - '0' - 1;
    
    return success;
}

/*
 * FUNZIONE CHE PRENDE IN INPUT LA SELEZIONE DELLA MODALITA' DI GIOCO
*/
int getMode(void){
    int mode, i;
    printf("\nPer selezionare la modalità player 1 vs player 2 premi '1';\n\nPer selezionare la modalità player vs CPU premi '2';\n\nPer le regole e i crediti premi '3';\n\nModalità: ");
    i = scanf("%d",&mode);
    
    if(i < 0)
		perror("Errore scanf");
    
    printf("\n");
    return mode;
}

/*Ritorna il livello di difficoltà della CPU*/
int getDepth(void){
    int depth = 0, i;
    do{
        printf("\nInserisci la difficoltà della CPU (con un minimo di 1, fino ad un massimo di 6): ");
        i = scanf("%d",&depth);
        if(i < 0)
			perror("Errore scanf");
        
        printf("\n");
    }while(depth<1 || depth>6);
    
    return depth;
}

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

/* Stampa un carattere ASCII identificativo del contenuto della casella p
 *
 * PROVO A TOGLIERE IL CONTROLLO DEL NULL
 *
 * */
void printPedina(pedina *p){

    if(!p){
        printf(" ");
    }
    else if(get_id_player(p) && get_grade(p))
        printf("N");
    else if(get_id_player(p) && !get_grade(p))
        printf("n");
    else if(!get_id_player(p) && get_grade(p))
        printf("B");
    else
        printf("b");
}

/* Funzione che stampa la scacchiera in base al posizionamento delle pedine. */
void printMatrix(pedina** board){

    int i,j;
    point p;

    for(i=0; i<ROW; i++){

        printf("%c > ",('A'+ i));

        for(j=0;j<COL;j++){
            p.x = j;
            p.y = i;

            if ((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2)))
                printf("###");
            else if(!get_board_value(board,p)){
                printf("   ");
            }
            else{
                printPedina(get_board_value(board,p));
                printPedina(get_board_value_middle(board,p));
                printPedina(get_board_value_down(board,p));
            }
            printf("|");
        }
        printf("\n");
    }

    printf("    ");

    for(i=0;i<COL;i++)
        printf("^   ");

    printf("\n");

    printf("    ");

    for(i=0;i<COL;i++){
        printf("%d   ", (i+1));
    }

    printf("\n");
}

void printStatus(int turn){
    printf("\n\nTurn number: %u\nMove player: %s\n\n",(turn+1),(turn%2)?"User 2":"User 1");
}

void printRules(){
    printf("                          Benvenuto in MiniLaska\n\n");
    printf("MiniLaska è una variante del gioco originale Lasca le cui uniche differenze sono due:\n");
    printf("1)si può avere una colonna di massimo tre pedine,\n");
    printf("se si supera tale numero si perde l'ultima pedina a partire dal basso\n");
    printf("2)si può conquistare/mangiare una pedina per volta.\n");
    printf("E' composta da una scacchiera 7x7, delle 49 caselle solo 25 sono giocabili\n");
    printf("essendo che ci si può spostare solo in diagonale.\n");
    printf("I due giocatori partono con 11 pedine ciascuno.\n\n\n\n");

    printf("Struttura: soldato,ufficiale,colonna,comandante:\n\n");
    printf("Tutti partono come soldati semplici. Una volta raggiunta l'ultima riga\n");
    printf("del lato opposto si diventa ufficiali (la pedina viene capovolta),\n");
    printf("ora ci si può muovere sia in avanti che indietro,sempre diagonalmente.\n");
    printf("Quando si catturano le pedine dell'avversario si forma una\n");
    printf("colonna dove in cima abbiamo il giocatore che ha mangiato la/e pedina/e,\n");
    printf("la colonna può essere fomata da due/tre pedine, quella più in alto è detta comandante,\n");
    printf("se il comandante è un colonello permette alla colonna di spostarsi anche all'indietro.\n\n\n\n");

    printf("Come si vince?\n\n");
    printf("quando uno dei due giocatori non ha piu mosse disponibili: \n");
    printf("o tutte le sue pedine vengono catturate oppure viene bloccato,\n");
    printf("quindi qualsiasi mossa faccia finirebbe col perdere.\n\n\n\n");
}

void victory(id_p winner){
    if(winner == Umano)
        printf("\tComplimenti giocatore, grande vittoria!!!");
    else
        printf("\tComplimenti Ai, grande vittoria!!!");
}

void moveError(pedina **board, int cord[4], int turn){
    point from,to;
    from.x = cord[1];
    from.y = cord[1];
    to.x = cord[3];
    to.y = cord[2];
    
    printf("\n<<<---|Non puoi spostarti in quella casella:\t(%d,%d)->(%d,%d)\tPlayer: %d Distance: %d EM: %d |",cord[1],cord[0],cord[3],cord[2],is_legal_player(board,from,turn), is_valid_distance(from,to), existMandatory(board,from,to));
    printf("--->>>\n");
}

void inputError(int cord[4]){
    printf("+++---|Errore di inserimento:\t(%d,%d)->(%d,%d)\t%s\tLegal: #%d#%d#%d#%d#|",cord[1],cord[0],cord[3],cord[2],(char *)cord,is_valid_letter(cord[1]),is_valid_number(cord[0]),is_valid_letter(cord[3]),is_valid_number(cord[2]));
    printf("--->>>\n");
}

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/


int is_same_team(pedina **board, point a, point b){
    return (int) (get_id_player(get_board_value(board,a)) == get_id_player(get_board_value(board,b)));
}

int is_legal_player(pedina **board, point from, int turn){
    return (int)get_id_player(get_board_value(board,from)) == (turn %2);
}

int is_empty(pedina **board, point x){
    return (int)!get_board_value(board,x);
}

int is_full(pedina **board, point x){
    return (int)!is_empty(board,x);
}

int is_valid_distance(point from, point to){
    return distance(from,to) != -1;
}

int is_valid_cell(point p){
    return is_inside(p.x,p.y) && !isForbiddenCell(p);
}

int is_valid_move(pedina** board, point from, point to, int turn){

    int res = 1;
    
    if(is_valid_cell(from) && is_valid_cell(to) && is_full(board,from) && is_legal_player(board, from, turn) && is_empty(board,to) && is_valid_distance(from,to) && !existMandatory(board,from,to) && gradeCheck(board,from,to)){
        if(distance(from,to) == 2){
            point middle;
            middle.x = (from.x + to.x)/2;
            middle.y = (from.y + to.y)/2;
            
            if(is_empty(board, middle) || is_same_team(board,from,middle))
                res = 0;
        }
    }
    else
        res = 0;

    return res;
}

void increase_grade(pedina **board, point soldier){
    if(soldier.y == 6 || soldier.y == 0){ /*Controllo per l'aumento del grado della pedina*/
        int tb = 0;/*top 0 - bottom 1*/
            if(soldier.y == 6)
                tb = 1;
            if(soldier.y == 0)
                tb = 0;
                
            if(!(tb ^ get_id_player(get_board_value(board,soldier))))
                set_grade(get_board_value(board,soldier), Officer); /*increase_grade(pedina **board,point soldier) */
        }
}

/* Verifica che il giocatore idPlayer abbia vinto
 * Restituisce 1 se idPlayer ha vinto, altrimenti 0
*/
int isWinner(pedina **board, id_p idPlayer) {

    int i,j,c;
    pedina *current;
    point p;
    current = 0;
    c = 0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) { /*Controllo ordine coordinate*/
            p.x = j;
            p.y = i;
            current = get_board_value(board,p);
            if(current && get_id_player(current) != idPlayer && can_move(board,p)) /*Prima era j,i*/
                    c++;
        }
    }

    if(c>0){
        return 0;
    } else {
        return 1;
    }
}

/*
 * Restituisce 1 se la mossa è stata fatta, 0 se non è stato possibile
 *
 * Le coordinate inserite sono corrette in fase di input (sono all'interno della scacchiera e non sono caselle proibite)
 * Verifica che la distanza ed il grado siano compatibili con la mossa
 * distance -> distanza tra due punti
 * grade_cntrl -> ctrl spostamento tipo pedina
 * existM -> se esiste mossa obb.
 * legal ply-> ctrl player che muove
*/
int my_move(pedina** b, point from, point to, int turn){

    int success, d;
    /*pedina *from_p, *to_p;*/
    
    success = 1;
    d = distance(from,to);
    
    if(!is_valid_move(b,from,to,turn)){
        success = 0;
    } else{
        if(d == 1){
            set_board_value(b,to,get_board_value(b,from));
            set_board_value(b,from,0);
        }
        else if(d == 2){
            capture(b,from,to); /*se nemica cattura*/
        }
        
        increase_grade(b,to);
        
    }
    
    return success;
}

/*
 * Restituisce la distanza in modulo tra due punti nella matrice:
 * Se è maggiore di 2, uguale a 0, o la destinazione è in una casella non accessibile restituisce il codice errore -1
 *
 * Le coordinate inserite sono corrette (la destinazione non è una casella proibita)
*/
int distance(point from, point to){
    int result;
    int dx = abs(to.x - from.x), dy = abs(to.y - from.y);

    if(dx == dy && dx && dx < 3)
        result = dx;
    else
        result = -1;

    return result;
}

/*
 * Questa funzione si occupa di catturare le pedine indicate.
 * Si assume la correttezza delle coordinate inserite, la legalità della mossa è verificata nella funzione move(...).
*/

void capture(pedina **b, point from, point to){
    point mid;
    pedina *prisoner;
    pedina *soldier;
    
    mid.x = (from.x+to.x)/2;
    mid.y = (to.y+from.y)/2;
    
    prisoner = get_board_value(b,mid);
    soldier = get_board_value(b,from);

    if(prisoner->middle || prisoner->down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        if(get_id_player(prisoner->middle) == get_id_player(soldier) && prisoner->down && get_id_player(prisoner->down) == get_id_player(soldier)) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            prisoner->middle->middle = prisoner->down;
            set_board_value(b,mid,prisoner->middle);
        }
        else if(get_id_player(prisoner->middle) == get_id_player(soldier) && !(prisoner->down)){/*Se la pedina prigioniera ha solo un prigioniero, alleato, l'altra è vuota*/
            set_board_value(b,mid,prisoner->middle);
        }
        else if(get_id_player(prisoner->down) == get_id_player(soldier)){/*Se una delle pedine catturate dal prigioniero è alleata e l'altra è nemica*/
            prisoner->down->middle = prisoner->middle;
            set_board_value(b,mid,prisoner->down);
        }
        else{/*La pedina catturata ha sotto una pedina, nemica*/
            if(!(soldier->down))
                soldier->down = prisoner->middle;

            free(get_board_value(b,mid));
            set_board_value(b,mid,0);
        }

        if(soldier->middle){
            if(!soldier->down)
                soldier->down = prisoner;
        }else
            soldier->middle = prisoner;
        
        prisoner->middle = 0;
        prisoner->down = 0;
    }
    else{ /*In questo ramo la pedina catturata non ha pedine sottostanti*/
        set_board_value(b,mid,0);

        if(soldier->middle && !(soldier->down)){  /*Sistema la pedina catturata nella pedina del catturante*/
            soldier->down = prisoner;
        }
        else {
            soldier->middle = prisoner;
        }
    }

    set_board_value(b,from,0);
    set_board_value(b,to,soldier);
}

/* Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita
*/
int gradeCheck(pedina **board, point from, point to){

    int success = 1;
    if(get_board_value(board,from)) { /* controlla se la casella è piena o vuota*/
        if (!get_grade(get_board_value(board, from))) { /*controlla il grado della pedina*/

            if (!get_id_player(get_board_value(board, from))) {

                if (to.y > from.y){
                    success = 0;
                }

            } else { /*controlla se la pedina appartiene al giocatore 1*/
                if (to.y < from.y) {
                    success = 0;
                }
            }
        }
    } else {
        success = 0;
    }

    return success;

}

/*
* Verifica che la pedina in x,y possa mangiare almeno una pedina avversaria
* Viene verificata prima l'esistenza della casella a distanza due, poi che questa sia libera e che la casella adiacente sia occupata.
* Poi viene verificata la possibilità di mangiare la pedina nella casella adiacente.
*/
int can_eat(pedina **board, point p){
    
    int success;
    id_p current_player;
    gr current_grade;
    
    success = 0;
    
    current_grade = get_grade(get_board_value(board,p));
    current_player = get_id_player(get_board_value(board,p));
    
    if(is_inside(p.x+2,p.y+2) && !get_board_value_immediate(board,p.x+2,p.y+2) && get_board_value_immediate(board,p.x+1,p.y+1) && right_path(Down,current_grade,current_player)){ /*Controllo (p.x+2,p.y+2)*/
            success = get_id_player(get_board_value_immediate(board,p.x + 1,p.y + 1)) != current_player;
    }
    else if(is_inside(p.x+2,p.y-2) && !get_board_value_immediate(board,p.x+2,p.y-2) && get_board_value_immediate(board,p.x+1,p.y-1) && right_path(Up,current_grade,current_player)){
            success = get_id_player(get_board_value_immediate(board,p.x + 1,p.y - 1)) != current_player;
    }
    else if(is_inside(p.x-2,p.y-2) && !get_board_value_immediate(board,p.x-2,p.y-2) && get_board_value_immediate(board,p.x-1,p.y-1) && right_path(Up,current_grade,current_player)){
            success = get_id_player(get_board_value_immediate(board,p.x - 1,p.y - 1)) != current_player;
    }
    else if(is_inside(p.x-2,p.y+2) && !get_board_value_immediate(board,p.x-2,p.y+2) && get_board_value_immediate(board,p.x-1,p.y+1) && right_path(Down,current_grade,current_player)){
            success = get_id_player(get_board_value_immediate(board,p.x - 1,p.y + 1)) != current_player;
    }
            
    return success;
}

/*
* Verifica che la pedina in x,y possa mangiare almeno una pedina avversaria
* Viene verificata prima l'esistenza della casella a distanza due, poi che questa sia libera e che la casella adiacente sia occupata.
* Poi viene verificata la possibilità di mangiare la pedina nella casella adiacente.
*/
int can_move(pedina **board, point p){

    int success = 0;
    id_p current_player;
    gr current_grade;
    
    current_grade = get_grade(get_board_value(board,p));
    current_player = get_id_player(get_board_value(board,p));

    
    if(is_inside(p.x+1,p.y+1) && !get_board_value_immediate(board,p.x+1,p.y+1) && right_path(Down,current_grade,current_player)){ /*Controllo (p.x+2,p.y+2)*/
        success = 1;
    }
    else if(is_inside(p.x+1,p.y-1) && !get_board_value_immediate(board,p.x+1,p.y-1) && right_path(Up,current_grade,current_player)){
        success = 1;
    }
    else if(is_inside(p.x-1,p.y-1) && !get_board_value_immediate(board,p.x-1,p.y-1) && right_path(Up,current_grade,current_player)){
        success = 1;
    }
    else if(is_inside(p.x-1,p.y+1) && !get_board_value_immediate(board,p.x-1,p.y+1) && right_path(Down,current_grade,current_player)){
        success = 1;
    }
    
    return success || can_eat(board,p);
        
}

/* Verifica se, nel caso di non cattura, esiste una cattur obbligatoria da fare
 * Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0
 */
int existMandatory(pedina **board, point from, point to){

    int success;
    unsigned i, j;
    id_p current_player;
    
    success = 0;
    
    if(get_board_value(board,from)){ /*Controllo esistenza*/
        
        current_player = get_id_player(get_board_value(board,from));
    
        if(distance(from,to) != 2 || !can_eat(board,from)){/*Se la pedina di partenza non sta mangiando*/
            point p;
            for(i = 0; i < COL; i++){
                for(j = 0; j < ROW; j++){
                    p.x = i;
                    p.y = j;
                    if(get_board_value(board,p) && (get_id_player(get_board_value(board,p)) == current_player) && can_eat(board,p)){
                        success = 1; /*esite pedina(i,j) && è amica && può mangiare*/
                        break;
                    }
                }
            }
        }
    }

    return success;
}
