#pragma once
#include <thread>
#ifdef __linux__
#    include <signal.h>
#    include <unistd.h>
#else
#    include <csignal>
#endif

namespace utils
{
class signals_wait
{
    inline static bool interrupt = false;

public:
    static void wait_interrupt()
    {
        signal(SIGINT, sigint);
        signal(SIGTERM, sigterm);
#ifdef __linux__
        signal(SIGKILL, sigkill);
#else
        signal(SIGBREAK, sigbreak);
#endif

        while (!interrupt)
        {
#ifdef __linux__
            sleep(60);
#else
            std::this_thread::sleep_for(std::chrono::seconds(1));
#endif
        }
    }

private:
#ifdef __linux__
    static void sigkill(int)
    {
        interrupt = true;
    }
#else
    static void sigbreak(int)
    {
        interrupt = true;
    }
#endif

    static void sigint(int)
    {
        interrupt = true;
    }

    static void sigterm(int)
    {
        interrupt = true;
    }
};
};  // namespace utils
