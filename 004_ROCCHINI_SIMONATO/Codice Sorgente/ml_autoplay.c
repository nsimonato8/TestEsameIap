#include"ml_autoplay.h"

/*Ai:
    Soldier: (1,1) , (-1,1) , (2,2) , (-2,2)
    Officer: Soldier, (1,-1) ,(-1,-1) , (2,-2) , (-2,-2)
*/
/*Umano:
    Soldier: (1,-1) ,(-1,-1) , (2,-2) , (-2,-2)
    Officer: Soldier , (1,1) , (-1,1) , (2,2) , (-2,2)
*/

/*
* Invoca minimax e restituisce la mossa (start,end) migliore
*/

int catchInput_Autoplay(pedina **board, int turn, int depth){
    
    t_node result;
    t_node_list possible_moves = NULL, i;
    
    possible_moves = get_moves(board,turn);
    
    for(i = possible_moves; i != NULL; i = i->next){ /*Scorro e valuto tutte le possibili mosse*/
        pedina** new_board;
                
        new_board = cloneMatrix(board);
        
        i->data.value = minimax(new_board,i->data,depth,turn);
        destroyMatrix(new_board);
    }
    
    result = get_from_list(possible_moves,MAX);
    
    destroy_list(possible_moves);
    
    return my_move(board,result.start,result.end,turn);
    
}

int can_be_eaten(pedina **board, point p){
    int success;
    pedina *avversario, *noi;
    int vuoto;
    success = 0;
    
    if((noi = get_board_value(board,p))){
    
        avversario = is_inside(p.x-1,p.y-1)? get_board_value_immediate(board,p.x-1,p.y-1): 0;
        vuoto = is_inside(p.x+1,p.y+1) ? !get_board_value_immediate(board,p.x+1,p.y+1) : 0;
        if(vuoto && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (NW -> SE)*/
            success = (int) avversario->id_player != (int) noi->id_player;
        }
    
        avversario = is_inside(p.x-1,p.y+1)? get_board_value_immediate(board,p.x-1,p.y+1): 0;
        vuoto = is_inside(p.x+1,p.y-1) ? !get_board_value_immediate(board,p.x+1,p.y-1) : 0;
        if(vuoto && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (SW -> NE)*/
            success = (int) avversario->id_player != (int) noi->id_player;
        }
    
        avversario = is_inside(p.x+1,p.y+1)? get_board_value_immediate(board,p.x+1,p.y+1): 0;
        vuoto = is_inside(p.x-1,p.y-1) ? !get_board_value_immediate(board,p.x-1,p.y-1) : 0;
        if(vuoto && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (SE -> NW)*/
            success = (int) avversario->id_player != (int) noi->id_player;
        }
    
        avversario = is_inside(p.x+1,p.y-1)? get_board_value_immediate(board,p.x+1,p.y-1): 0;
        vuoto = is_inside(p.x-1,p.y+1) ? !get_board_value_immediate(board,p.x-1,p.y+1) : 0;
        if(vuoto && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (NE -> SW)*/
            success = (int) avversario->id_player != (int) noi->id_player;
        }
    
    }
    
    return success;
}

/*Valutazione euristica pedina*/
int evaluate(pedina **board){
    
    int res;
    
    if(isWinner(board, Ai))
        res = 20;
    else if (isWinner(board, Umano))
        res = -20;
    else{
        int can_eat_count = 0, can_be_eaten_count = 0;
        point i;
        pedina *aux;
        for(i.y = 0; i.y < ROW; i.y++){
            for(i.x = 0; i.x < COL; i.x++){
                if((int)(aux = get_board_value(board,i)) && ((int)get_id_player(aux) == Ai)){
                    if(can_be_eaten(board,i))
                        can_be_eaten_count++;
                    if(can_eat(board,i))
                        can_eat_count++;
                }
            }
        }
        res = can_eat_count - can_be_eaten_count;
    }
    return res;
    
}

void print_t_node(t_node t){
    printf("(%d,%d)->(%d,%d) ",t.start.x,t.start.y,t.end.x,t.end.y);
}

void print_list(t_node_list i){
    if(i){
        print_t_node(i->data);
        printf(" |-> ");
        print_list(i->next);
    }
}

int prepend(t_node_list *l, t_node val){
    t_node_list new;
    new = (t_node_list) malloc(sizeof(struct s_node_list));
    if(new != NULL)
    {
        new->next = *l;
        new->data = val;
        *l = new;
        return 1;
    }
    else
        return 0;
}

void destroy_list(t_node_list l){
    if(l){
        destroy_list(l->next);
        free(l);
    }
}

int append(t_node_list *l, t_node val){
    if(*l)
        return append(&((*l)->next),val);
    else
        return prepend(l,val);
}

t_node get_from_list(t_node_list l, mode x){
    t_node_list i;
    t_node m;
    
    m.value = (x?INT_MIN:INT_MAX);
    
    for(i = l; i != NULL; i = i->next){
        if((x && i->data.value == 20) || (!x && i->data.value == -20))
            return i->data;
        if((x && i->data.value > m.value) || (!x && i->data.value < m.value))/*se x == MAX prende il massimo, altrimenti il minimo*/
            m = i->data;
    }
    return m;
    
}

point* get_dir(){
    point *res;
    
    res = (point *) malloc(MOSSE*sizeof(point));
    
    res[0].x = 1;
    res[0].y = 1;
    
    res[1].x = 1;
    res[1].y = -1;
    
    res[2].x = -1;
    res[2].y = -1;
    
    res[3].x = -1;
    res[3].y = 1;
    
    res[4].x = 2;
    res[4].y = 2;
    
    res[5].x = 2;
    res[5].y = -2;
    
    res[6].x = -2;
    res[6].y = -2;
    
    res[7].x = -2;
    res[7].y = 2;
        
    return res;
}

/*Calcola tutte le mosse possibili per ogni pedina e restituisce una lista che le contiene. Se il giocatore può muovere viene restituita una lista con un singleton della mossa di cattura*/
t_node_list get_moves(pedina **board, int turn){
    int j, stop = 0;
    point i;
    t_node aux;
    t_node_list possible_moves = NULL;
    extern point *moves;
    
    for(i.y = 0; !stop && i.y < ROW; i.y++){
        for(i.x = 0; !stop && i.x < COL; i.x++){/*Scorro tutte le pedine*/
            if(is_full(board,i) && is_legal_player(board,i,turn)){ /*Seleziono le pedine del giocatore che deve muovere*/
                if(can_eat(board,i)){
                    for(j = 4; !stop && j < MOSSE; j++){
                        if(is_valid_move(board,i,add_point(i,moves[j]),turn)){ /*In caso di possibilità di mangiare elimina le altre mosse e restituisce un singleton con la mossa */
                            aux.start = i;
                            aux.end = add_point(i,moves[j]);
                            aux.value = (turn%2) ? 20 : -20;
                            destroy_list(possible_moves);
                            stop = 1;
                            if(!append(&possible_moves,aux)) /*Controllo su malloc*/
                                printf("get_moves -> append -> malloc failed");
                            
                        }
                    }
                }else{
                    for(j = 0; j < MOSSE; j++){
                        if(is_valid_move(board,i,add_point(i,moves[j]),turn)){
                            aux.start = i;
                            aux.end = add_point(i,moves[j]);
                            aux.value = 0;
                            if(!append(&possible_moves,aux)) /*Controllo su malloc*/
                                printf("get_moves -> append -> malloc failed");
                        }
                    }
                }
            }
        }
    }
    
    return possible_moves;
}

/*Ritorna un indice numerico della bontà della mossa fatta
*
*            Per ogni pedina Ai
*                Per ogni mossa
*                    Se è valida
*                        genera nuova board con stato modificato
*                        ritorna minimax sul nuovo stato e turno modificato
*/
int minimax(pedina **board, t_node movement, int depth, int turn){
    
    int alfa;
    t_node_list new_move, i; /*Lista di mosse non valutate e iteratore*/
    t_node aux;
    
    new_move = NULL;
    i = NULL;
    
    my_move(board,movement.start,movement.end,turn); /*attuo la mossa movement*/

    if(!depth || isWinner(board,Umano) || isWinner(board,Ai)){
        return evaluate(board);
    } else{
        if(turn%2){ /*Gioca AI*/
            
            alfa = INT_MIN;
            
            new_move = get_moves(board, turn); /*Riempe la lista di mosse possibili non valutate*/
            
            for(i = new_move; i != NULL; i = i->next){
                pedina** new_board;
                
                new_board = cloneMatrix(board);
                
                i->data.value = minimax(new_board,i->data,depth - 1,turn + 1);
                destroyMatrix(new_board);
                
                if(i->data.value == 20)
                    return 20;
            }
            
            aux = get_from_list(new_move,MAX); /*Cerco il maggiore*/

            if(aux.value > alfa)
                alfa = aux.value;
        }
        else{ /*Gioca UMANO*/

            alfa = INT_MAX;
            
            new_move = get_moves(board, turn); /*Riempe la lista di mosse possibili non valutate*/
            
            for(i = new_move; i != NULL; i = i->next){
                pedina** new_board;
                
                new_board = cloneMatrix(board);
                
                i->data.value = minimax(new_board,i->data,depth - 1,turn + 1);
                destroyMatrix(new_board);
                
                if(i->data.value == -20)
                    return -20;
            }
            
            aux = get_from_list(new_move,MIN); /*Cerco il minore*/
            
            if(aux.value < alfa)
                alfa = aux.value;
        }
    }
    
    destroy_list(new_move);
    
    return alfa;
}
