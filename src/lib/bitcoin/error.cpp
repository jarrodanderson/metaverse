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
#include <metaverse/bitcoin/error.hpp>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <metaverse/bitcoin/compat.hpp>
#include <metaverse/bitcoin/utility/log.hpp>

using namespace bc;

class error_category_impl
  : public std::error_category
{
public:
    virtual const char* name() const BC_NOEXCEPT;
    virtual std::string message(int ev) const BC_NOEXCEPT;
    virtual std::error_condition default_error_condition(int ev)
        const BC_NOEXCEPT;
};

static const error_category_impl& get_error_category_instance()
{
    static error_category_impl instance;
    return instance;
}

const char* error_category_impl::name() const BC_NOEXCEPT
{
    return "bitcoin";
}

std::string error_category_impl::message(int ev) const BC_NOEXCEPT
{
    // TODO: use a static map (hash table)
    // This text mapping may change without notice.
    switch (ev)
    {
        case error::success:
            return "success";

        // network errors
        case error::service_stopped:
            return "service is stopped";
        case error::operation_failed:
            return "operation failed";

        // blockchain errors
        case error::not_found:
            return "object does not exist";
        case error::duplicate:
            return "matching previous object found";
        case error::unspent_output:
            return "unspent output";
        case error::unsupported_script_pattern:
            return "unsupport script pattern";

        // network errors (more)
        case error::resolve_failed:
            return "resolving hostname failed";
        case error::network_unreachable:
            return "unable to reach remote host";
        case error::address_in_use:
            return "address already in use";
        case error::listen_failed:
            return "incoming connection failed";
        case error::accept_failed:
            return "connection acceptance failed";
        case error::bad_stream:
            return "bad data stream";
        case error::channel_timeout:
            return "connection timed out";

        // transaction pool
        case error::blockchain_reorganized:
            return "transactions invalidated by blockchain reorganization";
        case error::pool_filled:
            return "forced removal of old transaction from pool overflow";

        // validate tx
        case error::coinbase_transaction:
            return "coinbase transaction disallowed in memory pool";
        case error::is_not_standard:
            return "transaction is not standard";
        case error::invalid_input_script_lock_height:
            return "get coinage reward transaction input script lock heigh value error";
        case error::invalid_output_script_lock_height:
            return "get coinage reward transaction output script lock heigh value error";
        case error::double_spend:
            return "double spend of input";
        case error::input_not_found:
            return "input not found";
        case error::script_not_standard:
            return "script not standard";
        case error::transaction_version_error:
            return "transaction version error";

        // check_transaction()
        case error::empty_transaction:
            return "transaction inputs or outputs are empty";
        case error::output_value_overflow:
            return "output value outside valid range";
        case error::invalid_coinbase_script_size:
            return "coinbase script is too small or large";
        case error::previous_output_null:
            return "non-coinbase transaction has input with null previous output";

        // validate block
        case error::previous_block_invalid:
            return "previous block failed to validate";

        // check_block()
        case error::size_limits:
            return "size limits failed";
        case error::proof_of_work:
            return "proof of work failed";
        case error::futuristic_timestamp:
            return "timestamp too far in the future";
        case error::first_not_coinbase:
            return "first transaction is not a coinbase";
        case error::extra_coinbases:
            return "more than one coinbase";
        case error::too_many_sigs:
            return "too many script signatures";
        case error::merkle_mismatch:
            return "merkle root mismatch";

        // accept_block()
        case error::incorrect_proof_of_work:
            return "proof of work does not match bits field";
        case error::timestamp_too_early:
            return "block timestamp is too early";
        case error::non_final_transaction:
            return "block contains a non-final transaction";
        case error::checkpoints_failed:
            return "block hash rejected by checkpoint";
        case error::old_version_block:
            return "block version rejected at current height";
        case error::coinbase_height_mismatch:
            return "block height mismatch in coinbase";
        case error::block_intermix_interval_error:
            return "block intermix interval dismatch";

        // connect_block()
        case error::duplicate_or_spent:
            return "duplicate transaction with unspent outputs";
        case error::validate_inputs_failed:
            return "validation of inputs failed";
        case error::fees_out_of_range:
            return "fees are out of range";
        case error::coinbase_too_large:
            return "coinbase value is too large";
        case error::invalid_coinage_reward_coinbase:
            return "coinage reward coinbase value is wrong";

        // file system errors
        case error::file_system:
            return "file system error";

        // network errors
        case error::address_blocked:
            return "address is blocked by policy";
        case error::channel_stopped:
            return "channel is stopped";
        case error::not_satisfied:
            return "not satisfied";

        // asset errors
        case error::asset_amount_overflow:
            return "asset amount overflow";
        case error::asset_amount_not_equal:
            return "asset amount not equal";
        case error::asset_symbol_not_match:
            return "asset symbol not match";
        case error::asset_symbol_invalid:
            return "asset symbol invalid";
        case error::asset_address_not_match:
            return "asset attachment address must be equal with output address";
        case error::asset_exist:
            return "asset exist";
        case error::asset_not_exist:
            return "asset not exist";
        case error::asset_issue_error:
            return "issue asset error";
        case error::asset_secondaryissue_error:
            return "secondary issue asset error";
        case error::asset_secondaryissue_share_not_enough:
            return "user asset share is not enought to secondary issue asset ";
        case error::asset_secondaryissue_threshold_invalid:
            return "asset secondaryissue assetshare threshold value invalid";

        // did errors
        case error::did_symbol_not_match:
            return "did symbol not match";
        case error::did_symbol_invalid:
            return "did symbol invalid";
        case error::did_exist:
            return "did exist";
        case error::address_registered_did:
            return "address already registered did";
        case error::did_func_not_actived:
            return "did function has not been actived until block height is larger than 1130000";
        case error::did_address_not_match:
            return "attach did address must equal with output address";
        case error::did_address_needed:
            return "did address is needed but not supplied";
        case error::did_not_exist:
            return "did does not exist";
        case error::did_input_error:
            return "did input error";
        case error::did_multi_type_exist:
            return "did attchment type can not be with some others";
        case error::attenuation_model_param_error:
            return "attenuation model parameter is wrong";

        // cert errors
        case error::asset_cert_error:
            return "asset cert error";
        case error::asset_cert_exist:
            return "asset cert already exists";
        case error::asset_cert_not_exist:
            return "asset cert does not exist";
        case error::asset_cert_not_provided:
            return "asset cert is not provided";
        case error::asset_cert_not_owned:
            return "asset cert is not owned";
        case error::asset_cert_issue_error:
            return "asset cert issue error";

        case error::asset_did_registerr_not_match:
            return "attach todid must equal with asset issuer or cert owner";

        case error::attachment_invalid:
            return "attachment is invalid";

        // features
        case error::nova_feature_not_activated:
            return "nova feature is not activated, it will be activated when block height is larger than 1270000";
        case error::pos_feature_not_activated:
            return "pos feature is not activated, it will be activated when block height is larger than 1924000";
        case error::dpos_feature_not_activated:
            return "dpos feature is not activated, it will be activated when block height is larger than ...";

        // mit errors
        case error::mit_error:
            return "MIT token error";
        case error::mit_exist:
            return "MIT token already exists";
        case error::mit_register_error:
            return "MIT token register error";
        case error::mit_symbol_invalid:
            return "MIT symbol invalid";

        case error::sequence_locked:
            return "transaction currently locked";

        case error::sync_disabled:
            return "block sync is disabled";
        case error::block_version_not_match:
            return "block version not match";
        case error::witness_sign_invalid:
            return "witness sign is invalid";
        case error::witness_mismatch:
            return "witness mismatch";
        case error::witness_vote_error:
            return "witness vote error";
        case error::witness_update_error:
            return "witness update error";

        case error::proof_of_stake:
            return "proof of stake failed";
        case error::illegal_coinstake:
            return "illegal coinstake";
        case error::miss_coinstake:
            return "miss coinstake";
        case error::extra_coinstakes:
            return "more than one coinstake";
        case error::coinstake_version_invalid:
            return "coinstake version invalid";
        case error::block_signature_invalid:
            return "block signature failed";
        case error::check_pos_genesis_error:
            return "check pos genesis block failed";
        case error::mst_coinbase_too_large:
            return "asset coinbase value is too large";
        case error::mst_coinbase_invalid:
            return "asset coinbase value is invalid";

        case error::invalid_output_script_lock_sequence:
            return "invalid output script lock sequence";

        // unknown errors
        case error::unknown:
        default:
            return "unknown error";
    }
}

// We are not currently using this.
std::error_condition error_category_impl::default_error_condition(int ev)
    const BC_NOEXCEPT
{
    return std::error_condition(ev, *this);
}

namespace libbitcoin {
namespace error {

    code make_error_code(error_code_t e)
    {
        return code(e, get_error_category_instance());
    }

    std::error_condition make_error_condition(error_condition_t e)
    {
        return std::error_condition(e, get_error_category_instance());
    }

    error_code_t boost_to_error_code(const boost_code& ec)
    {
        namespace boost_error = boost::system::errc;

#ifdef _MSC_VER
        // TODO: is there a means to map ASIO errors to boost errors?
        // ASIO codes are unique on Windows but not on Linux.
        namespace asio_error = boost::asio::error;
#endif
        // TODO: use a static map (hash table)
        switch (ec.value())
        {
            // There should be no boost mapping to the shutdown sentinel.
            //    return error::service_stopped;

            case boost_error::success:
                return error::success;

            // network errors
#ifdef _MSC_VER
            case asio_error::connection_aborted:
            case asio_error::connection_reset:
            case asio_error::operation_aborted:
            case asio_error::operation_not_supported:
#endif
            case boost_error::connection_aborted:
            case boost_error::connection_refused:
            case boost_error::connection_reset:
            case boost_error::not_connected:
            case boost_error::operation_canceled:
            case boost_error::operation_not_permitted:
            case boost_error::operation_not_supported:
            case boost_error::owner_dead:
            case boost_error::permission_denied:
                return error::operation_failed;

#ifdef _MSC_VER
            case asio_error::address_family_not_supported:
#endif
            case boost_error::address_family_not_supported:
            case boost_error::address_not_available:
            case boost_error::bad_address:
            case boost_error::destination_address_required:
                return error::resolve_failed;

#ifdef _MSC_VER
            case asio_error::connection_refused:
#endif
            case boost_error::broken_pipe:
            case boost_error::host_unreachable:
            case boost_error::network_down:
            case boost_error::network_reset:
            case boost_error::network_unreachable:
            case boost_error::no_link:
            case boost_error::no_protocol_option:
            case boost_error::no_such_file_or_directory:
            case boost_error::not_a_socket:
            case boost_error::protocol_not_supported:
            case boost_error::wrong_protocol_type:
                return error::network_unreachable;

            case boost_error::address_in_use:
            case boost_error::already_connected:
            case boost_error::connection_already_in_progress:
            case boost_error::operation_in_progress:
                return error::address_in_use;

            case boost_error::bad_message:
            case boost_error::illegal_byte_sequence:
            case boost_error::io_error:
            case boost_error::message_size:
            case boost_error::no_message_available:
            case boost_error::no_message:
            case boost_error::no_stream_resources:
            case boost_error::not_a_stream:
            case boost_error::protocol_error:
                return error::bad_stream;

#ifdef _MSC_VER
            case asio_error::timed_out:
#endif
            case boost_error::stream_timeout:
            case boost_error::timed_out:
                return error::channel_timeout;

            // file system errors
            case boost_error::cross_device_link:
            case boost_error::bad_file_descriptor:
            case boost_error::device_or_resource_busy:
            case boost_error::directory_not_empty:
            case boost_error::executable_format_error:
            case boost_error::file_exists:
            case boost_error::file_too_large:
            case boost_error::filename_too_long:
            case boost_error::invalid_seek:
            case boost_error::is_a_directory:
            case boost_error::no_space_on_device:
            case boost_error::no_such_device:
            case boost_error::no_such_device_or_address:
            case boost_error::read_only_file_system:
            // same as operation_would_block on non-windows
            //case boost_error::resource_unavailable_try_again:
            case boost_error::text_file_busy:
            case boost_error::too_many_files_open:
            case boost_error::too_many_files_open_in_system:
            case boost_error::too_many_links:
            case boost_error::too_many_symbolic_link_levels:
                return error::file_system;

            // unknown errors
            case boost_error::argument_list_too_long:
            case boost_error::argument_out_of_domain:
            case boost_error::function_not_supported:
            case boost_error::identifier_removed:
            case boost_error::inappropriate_io_control_operation:
            case boost_error::interrupted:
            case boost_error::invalid_argument:
            case boost_error::no_buffer_space:
            case boost_error::no_child_process:
            case boost_error::no_lock_available:
            case boost_error::no_such_process:
            case boost_error::not_a_directory:
            case boost_error::not_enough_memory:
            case boost_error::operation_would_block:
            case boost_error::resource_deadlock_would_occur:
            case boost_error::result_out_of_range:
            case boost_error::state_not_recoverable:
            case boost_error::value_too_large:
            default:
                return error::unknown;
        }
    }

} // namespace error
} // namespace libbitcoin
