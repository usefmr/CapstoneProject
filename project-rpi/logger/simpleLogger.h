#ifndef simpleLogger_h__
#define simpleLogger_h__

#define BOOST_LOG_DYN_LINK

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
// the logs are also written to LOGFILE
#define LOGFILE "/home/youssef/project/run_logs.log"

// just log messages with severity >= SEVERITY_THRESHOLD are written
#define SEVERITY_THRESHOLD logging::trivial::trace

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

// ===== log macros =====
#define LOG_TRACE   LOG(trace)
#define LOG_DEBUG   LOG(debug)
#define LOG_INFO    LOG(info)
#define LOG_WARNING LOG(warning)
#define LOG_ERROR   LOG(error)
#define LOG_FATAL   LOG(fatal)
//void auto_flush(bool = true);

#endif
