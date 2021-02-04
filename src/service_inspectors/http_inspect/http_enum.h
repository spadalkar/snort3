//--------------------------------------------------------------------------
// Copyright (C) 2014-2020 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------
// http_enum.h author Tom Peters <thopeter@cisco.com>

#ifndef HTTP_ENUM_H
#define HTTP_ENUM_H

#include <cstdint>

namespace HttpEnums
{
static const int MAX_OCTETS = 63780;
static const int GZIP_BLOCK_SIZE = 2048;
static const int MAX_SECTION_STRETCH = 1460;

static const uint32_t HTTP_GID = 119;
static const int GZIP_WINDOW_BITS = 31;
static const int DEFLATE_WINDOW_BITS = 15;
static const int MAX_FIELD_NAME_LENGTH = 100;
// Plan to support max 8 xff headers
static const uint8_t MAX_XFF_HEADERS = 8;
static const uint8_t MAX_CUSTOM_HEADERS = MAX_XFF_HEADERS;

// This can grow into a bitmap for the get_buf() form parameter
static const uint64_t FORM_REQUEST = 0x1;

// Type of message section
enum SectionType { SEC_DISCARD = -19, SEC_ABORT = -18, SEC__NOT_COMPUTE=-14, SEC__NOT_PRESENT=-11,
    SEC_REQUEST = 2, SEC_STATUS, SEC_HEADER, SEC_BODY_CL, SEC_BODY_CHUNK, SEC_TRAILER,
    SEC_BODY_OLD, SEC_BODY_H2 };

enum DetectionStatus { DET_REACTIVATING = 1, DET_ON, DET_DEACTIVATING, DET_OFF };

// Message buffers available to clients
// This enum must remain synchronized with HttpApi::classic_buffer_names[]
enum HTTP_BUFFER { HTTP_BUFFER_CLIENT_BODY = 1, HTTP_BUFFER_COOKIE, HTTP_BUFFER_HEADER,
    HTTP_BUFFER_METHOD, HTTP_BUFFER_PARAM, HTTP_BUFFER_RAW_BODY, HTTP_BUFFER_RAW_COOKIE,
    HTTP_BUFFER_RAW_HEADER, HTTP_BUFFER_RAW_REQUEST, HTTP_BUFFER_RAW_STATUS,
    HTTP_BUFFER_RAW_TRAILER, HTTP_BUFFER_RAW_URI, HTTP_BUFFER_STAT_CODE, HTTP_BUFFER_STAT_MSG,
    HTTP_BUFFER_TRAILER, HTTP_BUFFER_TRUE_IP, HTTP_BUFFER_URI, HTTP_BUFFER_VERSION,
    HTTP_BUFFER_MAX };

// Peg counts
// This enum must remain synchronized with HttpModule::peg_names[] in http_tables.cc
enum PEG_COUNT { PEG_FLOW = 0, PEG_SCAN, PEG_REASSEMBLE, PEG_INSPECT, PEG_REQUEST, PEG_RESPONSE,
    PEG_GET, PEG_HEAD, PEG_POST, PEG_PUT, PEG_DELETE, PEG_CONNECT, PEG_OPTIONS, PEG_TRACE,
    PEG_OTHER_METHOD, PEG_REQUEST_BODY, PEG_CHUNKED, PEG_URI_NORM, PEG_URI_PATH, PEG_URI_CODING,
    PEG_CONCURRENT_SESSIONS, PEG_MAX_CONCURRENT_SESSIONS, PEG_DETAINED, PEG_SCRIPT_DETECTION,
    PEG_PARTIAL_INSPECT, PEG_EXCESS_PARAMS, PEG_PARAMS, PEG_CUTOVERS, PEG_SSL_SEARCH_ABND_EARLY,
    PEG_PIPELINED_FLOWS, PEG_PIPELINED_REQUESTS, PEG_TOTAL_BYTES, PEG_COUNT_MAX };

// Result of scanning by splitter
enum ScanResult { SCAN_NOT_FOUND, SCAN_NOT_FOUND_ACCELERATE, SCAN_FOUND, SCAN_FOUND_PIECE,
    SCAN_DISCARD, SCAN_DISCARD_PIECE, SCAN_ABORT };

// State machine for chunk parsing
enum ChunkState { CHUNK_NEWLINES, CHUNK_ZEROS, CHUNK_LEADING_WS, CHUNK_NUMBER, CHUNK_TRAILING_WS,
    CHUNK_OPTIONS, CHUNK_HCRLF, CHUNK_DATA, CHUNK_DCRLF1, CHUNK_DCRLF2, CHUNK_BAD };

enum AcceleratedBlocking { AB_DETAIN, AB_INSPECT, AB_NONE };

// List of possible HTTP versions.
enum VersionId { VERS__NO_SOURCE=-16, VERS__NOT_COMPUTE=-14, VERS__PROBLEMATIC=-12,
    VERS__NOT_PRESENT=-11, VERS__OTHER=1, VERS_1_0, VERS_1_1, VERS_2_0, VERS_0_9 };

// Every request method we have ever heard of
enum MethodId {
    METH__NO_SOURCE=-16, METH__NOT_COMPUTE=-14, METH__PROBLEMATIC=-12,
    METH__NOT_PRESENT=-11, METH__OTHER=1, METH_OPTIONS, METH_GET,
    METH_HEAD, METH_POST, METH_PUT, METH_DELETE, METH_TRACE, METH_CONNECT,
    METH_VERSION_CONTROL, METH_REPORT, METH_CHECKOUT, METH_CHECKIN,
    METH_UNCHECKOUT, METH_MKWORKSPACE, METH_UPDATE, METH_LABEL, METH_MERGE,
    METH_BASELINE_CONTROL, METH_MKACTIVITY, METH_ORDERPATCH, METH_ACL,
    METH_PATCH, METH_BIND, METH_LINK, METH_MKCALENDAR, METH_MKREDIRECTREF,
    METH_REBIND, METH_UNBIND, METH_UNLINK, METH_UPDATEREDIRECTREF,

    METH__WEBDAV_LOW=1000,  // All WebDAV related methods go after this.
    METH_PROPFIND, METH_PROPPATCH, METH_MKCOL, METH_COPY, METH_MOVE,
    METH_LOCK, METH_UNLOCK, METH_SEARCH, METH_BCOPY, METH_BDELETE,
    METH_BMOVE, METH_BPROPFIND, METH_BPROPPATCH, METH_NOTIFY, METH_POLL,
    METH_SUBSCRIBE, METH_UNSUBSCRIBE, METH_X_MS_ENUMATTS,
    METH__WEBDAV_HIGH       // All WebDAV related methods go before this.
};

// URI formats
enum UriType { URI__NOT_COMPUTE=-14, URI__PROBLEMATIC=-12, URI_ASTERISK = 2, URI_AUTHORITY,
    URI_ORIGIN, URI_ABSOLUTE };

// Body compression types
enum CompressId { CMP_NONE=2, CMP_GZIP, CMP_DEFLATE };

// Message section in which an IPS option provides the buffer
enum InspectSection { IS_NONE, IS_HEADER, IS_FLEX_HEADER, IS_FIRST_BODY, IS_BODY, IS_TRAILER };

// Part of the URI to be provided
enum UriComponent { UC_SCHEME = 1, UC_HOST, UC_PORT, UC_PATH, UC_QUERY, UC_FRAGMENT };

// Every header we have ever heard of
enum HeaderId { HEAD__NOT_COMPUTE=-14, HEAD__PROBLEMATIC=-12, HEAD__NOT_PRESENT=-11, HEAD__OTHER=1,
    HEAD_CACHE_CONTROL, HEAD_CONNECTION, HEAD_DATE, HEAD_PRAGMA, HEAD_TRAILER, HEAD_COOKIE,
    HEAD_SET_COOKIE, HEAD_TRANSFER_ENCODING, HEAD_UPGRADE, HEAD_VIA, HEAD_WARNING, HEAD_ACCEPT,
    HEAD_ACCEPT_CHARSET, HEAD_ACCEPT_ENCODING, HEAD_ACCEPT_LANGUAGE, HEAD_AUTHORIZATION,
    HEAD_EXPECT, HEAD_FROM, HEAD_HOST, HEAD_IF_MATCH, HEAD_IF_MODIFIED_SINCE, HEAD_IF_NONE_MATCH,
    HEAD_IF_RANGE, HEAD_IF_UNMODIFIED_SINCE, HEAD_MAX_FORWARDS, HEAD_PROXY_AUTHORIZATION,
    HEAD_RANGE, HEAD_REFERER, HEAD_TE, HEAD_USER_AGENT, HEAD_ACCEPT_RANGES, HEAD_AGE, HEAD_ETAG,
    HEAD_LOCATION, HEAD_PROXY_AUTHENTICATE, HEAD_RETRY_AFTER, HEAD_SERVER, HEAD_VARY,
    HEAD_WWW_AUTHENTICATE, HEAD_ALLOW, HEAD_CONTENT_ENCODING, HEAD_CONTENT_LANGUAGE,
    HEAD_CONTENT_LENGTH, HEAD_CONTENT_LOCATION, HEAD_CONTENT_MD5, HEAD_CONTENT_RANGE,
    HEAD_CONTENT_TYPE, HEAD_EXPIRES, HEAD_LAST_MODIFIED, HEAD_X_FORWARDED_FOR, HEAD_TRUE_CLIENT_IP,
    HEAD_X_WORKING_WITH, HEAD_CONTENT_TRANSFER_ENCODING, HEAD_MIME_VERSION, HEAD_PROXY_AGENT,
    HEAD_CONTENT_DISPOSITION, HEAD__MAX_VALUE };

// All the infractions we might find while parsing and analyzing a message
enum Infraction
{
    INF__NONE = -1,
    INF_BARE_BYTE = 0,
    INF_HEAD_TOO_LONG,
    INF_BAD_REQ_LINE,
    INF_BAD_STAT_LINE,
    INF_TOO_MANY_HEADERS,
    INF_BAD_HEADER,
    INF_BAD_STAT_CODE,
    INF_UNKNOWN_VERSION,
    INF_BAD_VERSION,
    INF_ZERO_NINE_NOT_FIRST,
    INF_CODE_POINT_IN_URI,
    INF_BAD_CONTENT_LENGTH,
    INF_PIPELINE_OVERFLOW,
    INF_BAD_CHUNK_SIZE,
    INF_BAD_PHRASE,
    INF_BAD_URI,
    INF_ZERO_NINE_REQ,
    INF_ZERO_NINE_CONTINUE,
    INF_URI_PERCENT_UTF8_3B,
    INF_URI_PERCENT_UNRESERVED,
    INF_URI_PERCENT_UTF8_2B,
    INF_URI_NEED_NORM_SCHEME,
    INF_URI_PERCENT_OTHER,
    INF_URI_BAD_CHAR,
    INF_URI_8BIT_CHAR,
    INF_URI_MULTISLASH,
    INF_BACKSLASH_IN_URI,
    INF_URI_SLASH_DOT,
    INF_URI_SLASH_DOT_DOT,
    INF_URI_ROOT_TRAV,
    INF_TOO_MUCH_LEADING_WS,
    INF_WS_BETWEEN_MSGS,
    INF_ENDLESS_HEADER,
    INF_LF_WITHOUT_CR,
    INF_NOT_HTTP,
    INF_NO_URI,
    INF_REQUEST_WS,
    INF_REQUEST_TAB,
    INF_STATUS_WS,
    INF_STATUS_TAB,
    INF_URI_SPACE,
    INF_TOO_LONG_HEADER,
    INF_CR_WITHOUT_LF,
    INF_CHUNK_ZEROS,
    INF_CHUNK_OPTIONS,
    INF_CHUNK_BAD_CHAR,
    INF_CHUNK_TOO_LARGE,
    INF_CHUNK_BARE_LF,
    INF_CHUNK_LONE_CR,
    INF_CHUNK_NO_LENGTH,
    INF_CHUNK_BAD_END,
    INF_PARTIAL_START,
    INF_CHUNK_WHITESPACE,
    INF_HEAD_NAME_WHITESPACE,
    INF_GZIP_OVERRUN,
    INF_GZIP_FAILURE,
    INF_GZIP_EARLY_END,
    INF_URI_NEED_NORM_PATH,
    INF_URI_NEED_NORM_HOST,
    INF_URI_NEED_NORM_QUERY,
    INF_URI_NEED_NORM_FRAGMENT,
    INF_URI_U_ENCODE,
    INF_URI_UNKNOWN_PERCENT,
    INF_URI_DOUBLE_DECODE,
    INF_MULTIPLE_CONTLEN,
    INF_BOTH_CL_AND_TE,
    INF_BAD_CODE_BODY_HEADER,
    INF_BAD_TE_HEADER,
    INF_PADDED_TE_HEADER,
    INF_OVERSIZE_DIR,
    INF_POST_WO_BODY,
    INF_UTF_NORM_FAIL,
    INF_UTF7,
    INF_UNSUPPORTED_ENCODING,
    INF_UNKNOWN_ENCODING,
    INF_STACKED_ENCODINGS,
    INF_JS_OBFUSCATION_EXCD,
    INF_JS_EXCESS_WS,
    INF_MIXED_ENCODINGS,
    INF_RESPONSE_WO_REQUEST,
    INF_SWF_ZLIB_FAILURE,
    INF_SWF_LZMA_FAILURE,
    INF_PDF_DEFL_FAILURE,
    INF_PDF_UNSUP_COMP_TYPE,
    INF_PDF_CASC_COMP,
    INF_PDF_PARSE_FAILURE,
    INF_FILE_DECOMPR_OVERRUN,
    INF_BAD_CHAR_IN_HEADER_NAME,
    INF_HEADER_WRAPPING,
    INF_CHUNK_BAD_SEP,
    INF_MULTIPLE_100_RESPONSES,
    INF_UNEXPECTED_100_RESPONSE,
    INF_UNKNOWN_1XX_STATUS,
    INF_EXPECT_WITHOUT_BODY_CL0,
    INF_EXPECT_WITHOUT_BODY_NO_CL,
    INF_CHUNKED_ONE_POINT_ZERO,
    INF_CTE_HEADER,
    INF_ILLEGAL_TRAILER,
    INF_REPEATED_HEADER,
    INF_CONTENT_ENCODING_CHUNKED,
    INF_206_WITHOUT_RANGE,
    INF_VERSION_NOT_UPPERCASE,
    INF_CHUNK_LEADING_WS,
    INF_BAD_HEADER_WHITESPACE,
    INF_H2_NON_IDENTITY_TE,
    INF_H2_DATA_OVERRUNS_CL,
    INF_H2_DATA_UNDERRUNS_CL,
    INF_CONNECT_REQUEST_BODY,
    INF_EARLY_C2S_TRAFFIC_AFTER_CONNECT,
    INF_200_CONNECT_RESP_WITH_CL,
    INF_200_CONNECT_RESP_WITH_TE,
    INF_100_CONNECT_RESP,
    INF_EARLY_CONNECT_RESPONSE,
    INF_MALFORMED_CD_FILENAME,
    INF_HTTP2_IN_HI,
    INF_TRUNCATED_MSG_BODY_CL,
    INF_TRUNCATED_MSG_BODY_CHUNK,
    INF_LONG_SCHEME,
    INF_MULTIPLE_HOST_HDRS,
    INF__MAX_VALUE
};

// Types of character for URI scanning
enum CharAction { CHAR_NORMAL=2, CHAR_PERCENT, CHAR_PATH, CHAR_EIGHTBIT, CHAR_SUBSTIT };

// Content codings
enum Contentcoding { CONTENTCODE__OTHER=1, CONTENTCODE_GZIP, CONTENTCODE_DEFLATE,
    CONTENTCODE_COMPRESS, CONTENTCODE_EXI, CONTENTCODE_PACK200_GZIP, CONTENTCODE_X_GZIP,
    CONTENTCODE_X_COMPRESS, CONTENTCODE_IDENTITY, CONTENTCODE_CHUNKED, CONTENTCODE_BR,
    CONTENTCODE_BZIP2, CONTENTCODE_LZMA, CONTENTCODE_PEERDIST, CONTENTCODE_SDCH,
    CONTENTCODE_XPRESS, CONTENTCODE_XZ };

enum EventSid
{
    EVENT__NONE = -1,
    EVENT_ASCII = 1,
    EVENT_DOUBLE_DECODE = 2,
    EVENT_U_ENCODE = 3,
    EVENT_BARE_BYTE = 4,
    // EVENT_OBSOLETE_BASE_36 = 5,   // Previously used, do not reuse this number
    EVENT_UTF_8 = 6,
    EVENT_CODE_POINT_IN_URI = 7,
    EVENT_MULTI_SLASH = 8,
    EVENT_BACKSLASH_IN_URI = 9,
    EVENT_SELF_DIR_TRAV = 10,
    EVENT_DIR_TRAV = 11,
    EVENT_APACHE_WS = 12,
    EVENT_LF_WITHOUT_CR = 13,
    EVENT_NON_RFC_CHAR = 14,
    EVENT_OVERSIZE_DIR = 15,
    // EVENT_LARGE_CHUNK = 16,
    // EVENT_PROXY_USE = 17,
    EVENT_WEBROOT_DIR = 18,
    EVENT_LONG_HDR = 19,
    EVENT_MAX_HEADERS = 20,
    EVENT_MULTIPLE_CONTLEN = 21,
    // EVENT_OBSOLETE_CHUNK_SIZE_MISMATCH = 22,   // Previously used, do not reuse this number
    // EVENT_INVALID_TRUEIP = 23,
    EVENT_MULTIPLE_HOST_HDRS = 24,
    // EVENT_LONG_HOSTNAME = 25,
    // EVENT_EXCEEDS_SPACES = 26,
    // EVENT_CONSECUTIVE_SMALL_CHUNKS = 27,
    EVENT_UNBOUNDED_POST = 28,
    // EVENT_MULTIPLE_TRUEIP_IN_SESSION = 29,
    // EVENT_BOTH_TRUEIP_XFF_HDRS = 30,
    EVENT_UNKNOWN_METHOD = 31,
    EVENT_SIMPLE_REQUEST = 32,
    EVENT_UNESCAPED_SPACE_URI = 33,
    EVENT_PIPELINE_MAX = 34,

    // EVENT_OBSOLETE_ANOM_SERVER = 101,      // Previously used, do not reuse this number
    EVENT_INVALID_STATCODE = 102,
    // EVENT_UNUSED_1 = 103,
    EVENT_UTF_NORM_FAIL = 104,
    EVENT_UTF7 = 105,
    // EVENT_DECOMPR_FAILED = 106,
    // EVENT_CONSECUTIVE_SMALL_CHUNKS_S = 107,
    // EVENT_UNUSED_2 = 108,
    EVENT_JS_OBFUSCATION_EXCD = 109,
    EVENT_JS_EXCESS_WS = 110,
    EVENT_MIXED_ENCODINGS = 111,
    EVENT_SWF_ZLIB_FAILURE = 112,
    EVENT_SWF_LZMA_FAILURE = 113,
    EVENT_PDF_DEFL_FAILURE = 114,
    EVENT_PDF_UNSUP_COMP_TYPE = 115,
    EVENT_PDF_CASC_COMP = 116,
    EVENT_PDF_PARSE_FAILURE = 117,

    EVENT_LOSS_OF_SYNC = 201,
    EVENT_CHUNK_ZEROS = 202,
    EVENT_WS_BETWEEN_MSGS = 203,
    EVENT_URI_MISSING = 204,
    EVENT_CTRL_IN_REASON = 205,
    EVENT_IMPROPER_WS = 206,
    EVENT_BAD_VERS = 207,
    EVENT_UNKNOWN_VERS = 208,
    EVENT_BAD_HEADER = 209,
    EVENT_CHUNK_OPTIONS = 210,
    EVENT_URI_BAD_FORMAT = 211,
    EVENT_UNKNOWN_PERCENT = 212,
    EVENT_BROKEN_CHUNK = 213,
    EVENT_CHUNK_WHITESPACE = 214,
    EVENT_HEAD_NAME_WHITESPACE = 215,
    EVENT_GZIP_OVERRUN = 216,
    EVENT_GZIP_FAILURE = 217,
    EVENT_ZERO_NINE_CONTINUE = 218,
    EVENT_ZERO_NINE_NOT_FIRST = 219,
    EVENT_BOTH_CL_AND_TE = 220,
    EVENT_BAD_CODE_BODY_HEADER = 221,
    EVENT_BAD_TE_HEADER = 222,
    EVENT_PADDED_TE_HEADER = 223,
    EVENT_MISFORMATTED_HTTP = 224,
    EVENT_UNSUPPORTED_ENCODING = 225,
    EVENT_UNKNOWN_ENCODING = 226,
    EVENT_STACKED_ENCODINGS = 227,
    EVENT_RESPONSE_WO_REQUEST = 228,
    EVENT_FILE_DECOMPR_OVERRUN = 229,
    EVENT_BAD_CHAR_IN_HEADER_NAME = 230,
    EVENT_BAD_CONTENT_LENGTH = 231,
    EVENT_HEADER_WRAPPING = 232,
    EVENT_CR_WITHOUT_LF = 233,
    EVENT_CHUNK_BAD_SEP = 234,
    EVENT_CHUNK_BARE_LF = 235,
    EVENT_MULTIPLE_100_RESPONSES = 236,
    EVENT_UNEXPECTED_100_RESPONSE = 237,
    EVENT_UNKNOWN_1XX_STATUS = 238,
    EVENT_EXPECT_WITHOUT_BODY = 239,
    EVENT_CHUNKED_ONE_POINT_ZERO = 240,
    EVENT_CTE_HEADER = 241,
    EVENT_ILLEGAL_TRAILER = 242,
    EVENT_REPEATED_HEADER = 243,
    EVENT_CONTENT_ENCODING_CHUNKED = 244,
    EVENT_206_WITHOUT_RANGE = 245,
    EVENT_VERSION_NOT_UPPERCASE = 246,
    EVENT_BAD_HEADER_WHITESPACE = 247,
    EVENT_GZIP_EARLY_END = 248,
    EVENT_EXCESS_REPEAT_PARAMS = 249,
    EVENT_H2_NON_IDENTITY_TE = 250,
    EVENT_H2_DATA_OVERRUNS_CL = 251,
    EVENT_H2_DATA_UNDERRUNS_CL = 252,
    EVENT_CONNECT_REQUEST_BODY = 253,
    EVENT_EARLY_C2S_TRAFFIC_AFTER_CONNECT = 254,
    EVENT_200_CONNECT_RESP_WITH_CL = 255,
    EVENT_200_CONNECT_RESP_WITH_TE = 256,
    EVENT_100_CONNECT_RESP = 257,
    EVENT_EARLY_CONNECT_RESPONSE = 258,
    EVENT_MALFORMED_CD_FILENAME = 259,
    EVENT_TRUNCATED_MSG_BODY_CL = 260,
    EVENT_TRUNCATED_MSG_BODY_CHUNK = 261,
    EVENT_LONG_SCHEME = 262,
    EVENT__MAX_VALUE
};

extern const int8_t as_hex[256];
extern const bool token_char[256];
extern const bool scheme_char[256];
extern const bool is_sp_tab[256];
extern const bool is_cr_lf[256];
extern const bool is_sp_tab_lf[256];
extern const bool is_sp_tab_cr_lf[256];
extern const bool is_sp_tab_cr_lf_vt_ff[256];
extern const bool is_sp_tab_quote_dquote[256];
extern const bool is_print_char[256]; // printable includes SP, tab, CR, LF
extern const bool is_sp_comma[256];

enum H2BodyState { H2_BODY_NOT_COMPLETE, H2_BODY_LAST_SEG, H2_BODY_COMPLETE,
    H2_BODY_COMPLETE_EXPECT_TRAILERS, H2_BODY_NO_BODY };

} // end namespace HttpEnums

#endif

