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
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>

#include <norns.h>
//#include <norns-rpc.h>

#include "xmalloc.h"
#include "xstring.h"
#include "daemon-communication.h"


/* Public API */

int 
norns_transfer(struct norns_iotd* iotdp) {

    if(iotdp == NULL) {
        return NORNS_EBADARGS;
    }

    return send_transfer_request(iotdp);
}


/* Register and describe a batch job */
int 
norns_register_job(struct norns_cred* auth, uint32_t jobid, 
                   struct norns_job* job) {

    if(auth == NULL || job == NULL) {
        return NORNS_EBADARGS;
    }

    return send_job_request(NORNS_REGISTER_JOB, auth, jobid, job);
}

/* Update an existing batch job */
int 
norns_update_job(struct norns_cred* auth, uint32_t jobid, 
                 struct norns_job* job) {

    if(auth == NULL || job == NULL) {
        return NORNS_EBADARGS;
    }

    return send_job_request(NORNS_UPDATE_JOB, auth, jobid, job);
}


/* Remove a batch job from the system */
int norns_unregister_job(struct norns_cred* auth, uint32_t jobid) {

    if(auth == NULL) {
        return NORNS_EBADARGS;
    }

    return send_job_request(NORNS_UNREGISTER_JOB, auth, jobid, NULL);
}


/* Add a process to a registered batch job */
int 
norns_add_process(struct norns_cred* auth, uint32_t jobid, uid_t uid,
                  gid_t gid, pid_t pid) {

    if(auth == NULL) {
        return NORNS_EBADARGS;
    }

    return send_process_request(NORNS_ADD_PROCESS, auth, jobid, uid, gid, pid);
}


/* Remove a process from a registered batch job */
int 
norns_remove_process(struct norns_cred* auth, uint32_t jobid, uid_t uid,
                     gid_t gid, pid_t pid) {

    if(auth == NULL) {
        return NORNS_EBADARGS;
    }

    return send_process_request(NORNS_REMOVE_PROCESS, auth, jobid, 
                                uid, gid, pid);
}


