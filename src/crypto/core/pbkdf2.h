#ifndef PBKDF2_H 
#define PBKDF2_H



void PBKDF2_HMAC_SHA_512(const char* pass, size_t pass_size, 
                         const char* salt, size_t salt_size,
                         int32_t iterations, uint32_t outputBytes, uint8_t* bin_result);



#endif