/************************************************************************* 
 * Copyright (C) 2017-2019 Barcelona Supercomputing Center               *
 *                         Centro Nacional de Supercomputacion           *
 * All rights reserved.                                                  *
 *                                                                       *
 * This file is part of NORNS, a service that allows other programs to   *
 * start, track and manage asynchronous transfers of data resources      *
 * between different storage backends.                                   *
 *                                                                       *
 * See AUTHORS file in the top level directory for information regarding *
 * developers and contributors.                                          *
 *                                                                       *
 * This software was developed as part of the EC H2020 funded project    *
 * NEXTGenIO (Project ID: 671951).                                       *
 *     www.nextgenio.eu                                                  *
 *                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining *
 * a copy of this software and associated documentation files (the       *
 * "Software"), to deal in the Software without restriction, including   *
 * without limitation the rights to use, copy, modify, merge, publish,   *
 * distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to *
 * the following conditions:                                             *
 *                                                                       *
 * The above copyright notice and this permission notice shall be        *
 * included in all copies or substantial portions of the Software.       *
 *                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                 *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS   *
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN    *
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN     *
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE      *
 * SOFTWARE.                                                             *
 *************************************************************************/

#ifndef NORNS_UTILS_TAR_ARCHIVE_HPP
#define NORNS_UTILS_TAR_ARCHIVE_HPP

#include <boost/filesystem.hpp>
#include <system_error>

// forward declare 'struct archive'
struct archive;

namespace bfs = boost::filesystem;

namespace norns {
namespace utils {

struct tar {

    enum class openmode : int {
        create = 0,
        open   = 1,
    };

    constexpr static const auto TAR_BLOCK_SIZE = 512;
    constexpr static const openmode create = openmode::create;
    constexpr static const openmode open = openmode::open;

    tar(const bfs::path& filename, openmode op, std::error_code& ec);

    ~tar();

    void
    add_file(const bfs::path& real_name, 
             const bfs::path& archive_name,
             std::error_code& ec);

    void
    add_directory(const bfs::path& real_dir, 
                  const bfs::path& archive_dir,
                  std::error_code& ec);

    void
    release();

    void
    extract(const bfs::path& parent_dir,
            std::error_code& ec);

    bfs::path
    path() const;

    static std::size_t
    estimate_size_once_packed(const bfs::path& source_path,
                              /*const bfs::path& packed_path,*/
                              std::error_code& ec);

    struct archive* m_archive = nullptr;
    bfs::path m_path;
    openmode m_openmode;
};

} // namespace utils
} // namespace norns

#endif // NORNS_UTILS_TAR_ARCHIVE_HPP