<h1>:key: KEYSHADOW</h1>

- [Development](#development)
- [Usage](#usage)

<p>It's simple password manager with 2 my libraries:</p>

- encprocessor
- noteprocessor

<a name="development"/>
<h1>:construction: Development</h1>

<h2>:books: Stack</h2>

- C++
- [AES](https://github.com/SergeyBel/AES) by SergeyBel
- [CRC32](https://gist.github.com/iwanders/8e1cb7b92af2ccf8d1a73450d771f483) by Ivor Wanders

<h2>:rocket: Progress</h2>

- :star: [Encryption architecture development](https://github.com/p2034/encprocessor)
- :star: [Special format encrypted file](https://github.com/p2034/encprocessor)
- :star: Saving data architecture development
- :star: Saving logins and passwords
- Saving other note types
- Saving images
- :star: Console client
- :full_moon: Adding normal key-creation with SHA256, HMAC and PBKDF2
- Transition to functions from OpenSSL
- :new_moon_with_face: GUI client (QT)

<h2>:page_facing_up: File structure:</h2>

- I use note format from [noteprocessor](https://github.com/p2034/keyshadow/blob/main/src/noteprocessor/writable.h):

```
 *    < Code > | < Name Length > |       < Name >      | < Data Length > |      < Data >
 *    2 bytes  |    1 bytes      | "Name Length" bytes |     4 bytes     | "Data Length" bytes
```

- This format is wrapped by encypet file format from [encprocessor](https://github.com/p2034/keyshadow/blob/main/src/encprocessor/core/encformat.h):

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

<h2>:flying_saucer: Problems</h2>

1. :white_check_mark: When we call write() on WritableArray it use writeHeader() from Writable and does not see code() implementation. [source](https://github.com/p2034/keyshadow/blob/main/src/noteprocessor/writablearray.cpp)
  - Solved: problem was related to the destructor in WritableArray::readData() function, WritableArray lose it's class type and became Writable after this destructor, strange.
2. :construction: I need to set up OpenSSL functions for encryption, because I am not sure about currently used realisations. [source](https://github.com/p2034/keyshadow/blob/main/src/encprocessor/core/encdata.cpp)

<a name="usage"/>
<h1>Usage</h1>

<h2>Install</h2>

- Clone this repo to your projects directory
- Go to the <b>/build</b>
- Run to compile:

```bash
cmake ./
make
```

- Run to use the programm with database which you already have on the computer:

```bash
./keyshadow <path to the database> <password>
```

- Run to create new database and use the programm:

```bash
./keyshadow -create <path to the database> <password>
```

- Run for help:

```bash
./keyshadow -help
```

<h2>Example</h2>

<p>Console example of using this program:</p>

```
build$ ./keyshadow -create newdb Lol12345
> add
> Resource: resource_name_1
> Login: login_1
> Password: password_1
Data was added.
> add
> Resource: resource_name_2
> Login: login_2
> Password: password_2
Data was added.
> list
> All data:
> Login-Password resource_name_1
> Login-Password resource_name_2
> find
> Resource: resource_name_2
> Found:
> login_2 password_2
> save
File was saved.
> exit 
...the end.
build$ ./keyshadow newdb Lol12345
> list
> All data:
> Login-Password resource_name_1
> Login-Password resource_name_2
> find 
> Resource: resource_name_1
> Found:
> login_1 password_1
> remove
> Resource: resource_name_1
> Index: 0
Data was removed.
> list
> All data:
> Login-Password resource_name_2
> save
File was saved.
> exit
...the end.
build$ 
```
