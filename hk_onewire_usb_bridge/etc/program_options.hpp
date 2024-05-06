#pragma once

#include <string_view>
#include <optional>
#include <vector>

namespace po
{

using ProgramArguments = std::vector<std::string_view>;

ProgramArguments
fromParameter(int argc, char* argv[])
{
    return std::vector<std::string_view>{argv + 1, argv + argc};
}

bool hasOption(const ProgramArguments& args,
                const std::string_view& option_name)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            return true;
    }

    return false;
}

std::optional<std::string_view>
getOption(const ProgramArguments& args,
          const std::string_view& option_name)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            if (it + 1 != end)
                return *(it + 1);
    }
    return std::nullopt;
}

} // namespace po