// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief include constants for encdata and description of data format
 * 
 * @code
 * Data Format:
 *           < HEADER >                   < ENCRYPTED DATA >                  < TAIL >
 *           signature +                    encrypted data            hash of unencrypted data +
 *       encrypted data length                                         unencrypted data length
 *          not encrypted                        AES                            AES
 * 
 *   signature  | enc.d. length  |         encrypted data          |    hash    | unenc.d. length
 *    8 bytes   |  4 bytes       |  "encrypted data length" bytes  |  4 bytes   |  4 bytes
 *            12 bytes                                               16 bytes (after encryption)
 *
 *                                                                     crc32
 * @endcode
 **/



#ifndef ENC_ENCFORMAT_H
#define ENC_ENCFORMAT_H



#define ENC_SIGNATURE_SIZE 8
#define ENC_SIGNATURE "NCRYPTED"
#define ENC_DATALENGTH_SIZE 4
#define ENC_HASH_SIZE 4
#define ENC_ENCRYPTED_TAIL_SIZE 16



#endif