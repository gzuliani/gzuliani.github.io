#ifndef REENTRANT_H_13DF318343024713BAA753E8AE68D824
#define REENTRANT_H_13DF318343024713BAA753E8AE68D824

#define CR_BEGIN_REENTRANT(cr_name_) \
    typedef struct cr_ ## cr_name_ ## _context cr_ ## cr_name_ ## _context; \
    static cr_state cr_name_(cr_ ## cr_name_ ## _context* cr_context) { \
        if (cr_entry_point_ == -1) \
            return CR_TERMINATED; \
        switch (cr_entry_point_) { \
            case 0:

#define CR_CONTEXT_FOR(cr_name_) \
    struct cr_ ## cr_name_ ## _context { \

#define CR_END_CONTEXT \
        unsigned long timer_; \
        int entry_point_; \
    };

#define CR_EMPTY_CONTEXT_FOR(cr_name_) \
    CR_CONTEXT_FOR(cr_name_) \
    CR_END_CONTEXT

#undef CR_YIELD_FOR

#define CR_YIELD_FOR(cr_interval_) \
    do { \
        cr_context->timer_ = cr_elapsed_ms(); \
        cr_entry_point_ = __LINE__; \
        case __LINE__:; \
            if (cr_elapsed_ms() - cr_context->timer_ < cr_interval_) \
                return CR_SUSPENDED; \
    } while (0)

#define cr_entry_point_ (cr_context->entry_point_)

#endif // REENTRANT_H_13DF318343024713BAA753E8AE68D824
