#ifndef OPTIONAL_H
#define OPTIONAL_H

#define DEFINE_OPTION(NAME, TYPE)\
    typedef enum {NAME##_None, NAME##_Some} NAME##_Tag; \
    typedef struct {    \
        NAME##_Tag tag; \
        union { \
            TYPE some;  \
        } data; \
    } NAME;\
    static inline NAME NAME##_some(TYPE value) {\
        NAME opt;   \
        opt.tag = NAME##_Some;  \
        opt.data.some = value;  \
        return opt; \
    }\
    static inline NAME NAME##_none() {\
        NAME opt;   \
        opt.tag = NAME##_None;  \
        return opt; \
    }\
    static inline int NAME##_is_some(NAME* opt) {\
        return opt->tag == NAME##_Some; \
    }\
    static inline TYPE NAME##_unwrap(NAME* opt) {\
        return opt->data.some;  \
    }\
    static inline TYPE NAME##_unwrap_or(NAME* opt, TYPE* default_value) {\
        return NAME##_is_some(opt) ? opt->data.some : *default_value;   \
    }\
    static inline TYPE NAME##_take(NAME* opt) {\
        TYPE value = opt->data.some;    \
        for (unsigned long i = 0; i < sizeof(opt->data.some); i++) {\
            ((unsigned char*)&opt->data.some)[i] = 0; /*zeroing data memory*/\
        }\
        opt->tag = NAME##_None; \
        return value;   \
    }\

#endif