#ifndef __IO_TASK_MOVE_HPP__
#define __IO_TASK_MOVE_HPP__

namespace norns {
namespace io {

/////////////////////////////////////////////////////////////////////////////////
//   specializations for move tasks 
/////////////////////////////////////////////////////////////////////////////////
template<>
inline void 
task<iotask_type::move>::operator()() {

    std::error_code ec;

    const auto tid = m_task_info->id();
    const auto type = m_task_info->type();
    const auto src_backend = m_task_info->src_backend();
    const auto src_rinfo = m_task_info->src_rinfo();
    const auto dst_backend = m_task_info->dst_backend();
    const auto dst_rinfo = m_task_info->dst_rinfo();
    const auto auth = m_task_info->auth();

    // helper lambda for error reporting 
    const auto log_error = [&] (const std::string& msg) {
        m_task_info->update_status(task_status::finished_with_error,
                                   urd_error::system_error, ec);

        std::string r_msg = "[{}] " + msg + ": {}";

        LOGGER_ERROR(r_msg.c_str(), tid, ec.message());
        LOGGER_WARN("[{}] I/O task completed with error", tid);
    };

    LOGGER_WARN("[{}] Starting I/O task", tid);
    LOGGER_WARN("[{}]   TYPE: {}", tid, utils::to_string(type));
    LOGGER_WARN("[{}]   FROM: {}", tid, src_backend->to_string());
    LOGGER_WARN("[{}]     TO: {}", tid, dst_backend->to_string());

    m_task_info->update_status(task_status::running);

    auto src = src_backend->get_resource(src_rinfo, ec);

    if(ec) {
        log_error("Could not access input data " + src_rinfo->to_string());
        return;
    }

    auto dst = dst_backend->new_resource(dst_rinfo, src->is_collection(), ec);

    if(ec) {
        log_error("Could not create output data " + dst_rinfo->to_string());
        return;
    }

    ec = m_transferor->transfer(auth, m_task_info, src, dst);

    if(ec) {
        log_error("Transfer failed");
        return;
    }

    LOGGER_WARN("[{}] I/O task completed successfully [{} MiB/s]", 
                tid, m_task_info->bandwidth());

    m_task_info->update_status(task_status::finished, urd_error::success, 
                    std::make_error_code(static_cast<std::errc>(ec.value())));
}

} // namespace io
} // namespace norns

#endif // __IO_TASK_MOVE_HPP__
