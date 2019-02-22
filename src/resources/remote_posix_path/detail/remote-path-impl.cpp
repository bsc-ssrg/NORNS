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

#include <system_error>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

#include "resource-type.hpp"
#include "resource.hpp"
#include "remote-path-info.hpp"
#include "remote-path-impl.hpp"
#include "backends/remote-backend.hpp"

namespace norns {
namespace data {
namespace detail {

// remote alias for convenience
using remote_path_resource = resource_impl<resource_type::remote_posix_path>;

remote_path_resource::resource_impl(
    const std::shared_ptr<const storage::backend> parent)
    : m_parent(std::static_pointer_cast<const storage::detail::remote_backend>(
          std::move(parent))) {}

std::string remote_path_resource::name() const {
    return "PENDING: " + m_parent->to_string();
}

resource_type remote_path_resource::type() const {
    return resource_type::remote_posix_path;
}

bool remote_path_resource::is_collection() const {
    return false;
}

std::size_t
remote_path_resource::packed_size() const {
    return 0;
}

const std::shared_ptr<const storage::backend>
remote_path_resource::parent() const {
    return std::static_pointer_cast<const storage::backend>(m_parent);
}

std::string remote_path_resource::to_string() const {
    return "node42@/foo/bar/baz";
}

} // namespace detail
} // namespace data
} // namespace norns
