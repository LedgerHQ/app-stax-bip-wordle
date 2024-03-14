#pragma once

/**
 * Instruction class of the Hello-World application.
 */
#define CLA 0xE0

/**
 * Length of APPNAME variable in the Makefile.
 */
#define APPNAME_LEN (sizeof(APPNAME) - 1)

/**
 * Maximum length of MAJOR_VERSION || MINOR_VERSION || PATCH_VERSION.
 */
#define APPVERSION_LEN 3

/**
 * Maximum length of application name.
 */
#define MAX_APPNAME_LEN 64

/**
 * Maximum transaction length (bytes).
 */
#define MAX_TRANSACTION_LEN 510

/**
 * Maximum signature length (bytes).
 */
#define MAX_DER_SIG_LEN 72

/**
 * Exponent used to convert mBOL to BOL unit (N BOL = N * 10^3 mBOL).
 */
#define EXPONENT_SMALLEST_UNIT 3

////////////////////////////////////////////////////////////////////////////////
// Hash
static const size_t HASH_20_LEN     = 20;
static const size_t HASH_32_LEN     = 32;
static const size_t HASH_64_LEN     = 64;

////////////////////////////////////////////////////////////////////////////////
// Identities
static const size_t ADDRESS_LEN                     = 34;
static const size_t ADDRESS_HASH_LEN                = 21;
static const size_t ADDRESS_MAX_BIP32_PATH          = 10;
static const size_t PUBLICKEY_COMPRESSED_LEN        = 33;
static const size_t PUBLICKEY_UNCOMPRESSED_LEN      = 65;

////////////////////////////////////////////////////////////////////////////////
// Signatures
static const size_t SIG_ECDSA_MIN_LEN   = 64;
static const size_t SIG_ECDSA_MAX_LEN   = 72;
static const size_t SIG_SCHNORR_LEN     = HASH_64_LEN;
////////////////////////////////////////////////////////////////////////////////
// General
#if defined(SUPPORTS_LARGE_OPERATIONS)
    static const size_t MAX_RAW_OPERATION   = 2496;     // 64-byte-aligned
#else
    static const size_t MAX_RAW_OPERATION   = 704;      // 64-byte-aligned
#endif

static const size_t MAX_TEXT_LEN = 255;
////////////////////////////////////////////////////////////////////////////////
// Numbers
static const uint64_t UINT64_BASE_10 = 10U;