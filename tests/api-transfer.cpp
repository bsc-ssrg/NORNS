/*************************************************************************
 * Copyright (C) 2017-2018 Barcelona Supercomputing Center               *
 *                         Centro Nacional de Supercomputacion           *
 *                                                                       *
 * This file is part of the Data Scheduler, a daemon for tracking and    *
 * managing requests for asynchronous data transfer in a hierarchical    *
 * storage environment.                                                  *
 *                                                                       *
 * See AUTHORS file in the top level directory for information           *
 * regarding developers and contributors.                                *
 *                                                                       *
 * The Data Scheduler is free software: you can redistribute it and/or   *
 * modify it under the terms of the GNU Lesser General Public License    *
 * as published by the Free Software Foundation, either version 3 of     *
 * the License, or (at your option) any later version.                   *
 *                                                                       *
 * The Data Scheduler is distributed in the hope that it will be useful, *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 * Lesser General Public License for more details.                       *
 *                                                                       *
 * You should have received a copy of the GNU Lesser General             *
 * Public License along with Data Scheduler.  If not, see                *
 * <http://www.gnu.org/licenses/>.                                       *
 *                                                                       *
 *************************************************************************/

#include "fake-daemon.hpp"

#include "catch.hpp"

#include <chrono>
#include <norns.h>
#include <urd.hpp>
#include <settings.hpp>

#include "fake-daemon.hpp"

//#define USE_REAL_DAEMON

SCENARIO("transfer request", "[api::norns_transfer]") {
    GIVEN("a running urd instance") {

#ifndef USE_REAL_DAEMON
//        extern const char* norns_api_sockfile;
//        norns_api_sockfile = "./test_urd.socket";

        fake_daemon td;
        td.run();
#endif



        WHEN("requesting a transfer") {

            struct norns_iotd iotd = NORNS_IOTD_INIT(
                NORNS_COPY, 
                NORNS_INPUT_PATH_INIT(
                    NORNS_BACKEND_LOCAL_NVML,
                    NORNS_LOCAL_PATH_INIT("nvml0://a/b/c")),
                NORNS_OUTPUT_PATH_INIT(
                    NORNS_BACKEND_REMOTE_NVML,
                    NORNS_REMOTE_PATH_INIT("host0", "nvml1://a/b/d"))
            );

            int rv = norns_transfer(&iotd);

            THEN("NORNS_SUCCESS is returned") {
                REQUIRE(rv == NORNS_SUCCESS);
                REQUIRE(iotd.io_taskid != 0);
            }
        }

#ifndef USE_REAL_DAEMON
        int ret = td.stop();
        REQUIRE(ret == 0);
#endif
    }

#if 0
    GIVEN("a non-running urd instance") {
        WHEN("attempting to request a transfer") {

            struct norns_iotd iotd = NORNS_IOTD_INIT(
                NORNS_COPY, 
                NORNS_INPUT_PATH_INIT(
                    NORNS_BACKEND_LOCAL_NVML,
                    NORNS_LOCAL_PATH_INIT("nvml0://a/b/c")),
                NORNS_OUTPUT_PATH_INIT(
                    NORNS_BACKEND_REMOTE_NVML,
                    NORNS_REMOTE_PATH_INIT("host0", "nvml1://a/b/d"))
            );

            int rv = norns_transfer(&iotd);

            THEN("NORNS_ECONNFAILED is returned") {
                REQUIRE(rv == NORNS_ECONNFAILED);
            }
        }
    }
#endif
}
