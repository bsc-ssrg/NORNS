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

#include "norns.h"
#include "nornsctl.h"
#include "catch.hpp"
#include "fake-daemon.hpp"

// enable to test connections with an already running daemon
//#define USE_REAL_DAEMON

SCENARIO("register job", "[api::norns_register_job]") {
    GIVEN("a running urd instance") {

#ifndef USE_REAL_DAEMON
        fake_daemon td;
        td.run();
#endif

        WHEN("a job is registered with invalid information") {

            norns_job_t job = NORNS_JOB(NULL, 0, NULL, 0);

            const uint32_t jobid = 42;

            int rv = norns_register_job(jobid, &job);

            THEN("NORNS_EBADARGS is returned") {
                REQUIRE(rv == NORNS_EBADARGS);
            }
        }

        WHEN("a job is registered with valid information") {

            const char* test_hosts[] = { "host00", "host01" };
            const size_t test_nhosts = sizeof(test_hosts) / sizeof(test_hosts[0]);

            norns_backend_t b0 = NORNS_BACKEND("b0://", NORNS_BACKEND_NVML, "/mnt/b0", 1024);
            norns_backend_t b1 = NORNS_BACKEND("b1://", NORNS_BACKEND_NVML, "/mnt/b1", 2048);
            norns_backend_t b2 = NORNS_BACKEND("b2://", NORNS_BACKEND_NVML, "/mnt/b2", 1024);

            norns_backend_t* test_backends[] = { &b0, &b1, &b2 };

            const size_t test_nbackends = sizeof(test_backends) / sizeof(test_backends[0]);

            norns_job_t job = NORNS_JOB(test_hosts, test_nhosts, test_backends, test_nbackends);

            const uint32_t jobid = 42;

            int rv = norns_register_job(jobid, &job);

            THEN("NORNS_SUCCESS is returned") {
                REQUIRE(rv == NORNS_SUCCESS);
            }
        }

#ifndef USE_REAL_DAEMON
        int ret = td.stop();
        REQUIRE(ret == 0);
#endif
    }

    GIVEN("a non-running urd instance") {
        WHEN("attempting to register a job") {

            const char* test_hosts[] = { "host00", "host01" };
            const size_t test_nhosts = sizeof(test_hosts) / sizeof(test_hosts[0]);

            norns_backend_t b0 = NORNS_BACKEND("b0://", NORNS_BACKEND_NVML, "/mnt/b0", 1024);
            norns_backend_t b1 = NORNS_BACKEND("b1://", NORNS_BACKEND_NVML, "/mnt/b1", 2048);
            norns_backend_t b2 = NORNS_BACKEND("b2://", NORNS_BACKEND_NVML, "/mnt/b2", 1024);

            norns_backend_t* test_backends[] = { &b0, &b1, &b2 };

            const size_t test_nbackends = sizeof(test_backends) / sizeof(test_backends[0]);

            norns_job_t job = NORNS_JOB(test_hosts, test_nhosts, test_backends, test_nbackends);

            const uint32_t jobid = 42;

            int rv = norns_register_job(jobid, &job);

            THEN("NORNS_ECONNFAILED is returned") {
                REQUIRE(rv == NORNS_ECONNFAILED);
            }
        }
    }
}
