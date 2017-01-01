#include "ChttpThread.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

CHttpThread::CHttpThread():m_curl(NULL), m_userdata(NULL)
{}

CHttpThread::~CHttpThread()
{}

bool CHttpThread::Run(const std::string &url, const std::string &call_back_function_name, 
                      void *userdata)
{
    m_url = url;
    m_call_back_function_name = call_back_function_name;
    m_userdata = userdata;

    int ret = pthread_create(&m_tid, NULL, CHttpThread::PullOneUrl, this);
    if (ret != 0)
    {
        printf("thread_create fail. %s", strerror(errno));
        return false;
    }
    pthread_detach(m_tid);
    return true;
}

void *CHttpThread::PullOneUrl(void *arg)
{
    CHttpThread *http_thread = static_cast<CHttpThread*>(arg);
    assert(http_thread != NULL);
    http_thread->m_curl = curl_easy_init();
    if (http_thread->m_curl == NULL)
    {
        printf("curl_easy_init fail");
        return NULL;
    }
    curl_easy_setopt(http_thread->m_curl, CURLOPT_URL, http_thread->m_url.c_str());
    curl_easy_setopt(http_thread->m_curl, CURLOPT_CONNECTTIMEOUT, 3L);
    curl_easy_setopt(http_thread->m_curl, CURLOPT_TIMEOUT, 7L);
    curl_easy_setopt(http_thread->m_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(http_thread->m_curl, CURLOPT_WRITEFUNCTION, CHttpThread::write_callback);
    curl_easy_setopt(http_thread->m_curl, CURLOPT_WRITEDATA, http_thread);
    printf("start:%d\n", (int)time(NULL));
    CURLcode ret = curl_easy_perform(http_thread->m_curl);
    printf("end:%d\n", (int)time(NULL));
    if (ret != CURLE_OK)
    {
        printf("url:%s, curl_easy_perform fail, ret:%d\n", http_thread->m_url.c_str(), ret);
    }
    return NULL;
}

size_t CHttpThread::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    CHttpThread *http_thread = static_cast<CHttpThread*>(userdata);
    assert(http_thread != NULL);
    int body_len = size * nmemb;
    std::string body(ptr, body_len);
    printf("0x%lx, fun:%s, url:%s, write_callback:%s\n", pthread_self(), 
                http_thread->m_call_back_function_name.c_str(), 
                http_thread->m_url.c_str(), body.c_str());

    //内存释放
    //userdata->Notify(http_thread->m_call_back_function_name);

    return body_len;
}

//test
int main(int argc, char *argv[])
{
    const char * const urls[4]= {
        "www.google.com",
        "https://www.baidu.com/search/error.html",
        "https://api.weixin.qq.com/sns/oauth2/access_token?appid=APPID&secret=SECRET&code=CODE&grant_type=authorization_code",
        "https://api.weixin.qq.com/sns/oauth2/access_token?appid=APPID&secret=SECRET&code=CODE&grant_type=authorization_code",
    };

    for (int i = 0; i < 4; ++i)
    {
        CHttpThread *p = new CHttpThread();
        p->Run(urls[i], "test_function_name", NULL);
    }
    pthread_exit(0);
    return 0;
}
