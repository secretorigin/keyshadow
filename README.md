<h1>KEY SHADOW</h1>

<h3>Progress</h3>
  <h4>Version 1.0</h4>



<h3>Usage</h3>

<h4>Commands</h4>

1. ks - create new database with first free name
  flags:
    1. -f _file_ - (-file) create database with name _file_
    2. -a _algorithm_ - (-alg) create new database with algorithm
      Values:
        1. AES 
    3. -h _hashfunction_ - (-hash) create new database with _hashfunction_ 
                            for creating key
      Values:
        1. SHA512
        2. SHA256
  Errors:
    1. Invalid command:
      1. invalid syntax
      2. invalid flag
      3. invalid argument
    2. Wrong repeated password
    3. File already exist

  ```

  ks -f newdatabase.shadow -a AES -h SHA512
    password: ...
    repeat password: ...
  
  ```

2. ks _file_ - open data base with name _file_
  Must be one of flags:
    1. -add _resourcename_ - add new resource named _resourcename_
      Flags:
        1. -t _type_ - (-type) add type of resource (default: size)
          Values:
            1. site (two fields)
            2. note (one field)
            3. file (encrypt file from path = _resourcename_)
      ```
      
      ks mydatabase.shadow -add newresource.com
        Password: ...
        Resource login: login
        Resource password: ...
        Resourse added.

      ```
    2. -del _resourcename_ - delete info about resource named _resourcename_
      
      ```
      
      ks mydatabase.shadow -del myresource.old
        Password: ...
        Resource deleted.

      ```

    3. -get _resourcename_
      For different resource types different meaning:
        1. Site:
          Display login and copy in clipboard password.
        2. Note
          Display note
        3. File
          Decrypt file and save it as new file.
      
    4. -ls - get full list of notes, sites and files in database
      
      ```

      ks mydatabase.shadow -ls
        Password: ...
        Sites:
          ...
          ...
        Notes:
          ...
        Files:
          ...

      ```
    5. -info - print database info


<h3>Structure:</h3>

<h4>Header structure:</h4>

1. 8 bytes - algorithm (AESECB\0\0 - AES ECB)
2. algorithm info (unknown count of bytes)
  For AES it's:
    2 bytes - key size
3. 8 bytes - hash algorithm (PHSHA512 - PBKDF2 HMAC SHA512)
4. hash algorithm info (unknown count of bytes)
  For PBKDF2 HMAC SHA512 it's:
    4 bytes - iterations
    2 bytes - salt size
    salt size bytes - salt
5. 8 bytes - data size (without encryption)
6. 4 bytes - crc32 hash of data (for checking password)
7. x bytes - encrypted data

<h4>Database structure:</h4>

