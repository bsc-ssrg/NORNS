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

#ifndef __DAEMON_COMMUNICATION_H__
#define __DAEMON_COMMUNICATION_H__

#include "requests.h"

#pragma GCC visibility push(hidden)

norns_error_t send_submit_request(norns_iotask_t* task);
norns_error_t send_job_request(norns_rpc_type_t type, struct norns_cred* auth, 
                     uint32_t jobid, norns_job_t* job);
norns_error_t send_process_request(norns_rpc_type_t type, struct norns_cred* auth, 
                         uint32_t jobid, uid_t uid, gid_t gid, pid_t pid);
norns_error_t send_backend_request(norns_rpc_type_t type, struct norns_cred* auth, 
                     const char* nsid, norns_backend_t* backend);
norns_error_t send_ping_request();

#pragma GCC visibility pop

#endif /* __DAEMON_COMMUNICATION_H__ */