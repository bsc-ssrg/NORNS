/* * Copyright (C) 2017 Barcelona Supercomputing Center
 *                    Centro Nacional de Supercomputacion
 *
 * This file is part of the Data Scheduler, a daemon for tracking and managing
 * requests for asynchronous data transfer in a hierarchical storage environment.
 *
 * See AUTHORS file in the top level directory for information
 * regarding developers and contributors.
 *
 * The Data Scheduler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Data Scheduler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Data Scheduler.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <ev.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>

const char* SOCKET_FILE = "/tmp/dloom.socket";

/* Global variables */
int sock;
char buff[10] = "hola";

/* Function declaration */

/* Specify init and finit function as constructor and destructor */

__attribute__((constructor)) static void init(void);
__attribute__((destructor)) static void finit(void); 

struct task{
	pid_t pid;
	uint64_t taskId;
	const char *filePath;
};


void init(void){
	/*
	 * 
	 */	
	printf("Executing this when the library is loaded\n");
	struct sockaddr_un server;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(EXIT_FAILURE);
	}

	server.sun_family = AF_UNIX;
	strncpy(server.sun_path, SOCKET_FILE, sizeof(server.sun_path));
	/*if (strncpy(server.sun_path, SOCKET_FILE, sizeof(server.sun_path)) < 0){
		perror("strncpy");
		exit(EXIT_FAILURE);
	}*/

	if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
        if (close(sock) < 0){
        	exit(EXIT_FAILURE);
        }
        perror("connecting stream socket");
        exit(EXIT_FAILURE);
    }

}

void finit(void){
	/*
	 * 
	 */
	printf("Executing this when the library is unloaded\n");
	close(sock);
}

int push_job(){
	/*
	 * return -1 on error
	 */
	
	struct task t;
	t.pid = 1234;
	t.taskId = 4321;
	t.filePath = "/tmp/something";

	if (write(sock, &t, sizeof(t)) < 0){
        perror("writing on stream socket");
        return -1;
	}
	return 0;
}
