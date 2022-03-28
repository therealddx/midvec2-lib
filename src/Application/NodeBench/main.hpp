/**
 * reference LICENSE file provided.
 *
 * main.hpp
 * Definitions for key static objects and CLI marshaling functions
 * in the nodebench test application.
 *
 */

#ifndef MAIN_HPP
#define MAIN_HPP

// NUM_BYTENODE_CLI_ARGS
//   from usage: `byte-node -ipr rb-uid -opr rb-uid`; all mandatory.
// 
static const int32_t NUM_BYTENODE_CLI_ARGS = 5;

// NUM_SOURCENODE_CLI_ARGS
//   from usage: `source-node -gsine 1 2 3 4 1000 -opr 12`
// 
static const int32_t NUM_SOURCENODE_CLI_ARGS = 9;

// NUM_SHOWNODE_CLI_ARGS
//   from usage: `show-node -ipr 999 -dtext humanreadable.txt`
// 
static const int32_t NUM_SHOWNODE_CLI_ARGS = 5;

// NUM_CORENODE_CLI_ARGS
//   from usage: `core-node -ipr 737 -pconv <arg> -opr 747`
// 
static const int32_t NUM_CORENODE_CLI_ARGS = 7;

// NUM_MIXERNODE_CLI_ARGS
//   from usage: `mixer-node -ipr 737 -ipr 747 -opf 757`
// 
static const int32_t NUM_MIXERNODE_CLI_ARGS = 7;

// db_ringbuffers
//   database of RingBuffer's allocated by this application.
//
//   key: 'int32_t'; assigned by user at CLI;
//     denotes producers/consumers to any ringbuffer
//
//   value: 'RingBuffer<char>*'; self-explanatory
//
static std::map<int32_t, RingBuffer<char>*> db_ringbuffers;

// rb_cancellation_token
//   global RingBuffer turn-off for graceful application close,
//     even if `Write`/`Read` calls are in 'drain'/'fill' mode.
//
static std::atomic<bool> rb_cancellation_token(false);

/**
 * <T_NODEPART>_from_cli
 *
 * @brief given an offset into the application's argv,
 *   (which corresponds to the first CLI argument of the 'T_NODEPART' type),
 * return either:
 *   a valid 'T_NODEPART*', or
 *   nullptr (if CLI args are bad).
 */
dispPs<double>*         dispPs_from_cli (char**);
procPs<double, double>* procPs_from_cli (char**);
genPs<double>*          genPs_from_cli  (char**);
outPs*                  outPs_from_cli  (char**);
inPs*                   inPs_from_cli   (char**);

#endif // MAIN_HPP

