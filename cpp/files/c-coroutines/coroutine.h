#ifndef COROUTINE_H_885561C7B1764A8E90F2CC0F9100C707
#define COROUTINE_H_885561C7B1764A8E90F2CC0F9100C707

#ifdef __linux__
#include <unistd.h> /* usleep */
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h> /* Sleep */
#endif

void cr_sleep_ms(unsigned long duration) {
#ifdef __linux__
    usleep(duration * 1000);
#endif
#ifdef _WIN32
    Sleep(duration);
#endif
}

unsigned long cr_elapsed_ms() {
    static struct timeb t;
    ftime(&t);
    return (unsigned long)(t.time) * 1000 + t.millitm;
}

typedef enum {
  CR_TERMINATED = 0,
  CR_SUSPENDED = 1,
} cr_state;

#define CR_BEGIN(cr_name_) \
    static cr_state cr_name_() { \
        static int cr_entry_point_ = 0; \
        if (cr_entry_point_ == -1) \
            return CR_TERMINATED; \
        switch (cr_entry_point_) { \
            case 0:

#define CR_END \
            cr_entry_point_ = -1; \
        } \
        return CR_TERMINATED; \
    }

#define CR_YIELD \
    do { \
        cr_entry_point_ = __LINE__; return CR_SUSPENDED; case __LINE__:; \
    } while (0)

#define CR_YIELD_WHILE(cr_flag_) \
    do { \
        cr_entry_point_ = __LINE__; \
        case __LINE__:; \
            if (cr_flag_) \
            return CR_SUSPENDED; \
    } while (0)

#define CR_YIELD_UNTIL(cr_flag_) \
    CR_YIELD_WHILE(!(cr_flag_))

#define CR_YIELD_FOR(cr_interval_) \
    do { \
        static unsigned long cr_timer_ ## __LINE__; \
        cr_timer_ ## __LINE__ = cr_elapsed_ms(); \
        cr_entry_point_ = __LINE__; \
        case __LINE__:; \
            if (cr_elapsed_ms() - cr_timer_ ## __LINE__ < cr_interval_) \
                return CR_SUSPENDED; \
    } while (0)

#define CR_EXIT \
    do { \
        cr_entry_point_ = -1; \
        return CR_TERMINATED; \
    } while (0)

#define CR_RUN_ALL(...) \
    typedef cr_state (*cr_coroutine_)(); \
    cr_coroutine_ cr_pool_[] = { __VA_ARGS__, NULL }; \
    int main() { \
        int cr_all_terminated_ = 0; \
        cr_coroutine_* cr_next_ = NULL; \
        do { \
            cr_all_terminated_ = 1; \
            cr_next_ = cr_pool_; \
            while (*cr_next_ != NULL) { \
                if ((*cr_next_)() == CR_SUSPENDED) \
                    cr_all_terminated_ = 0; \
                ++cr_next_; \
            } \
        } while (!cr_all_terminated_); \
    }

#define CR_RUN_ALL_WITH_PAUSE(cr_period_, ...) \
    typedef cr_state (*cr_coroutine_)(); \
    cr_coroutine_ cr_pool_[] = { __VA_ARGS__, NULL }; \
    int main() { \
        int cr_all_terminated_ = 0; \
        cr_coroutine_* cr_next_ = NULL; \
        unsigned long cr_start_ = 0; \
        unsigned long cr_elapsed_ = 0; \
        do { \
            cr_all_terminated_ = 1; \
            cr_next_ = cr_pool_; \
            cr_start_ = cr_elapsed_ms(); \
            while (*cr_next_ != NULL) { \
                if ((*cr_next_)() == CR_SUSPENDED) \
                    cr_all_terminated_ = 0; \
                ++cr_next_; \
            } \
            cr_elapsed_ = cr_elapsed_ms() - cr_start_; \
            if (cr_elapsed_ < cr_period_) \
                cr_sleep_ms(cr_period_ - cr_elapsed_); \
        } while (!cr_all_terminated_); \
    }

#define CR_RUN_ANY(...) \
    typedef cr_state (*cr_coroutine_)(); \
    cr_coroutine_ cr_pool_[] = { __VA_ARGS__, NULL }; \
    int main() { \
        cr_coroutine_* cr_next_ = NULL; \
        for (;;) { \
            cr_next_ = cr_pool_; \
            while (*cr_next_ != NULL) { \
                if ((*cr_next_)() == CR_TERMINATED) \
                    return 0; \
                ++cr_next_; \
            } \
        } \
    }

#define CR_RUN_ANY_WITH_PAUSE(cr_period_, ...) \
    typedef cr_state (*cr_coroutine_)(); \
    cr_coroutine_ cr_pool_[] = { __VA_ARGS__, NULL }; \
    int main() { \
        cr_coroutine_* cr_next_ = NULL; \
        unsigned long cr_start_ = 0; \
        unsigned long cr_elapsed_ = 0; \
        for (;;) { \
            cr_next_ = cr_pool_; \
            cr_start_ = cr_elapsed_ms(); \
            while (*cr_next_ != NULL) { \
                if ((*cr_next_)() == CR_TERMINATED) \
                    return 0; \
                ++cr_next_; \
            } \
            cr_elapsed_ = cr_elapsed_ms() - cr_start_; \
            if (cr_elapsed_ < cr_period_) \
                cr_sleep_ms(cr_period_ - cr_elapsed_); \
        } \
    }

#endif // COROUTINE_H_885561C7B1764A8E90F2CC0F9100C707
