//
// Copyright (C) 2017 Barcelona Supercomputing Center
//                    Centro Nacional de Supercomputacion
//
// This file is part of the Data Scheduler, a daemon for tracking and managing
// requests for asynchronous data transfer in a hierarchical storage environment.
//
// See AUTHORS file in the top level directory for information
// regarding developers and contributors.
//
// The Data Scheduler is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Data Scheduler is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Data Scheduler.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __URD_HPP__
#define __URD_HPP__

#include <sys/socket.h>
#include <sys/un.h>
#include <ev.h>

#include "ctpl.h"

#include "ipc-listener.hpp"

class urd {

public:
    /* constants */
    static constexpr const char* RUNNING_DIR = "/tmp";
    static constexpr const char* SOCKET_FILE = "/tmp/urd.socket";  
    static constexpr const char* DAEMON_LOCK_FILE = "/tmp/urd.lock";
    static constexpr const char* LOG_FILE = "/tmp/urd.log";
    static const int WAKEUP_PERIODIC_TIME = 5;
    static const int N_THREADS_IN_POOL = 3;
    static const int MAX_CLIENTS_SUPPORTED = 20;

    struct sock_ev_serv {
        ev_io io;
        int fd;
        struct sockaddr_un socket;
        int socket_len;
        int max_clients;
        int current_clients;
    };

    struct sock_ev_client {
        ev_io io;
        int fd;
        int index;
        struct sock_ev_serv *server;
    };

    struct task {
        task(struct norns_iotd* iotdp){
        }

        void operator()(int id) const{
            std::cout << "Hello from a task!\n";
        }

        pid_t       m_pid;
        uint64_t    m_task_id;
        const char* m_path;
    };



public:
    urd();
    void run();

    

private:
    void new_task_handler(struct norns_iotd*);

    void log_message(const char filename[], const char message[]);
    void signal_handler(int sig);
    int set_non_block(int fd);
    int unix_socket_init(sockaddr_un* socket_un, const char* sock_path);
    int server_init(sock_ev_serv *serv, const char *sock_path);

    void communication_thread(int id);
    void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
    sock_ev_client client_new(int fd);
    static void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);

private:

    ipc_listener<struct norns_iotd> m_ipc_listener;
    ctpl::thread_pool m_workers;

};

#endif /* __URD_HPP__ */
