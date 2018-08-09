#include <iostream>
#include <memory>

#include "hook.hpp"
#include <dlfcn.h>

void _init(void) __attribute__ ((constructor));

typedef int (* fn_mysqlnd_mysqlnd_conn_data_send_query_pub)(void * conn, const char * const query, const size_t query_len,
                                                            int type, void *read_cb, void *err_cb);
static
std::shared_ptr<Detouring::Hook> hook;

int _mysqlnd_mysqlnd_conn_data_send_query_pub(void * conn, const char * const query, const size_t query_len,
                                              int type, void *read_cb, void *err_cb) {
    (void)conn;
    (void)query;
    (void)query_len;
    (void)type;
    (void)read_cb;
    (void)err_cb;

    std::cout << "query:" << query << ", len:" << query_len << std::endl;

    fn_mysqlnd_mysqlnd_conn_data_send_query_pub pfn =
            hook->GetTrampoline<fn_mysqlnd_mysqlnd_conn_data_send_query_pub>();

    return pfn(conn, query, query_len, type, read_cb, err_cb);
}


void _init(void) {
    std::cout << "init called" << std::endl;

    std::cout << "lib:" << dlopen("/usr/local/lib/httpd/modules/libphp7.so",
                                  RTLD_LAZY)
              << std::endl;

    uintptr_t v = reinterpret_cast<uintptr_t>(dlsym(dlopen("/usr/local/lib/httpd/modules/libphp7.so",
                               RTLD_LAZY),
                                                    "mysqlnd_stats_reset_triggers"));
    std::cout << "fn:"
              << std::hex
              << v
              << ","
              << (v - 0x00000000003b104d + 0x00000000003a50d0)
              << std::endl;

    void * target = (void*)(v - 0x00000000003b104d + 0x00000000003a50d0);
    hook = std::make_shared<Detouring::Hook>(target,
                                             reinterpret_cast<void*>(_mysqlnd_mysqlnd_conn_data_send_query_pub));

    std::cout << "target:" << hook->GetTarget() << std::endl;
    hook->Enable();
}
