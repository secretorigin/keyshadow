<h1>:key: KEYSHADOW</h1>

<p>It's simple password manager with 2 my libraries:</p>

- encprocessor
- noteprocessor

<h1>:rocket: Progress</h1>

- :star: [Encryption architecture development](https://github.com/p2034/encprocessor)
- :star: [Special format encrypted file](https://github.com/p2034/encprocessor)
- :star: Saving data architecture development
- :star: Saving logins and passwords
- Saving other note types
- Saving images
- :full_moon: Console client
- :new_moon_with_face: GUI client (QT)

<h1>:page_facing_up: File structure:</h1>

- I use note format from (noteprocessor)[https://github.com/p2034/keyshadow/blob/main/src/noteprocessor/writable.h]:

```
 *    < Code > | < Name Length > |       < Name >      | < Data Length > |      < Data >
 *    2 bytes  |    1 bytes      | "Name Length" bytes |     4 bytes     | "Data Length" bytes
```

- This format is wrapped by encypet file format from (encprocessor)[https://github.com/p2034/keyshadow/blob/main/src/encprocessor/core/encformat.h]:

```
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
```

<h1>:flying_saucer: Problems</h1>

- When we call write() on WritableArray it use writeHeader() from Writable (noteprocessor)[https://github.com/p2034/keyshadow/blob/main/src/noteprocessor/writablearray.cpp]
- I need to set up OpenSSL functions for encryption, because I am not sure about currently used realisations. [https://github.com/p2034/keyshadow/blob/main/src/encprocessor/core/encdata.cpp]