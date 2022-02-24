#include <openssl/evp.h>
#include <cstring>



void PBKDF2_HMAC_SHA_512(const char* pass, size_t pass_size, 
                         const char* salt, size_t salt_size,
                         int32_t iterations, uint32_t outputBytes, uint8_t* bin_result) {
  unsigned char digest[outputBytes];
  PKCS5_PBKDF2_HMAC(pass, pass_size, reinterpret_cast<const unsigned char*>(salt), salt_size, 
                    iterations, EVP_sha512(), outputBytes, digest);
  memcpy(bin_result, digest, outputBytes);
}
