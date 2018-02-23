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

#ifndef __LUSTRE_FS_HPP__
#define __LUSTRE_FS_HPP__

#include "norns/norns_backends.h"
#include "backend-base.hpp"

namespace storage {

class lustre final : public storage::backend {
public:
    lustre(const std::string& mount, uint32_t quota);

    std::string mount() const override;
    uint32_t quota() const override;
    bool accepts(resource_info_ptr res) const override;
    void read_data() const override;
    void write_data() const override;
    std::string to_string() const override;

protected:
    std::string m_mount;
    uint32_t    m_quota;
};

NORNS_REGISTER_BACKEND(NORNS_BACKEND_LUSTRE, lustre);

} // namespace storage

#endif // __LUSTRE_FS_HPP__