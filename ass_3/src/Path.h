#ifndef ASS_3_SRC_PATH_H_
#define ASS_3_SRC_PATH_H_

#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace fs = boost::filesystem;

const fs::path build_dir = boost::dll::program_location().parent_path();
const fs::path src_dir = fs::path(build_dir).append("../src");

inline const std::string appendToSourcePath(const std::string& path) {
    return (fs::path(src_dir) /= path).string();
}

#endif