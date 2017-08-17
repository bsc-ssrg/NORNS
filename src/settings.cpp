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

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "utils.hpp"
#include "settings.hpp"

namespace bpt = boost::property_tree;

void config_settings::load(const std::string& filename) {

    bpt::ptree pt;

    bpt::read_json(filename, pt);

    m_progname = defaults::progname;

    m_running_dir = pt.get<std::string>("settings.running_dir", "");

    if(m_running_dir == ""){
        m_running_dir = defaults::running_dir;
    }

    m_ipc_sockfile = defaults::ipc_sockfile;
    
    m_daemon_pidfile = pt.get<std::string>("settings.pidfile", "");

    if(m_daemon_pidfile == ""){
        m_daemon_pidfile = defaults::daemon_pidfile;
    }

    m_workers_in_pool = pt.get<int32_t>("settings.workers", 0);

    if(m_workers_in_pool == 0){
        m_workers_in_pool = defaults::workers_in_pool;
    }

    m_storage_path = pt.get<std::string>("settings.storage.path", "");

    if(m_storage_path == "") {
        std::cerr << "Missing storage.path setting in configuration file";
        exit(EXIT_FAILURE);
    }

    auto capacity_str = pt.get<std::string>("settings.storage.capacity", "");

    if(capacity_str == "") {
        std::cerr << "Missing storage.capacity setting in configuration file";
        exit(EXIT_FAILURE);
    }

    try {
        m_storage_capacity = utils::parse_size(capacity_str);
    } catch(std::invalid_argument ex) {
        std::cerr << "Unable to parse storage.capacity parameter '" << capacity_str << "': " << ex.what() << "\n";
        exit(EXIT_FAILURE);
    }

    /* parse storage backends */
    BOOST_FOREACH(bpt::ptree::value_type& bend, pt.get_child("backends")){

        // bend.first == ""
        // make a copy of the ptree so that we can modify it
        bpt::ptree options(bend.second);

        const auto& name = options.get<std::string>("name", "");

        if(name == ""){
            std::cerr << "Missing 'name' in backend definition\n";
            exit(EXIT_FAILURE);
        }

        const auto& type = options.get<std::string>("type", "");

        if(type == ""){
            std::cerr << "Missing 'type' in backend definition\n";
            exit(EXIT_FAILURE);
        }

        const auto& desc = options.get<std::string>("description", "");

        if(desc == ""){
            std::cerr << "Missing 'description' in backend definition\n";
            exit(EXIT_FAILURE);
        }

        const auto& capacity_str = options.get<std::string>("capacity", "");

        if(capacity_str == ""){
            std::cerr << "Missing 'capacity' in backend definition\n";
            exit(EXIT_FAILURE);
        }

        uint64_t capacity;

        try {
            capacity = utils::parse_size(capacity_str);
        } catch(std::invalid_argument ex) {
            std::cerr << "Error parsing backend 'capacity' parameter: '" << capacity_str << "': " << ex.what() << "\n";
            exit(EXIT_FAILURE);
        }

        m_backends.emplace_back(name, type, desc, capacity, options);
    }
}
