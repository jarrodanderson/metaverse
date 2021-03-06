/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2021 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse.
 *
 * metaverse is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <metaverse/bitcoin/config/parser.hpp>

#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>
#include <metaverse/bitcoin/unicode/ifstream.hpp>
#include <metaverse/bitcoin/utility/path.hpp>

namespace libbitcoin {
namespace config {

using namespace boost::filesystem;
using namespace boost::program_options;
using namespace boost::system;

// The error is obtained from boost, which circumvents our localization.
// English-only hack to patch missing arg name in boost exception message.
std::string parser::format_invalid_parameter(const std::string& message)
{
    std::string clean_message(message);
    boost::replace_all(clean_message, "for option is invalid", "is invalid");
    return "{\"error\":\"parser " + clean_message +"\"}";
}

path parser::get_config_option(variables_map& variables,
    const std::string& name)
{
    // read config from the map so we don't require an early notify
    const auto& config = variables[name];

    // prevent exception in the case where the config variable is not set
    if (config.empty())
        return path();

    return config.as<path>();
}

bool parser::get_option(variables_map& variables, const std::string& name)
{
    // Read settings from the map so we don't require an early notify call.
    const auto& variable = variables[name];

    // prevent exception in the case where the settings variable is not set.
    if (variable.empty())
        return false;

    return variable.as<bool>();
}

void parser::load_command_variables(variables_map& variables, int argc,
    const char* argv[])
{
    const auto options = load_options();
    const auto arguments = load_arguments();
    auto command_parser = command_line_parser(argc, argv).options(options)
        /*.allow_unregistered()*/.positional(arguments);
    store(command_parser.run(), variables);
}

void parser::load_environment_variables(variables_map& variables,
    const std::string& prefix)
{
    const auto& environment_variables = load_environment();
    const auto environment = parse_environment(environment_variables, prefix);
    store(environment, variables);
}

bool parser::load_configuration_variables(variables_map& variables,
    const std::string& option_name)
{
    const auto config_settings = load_settings();
    auto config_path = default_data_path() / get_config_option(variables, option_name);

    // If the existence test errors out we pretend there's no file :/.
    error_code code;
    if (!config_path.empty() && exists(config_path, code))
    {
        const auto& path = config_path.string();
        bc::ifstream file(path);

        if (!file.good())
        {
            BOOST_THROW_EXCEPTION(reading_file(path.c_str()));
        }

        const auto config = parse_config_file(file, config_settings);
        store(config, variables);
        return true;
    }

    // Loading from an empty stream causes the defaults to populate.
    std::stringstream stream;
    const auto config = parse_config_file(stream, config_settings);
    store(config, variables);
    return false;
}

} // namespace config
} // namespace libbitcoin
