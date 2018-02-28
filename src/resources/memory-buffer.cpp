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

#include <sstream>
#include "backends.hpp"
#include "memory-buffer.hpp"

namespace data {

/*! Memory buffer data */
memory_buffer::memory_buffer(std::string nsid, uint64_t address, std::size_t size)
    : m_nsid(nsid),
      m_address(address),
      m_size(size) {}

memory_buffer::~memory_buffer() { }

resource_type memory_buffer::type() const {
    return resource_type::memory_region;
}

std::string memory_buffer::nsid() const {
    return m_nsid;
}

bool memory_buffer::is_remote() const {
    return false;
}

std::string memory_buffer::to_string() const {
    std::stringstream ss;
    ss << "0x" << std::hex << m_address << "+" << "0x" << m_size;
    return "MEMBUF[" + ss.str() + "]";
}

namespace detail {

resource_impl<resource_type::memory_region>::resource_impl(std::shared_ptr<resource_info> base_info) :
    m_backend(),
    m_resource_info(std::static_pointer_cast<memory_buffer>(base_info)) { }

std::string resource_impl<resource_type::memory_region>::to_string() const {
    return m_backend->to_string() + m_resource_info->to_string();
}

resource_type resource_impl<resource_type::memory_region>::type() const {
    return resource_type::memory_region;
}

void resource_impl<resource_type::memory_region>::set_backend(const backend_ptr backend) {
    m_backend = backend;
}

/* Stream implementation */
stream_impl<resource_type::memory_region>::stream_impl(std::shared_ptr<resource> resource) {
    (void) resource;
}

std::size_t stream_impl<resource_type::memory_region>::read(buffer& b) {
    (void) b;
    return 0;
}

std::size_t stream_impl<resource_type::memory_region>::write(const buffer& b) {
    (void) b;
    return 0;
}

} // namespace detail

} // namespace data
