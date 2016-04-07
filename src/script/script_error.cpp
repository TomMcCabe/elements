// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script_error.h"

const char* ScriptErrorString(const ScriptError serror)
{
    switch (serror)
    {
        case SCRIPT_ERR_OK:
            return "No error";
        case SCRIPT_ERR_EVAL_FALSE:
            return "Script evaluated without error but finished with a false/empty top stack element";
        case SCRIPT_ERR_VERIFY:
            return "Script failed an OP_VERIFY operation";
        case SCRIPT_ERR_EQUALVERIFY:
            return "Script failed an OP_EQUALVERIFY operation";
        case SCRIPT_ERR_CHECKMULTISIGVERIFY:
            return "Script failed an OP_CHECKMULTISIGVERIFY operation";
        case SCRIPT_ERR_CHECKSIGVERIFY:
            return "Script failed an OP_CHECKSIGVERIFY operation";
        case SCRIPT_ERR_NUMEQUALVERIFY:
            return "Script failed an OP_NUMEQUALVERIFY operation";
        case SCRIPT_ERR_SCRIPT_SIZE:
            return "Script is too big";
        case SCRIPT_ERR_PUSH_SIZE:
            return "Push value size limit exceeded";
        case SCRIPT_ERR_OP_COUNT:
            return "Operation limit exceeded";
        case SCRIPT_ERR_STACK_SIZE:
            return "Stack size limit exceeded";
        case SCRIPT_ERR_SIG_COUNT:
            return "Signature count negative or greater than pubkey count";
        case SCRIPT_ERR_PUBKEY_COUNT:
            return "Pubkey count negative or limit exceeded";
        case SCRIPT_ERR_BAD_OPCODE:
            return "Opcode missing or not understood";
        case SCRIPT_ERR_DISABLED_OPCODE:
            return "Attempted to use a disabled opcode";
        case SCRIPT_ERR_INVALID_STACK_OPERATION:
            return "Operation not valid with the current stack size";
        case SCRIPT_ERR_INVALID_ALTSTACK_OPERATION:
            return "Operation not valid with the current altstack size";
        case SCRIPT_ERR_OP_RETURN:
            return "OP_RETURN was encountered";
        case SCRIPT_ERR_UNBALANCED_CONDITIONAL:
            return "Invalid OP_IF construction";
        case SCRIPT_ERR_NEGATIVE_LOCKTIME:
            return "Negative locktime";
        case SCRIPT_ERR_UNSATISFIED_LOCKTIME:
            return "Locktime requirement not satisfied";
        case SCRIPT_ERR_SIG_HASHTYPE:
            return "Signature hash type missing or not understood";
        case SCRIPT_ERR_SIG_DER:
            return "Non-canonical DER signature";
        case SCRIPT_ERR_MINIMALDATA:
            return "Data push larger than necessary";
        case SCRIPT_ERR_SIG_PUSHONLY:
            return "Only non-push operators allowed in signatures";
        case SCRIPT_ERR_SIG_HIGH_S:
            return "Non-canonical signature: S value is unnecessarily high";
        case SCRIPT_ERR_SIG_NULLDUMMY:
            return "Dummy CHECKMULTISIG argument must be zero";
        case SCRIPT_ERR_DISCOURAGE_UPGRADABLE_NOPS:
            return "NOPx reserved for soft-fork upgrades";
        case SCRIPT_ERR_PUBKEYTYPE:
            return "Public key is neither compressed or uncompressed";
        case SCRIPT_ERR_WITHDRAW_VERIFY_FORMAT:
            return "Withdraw proof validation failed - invalid proof format";
        case SCRIPT_ERR_WITHDRAW_VERIFY_BLOCK:
            return "Withdraw proof validation failed - SPV proof/block coinbase invalid";
        case SCRIPT_ERR_WITHDRAW_VERIFY_LOCKTX:
            return "Withdraw proof validation failed - locking transaction misformatted";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_ONE:
            return "Withdraw proof validation failed - output does not match expected - ONE";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_TWO:
            return "Withdraw proof validation failed - output does not match expected - TWO";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_THREE:
            return "Withdraw proof validation failed - output does not match expected - THREE";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_FOUR:
            return "Withdraw proof validation failed - output does not match expected - FOUR";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_FIVE:
            return "Withdraw proof validation failed - output does not match expected - FIVE";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_SIX:
            return "Withdraw proof validation failed - output does not match expected - SIX";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_SEVEN:
            return "Withdraw proof validation failed - output does not match expected - SEVEN";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_EIGHT:
            return "Withdraw proof validation failed - output does not match expected - EIGHT";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_NINE:
            return "Withdraw proof validation failed - output does not match expected - NINE";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_TEN:
            return "Withdraw proof validation failed - output does not match expected - TEN";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_ELEVEN:
            return "Withdraw proof validation failed - output does not match expected - ELEVEN";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_TWELVE:
            return "Withdraw proof validation failed - output does not match expected - TWELVE";
        case SCRIPT_ERR_WITHDRAW_VERIFY_OUTPUT_THIRTEEN:
            return "Withdraw proof validation failed - output does not match expected - THIRTEEN";
        case SCRIPT_ERR_WITHDRAW_VERIFY_LOCKTIME:
            return "Withdraw proof validation failed - locktime was not set correctly";
        case SCRIPT_ERR_WITHDRAW_VERIFY_SECONDSCRIPT:
            return "Withdraw proof validation failed - second script validation failed";
        case SCRIPT_ERR_WITHDRAW_VERIFY_BLOCKCONFIRMED:
            return "Withdraw proof validation failed - lock block was not sufficiently confirmed on sending chain";
        case SCRIPT_ERR_WITHDRAW_VALUES_HIDDEN:
            return "Withdraw proof validation failed - values were hidden";
        case SCRIPT_ERR_REORG_VERIFY_FORMAT:
            return "Reorg/Fraud proof validation failed - invalid proof format";
        case SCRIPT_ERR_REORG_VERIFY_FRAUD_BLOCK:
            return "Fraud proof validation failed - bad SPV proof for tx being spent by fraud proof";
        case SCRIPT_ERR_REORG_VERIFY_FRAUD_ORIG_BLOCK:
            return "Fraud proof validation failed - bad SPV proof for original withdraw tx";
        case SCRIPT_ERR_REORG_VERIFY_FRAUD_ORIG_TX:
            return "Fraud proof validation failed - bad or unmatched original withdraw tx";
        case SCRIPT_ERR_REORG_VERIFY_FRAUD_OUTPUT:
            return "Fraud proof validation failed - output does not match expected";
        case SCRIPT_ERR_REORG_VALUES_HIDDEN:
            return "Fraud proof validation failed - values were hidden";
        case SCRIPT_ERR_UNKNOWN_ERROR:
        case SCRIPT_ERR_ERROR_COUNT:
        default: break;
    }
    return "unknown error";
}
