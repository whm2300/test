#!/usr/bin/bash
#gcc hiperfifo.c /home/michael/open_source_lib/curl/lib/libcurl.a /home/michael/open_source_lib/zlib/lib/libz.a /home/michael/open_source_lib/openssl/lib/libssl.a /home/michael/open_source_lib/openssl/lib/libcrypto.a -levent -lpthread -ldl -lldap -llber
#gcc test_multithread.c /home/michael/open_source_lib/curl/lib/libcurl.a /home/michael/open_source_lib/zlib/lib/libz.a /home/michael/open_source_lib/openssl/lib/libssl.a /home/michael/open_source_lib/openssl/lib/libcrypto.a -lpthread -ldl -lldap -llber
g++ ChttpThread.cpp /home/michael/open_source_lib/curl/lib/libcurl.a /home/michael/open_source_lib/zlib/lib/libz.a /home/michael/open_source_lib/openssl/lib/libssl.a /home/michael/open_source_lib/openssl/lib/libcrypto.a -lpthread -ldl -lldap -llber -Wall -Wextra
