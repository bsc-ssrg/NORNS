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

/**
 * This file implements a dispatch table that allows clients to register 
 * callables (i.e. lambdas, functions, functors, etc) and associate them
 * to a user-provided key.
 *
 * Example:
 *
 *  dispatch_table<
 *      api::request_type, 
 *      api::request_type_hash,
 *      response_ptr,
 *      request_ptr
 *          > dispatcher;
 *
 *  dispatcher.add(
 *      api::request_type::job_register,
 *      std::bind(&server::job_register, &ss, std::placeholders::_1));
 *
 *  for(int i=0; i<10; ++i) {
 *      auto req = generate_request();
 *
 *      auto resp = dispatcher.run(req->type(), std::move(req));
 *
 *      ...
 *  }
 */

#ifndef __DISPATCH_TABLE_HPP__
#define  __DISPATCH_TABLE_HPP__

#include <unordered_map>

template <typename Key, typename Hash, typename DispatchReturn, typename... DispatchArgs>
struct dispatch_table {

    template <typename Callable>
    void add(Key k, Callable&& func) {
        m_callbacks.emplace(k, std::forward<Callable>(func));
    }

    DispatchReturn run(Key k, DispatchArgs&&... args) {

        if(!m_callbacks.count(k)) {
            throw std::invalid_argument("Found no callback for provided key");
        }

        return m_callbacks.at(k)(std::forward<DispatchArgs>(args)...);
    }

    std::unordered_map<Key, std::function<DispatchReturn(DispatchArgs...)>, Hash> m_callbacks;
};

#endif /* __DISPATCH_TABLE_HPP__ */
