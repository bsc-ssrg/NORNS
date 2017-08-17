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

#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <thread>
#include <list>
#include <boost/property_tree/ptree.hpp>

namespace defaults {
    static constexpr const char* progname = "urd";
    static const bool            daemonize = true;
    static constexpr const char* running_dir = "/tmp";
    static constexpr const char* ipc_sockfile = "/tmp/urd.socket";  
    static constexpr const char* daemon_pidfile = "/tmp/urd.pid";
    static const uint32_t workers_in_pool = std::thread::hardware_concurrency();
} // namespace defaults

namespace bpt = boost::property_tree;

struct config_settings {

    struct backend {

        backend(const std::string& name, const std::string& type, const std::string& description, 
                const uint64_t capacity, const bpt::ptree& options)
            : m_name(name),
              m_type(type),
              m_description(description),
              m_capacity(capacity),
              m_options(options) { }

        const std::string m_name;
        const std::string m_type;
        const std::string m_description;
        const uint64_t    m_capacity;
        const bpt::ptree  m_options;
    };

    void load(const std::string& filename);

    std::string        m_progname;
    bool               m_daemonize;
    std::string        m_running_dir;
    std::string        m_ipc_sockfile;
    std::string        m_daemon_pidfile;
    uint32_t           m_workers_in_pool;
    std::string        m_storage_path;     /* path to internal storage */
    uint64_t           m_storage_capacity; /* internal storage's max capacity */
    std::list<backend> m_backends;         /* list of backend descriptions */
};

#endif /* __SETTINGS_HPP__ */