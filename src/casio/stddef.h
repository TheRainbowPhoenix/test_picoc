//
// Created by Phoebe on 11/09/2022.
//

#ifndef TEST_PICOC_STDDEF_H
#define TEST_PICOC_STDDEF_H

#ifdef __cplusplus
extern "C" {
#endif

// Python requires that NULL be a macro, so humor it.
#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void*)0)
#endif

#ifndef size_t
typedef unsigned size_t;
#endif

#ifdef __cplusplus
}
#endif


#endif //TEST_PICOC_STDDEF_H
