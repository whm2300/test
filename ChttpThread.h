#ifndef _CHTTPTHREAD_H_
#define _CHTTPTHREAD_H_

#include <string>
#include <pthread.h>
#include <curl/curl.h>


class CHttpThread
{
    public:
        CHttpThread();
        ~CHttpThread();

        bool Run(const std::string &url, const std::string &call_back_function_name, void *userdata);

    protected:
        static void *PullOneUrl(void *arg);
        static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

    protected:
        CURL *m_curl;
        std::string m_url;
        std::string m_call_back_function_name;
        void *m_userdata;

        pthread_t m_tid;
};

#endif // _CHTTPTHREAD_H_

