#include <string.h>
#include <stdio.h>
#include "game_field.h"
#include "utils.h"
#include "printer_thread.h"
#include <sys/time.h>


game_field* make_game_field(int width, int height, int num_threads) {

    // TODO: Erzeugen Sie ein Spielfeld mit der Breite width und der Höhe height

    // TODO: Initialisieren Sie die erste Generation (Nutzen Sie hierfür die 
	// Funktionen set_glider() und/oder set_glider_gun() aus utils.c) 

    // TODO: Initialisieren Sie alle notwendigen Mutex- und Cond-Objekte sowie
	// weitere Struct-Komponenten (TIPP: Da set_glider/set_glider_gun so tun,
	// als ob die Threads das Spielfeld gefüllt hätten, intialisieren Sie hier
	// field_filled mit der Anzahl der verwendeten Gamer-Threads)
	game_field * game_field = (malloc(sizeof(game_field)));
	game_field->field = (int**)(malloc(sizeof(int)*width));
	for (int i = 0; i < width; i++)
	{
		game_field->field[i] = (int*)(malloc(sizeof(int)*height));
	}
	set_glider_gun(width, height, game_field->field);
	game_field->num_threads = num_threads;
	game_field->width = width;
	game_field->height = height;
	game_field->field_filled = num_threads;
	game_field->field_read = 0;
	pthread_mutex_init(game_field->finished_reading, NULL);
	pthread_mutex_init(game_field->finished_writing, NULL);
	pthread_mutex_init(game_field->finished_printing, NULL);
	pthread_cond_init(game_field->read_lines, NULL);
	pthread_cond_init(game_field->write_cond, NULL);
	pthread_cond_init(game_field->print_cond, NULL);
	//game_field->has_read = (int*)malloc(sizeof(pthread_mutex_t)*num_threads);
	return game_field;
}

int write_to_field(game_field *field, int row_start, int num_rows, int **src_mat) {
	pthread_mutex_lock(field->finished_reading);
	while(!(field->num_finished_reading == field->num_threads))
			pthread_cond_wait(&(field->read_lines), field->finished_reading);
	pthread_mutex_unlock(field->finished_reading);
    // TODO: Stellen Sie sicher, dass jeder Gamer-Thread an dieser Stelle darauf
	// wartet, bis alle anderen Gamer-Threads ihre Ränder ausgelesen haben

    // TODO: Stellen Sie danach sicher, dass jeder Gamer-Thread an dieser Stelle 
	// solange wartet, bis die Ausgabe des Printer-Threads erfolgt
	pthread_cond_wait(field->finished_printing, field->print_cond);

        for (int i = 0; i < num_rows; i++) {
            memcpy(field->field[row_start+i], src_mat[i], field->width*sizeof(int)); 
        }
		
	field->printed = false;
	
	print_game_field(0, NULL, field, NULL);

        // TODO: Zurücksetzen der Print-Bedingungen
        // TODO: Warten Sie darauf, dass alle Gamer-Threads in das Spielfeld 
		// geschrieben haben und starten Sie dann den Printer-Thread

	return 1;
}


void print_game_field(int GUI, SDL_Surface* screen, game_field *field, int** last_field){

    // TODO: Warten Sie darauf, dass das Spielfeld vollständig beschrieben wurde
	pthread_mutex_lock(field->finished_writing);
	while(!(field->num_finished_writing == field->num_threads))
		pthread_cond_wait(&(field->read_lines), field->finished_reading);
	pthread_mutex_lock(field->finished_printing);
	pthread_mutex_unlock(field->finished_reading);
	
	field->num_finished_reading = 0;
	field->num_finished_writing = 0;
	
    if (GUI == 1) {
        update_matrix(screen, field, last_field);
    } else {
        printf("----------------------------------------\n");
        for (int i = 0; i < field->height; i++) {
            for (int j = 0; j < field->width; j++) {
                int elem = field->field[i][j];
                if (elem == 1) {
                    printf("\x1B[31m%d ", elem);
                } else {
                    printf("\x1B[37m%d ", elem);
                }
            }
            printf("\n");
        }
        printf("----------------------------------------\n");
    }
	
    // TODO: Signalisieren Sie den anderen Threads, dass das Spielfeld ausgegeben wurde
	pthread_mutex_lock(field->finished_printing);
	field->printed = 1;
	pthread_cond_broadcast(field->print_cond);
	pthread_mutex_unlock(field->finished_printing);
	
}


void read_adjacent_lines(game_field *field, int height_above, int height_below, int **line_above, int **line_below) {
    memcpy(*line_above, field->field[height_above], field->width*sizeof(int));
    memcpy(*line_below, field->field[height_below], field->width*sizeof(int));

    // TODO: Zählen Sie, wie viele Threads bereits ihre Ränder ausgelesen haben
	pthread_mutex_lock(field->finished_reading);
	field->num_finished_reading++;
	pthread_cond_broadcast(field->read_lines);
	pthread_mutex_unlock(field->finished_reading);
}
