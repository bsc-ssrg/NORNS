/*************************************************************************
 * Copyright (C) 2017-2018 Barcelona Supercomputing Center               *
 *                         Centro Nacional de Supercomputacion           *
 * All rights reserved.                                                  *
 *                                                                       *
 * This file is part of the NORNS Data Scheduler, a service that allows  *
 * other programs to start, track and manage asynchronous transfers of   *
 * data resources transfers requests between different storage backends. *
 *                                                                       *
 * See AUTHORS file in the top level directory for information           *
 * regarding developers and contributors.                                *
 *                                                                       *
 * The NORNS Data Scheduler is free software: you can redistribute it    *
 * and/or modify it under the terms of the GNU Lesser General Public     *
 * License as published by the Free Software Foundation, either          *
 * version 3 of the License, or (at your option) any later version.      *
 *                                                                       *
 * The NORNS Data Scheduler is distributed in the hope that it will be   *
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 * Lesser General Public License for more details.                       *
 *                                                                       *
 * You should have received a copy of the GNU Lesser General             *
 * Public License along with the NORNS Data Scheduler.  If not, see      *
 * <http://www.gnu.org/licenses/>.                                       *
 *************************************************************************/

#ifndef __NORNSCTL_TYPES_H__
#define __NORNSCTL_TYPES_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

#include "norns_types.h"

/* Additional administrative types */
typedef uint32_t nornsctl_backend_flags_t;
//typedef uint32_t nornsctl_command_t;

/* Administrative command IDs valid for nornsctl_send_command() */
typedef enum {
    NORNSCTL_CMD_PING = 1000,
    NORNSCTL_CMD_PAUSE_LISTEN,
    NORNSCTL_CMD_RESUME_LISTEN,
    NORNSCTL_CMD_SHUTDOWN,
} nornsctl_command_t;


#ifdef __cplusplus
};
#endif

#endif /* __NORNSCTL_TYPES_H__ */
