#ifndef __X_TYPES_H__
#define __X_TYPES_H__

typedef char            s8;
typedef unsigned char   u8;
typedef unsigned char   uint8_t;

typedef short			s16;
typedef unsigned short	u16;
typedef short			int16_t;
typedef unsigned short	uint16_t;

typedef int			    s32;
typedef unsigned int	u32;
typedef int			    int32_t;
typedef unsigned int	uint32_t;

typedef long			s64;
typedef unsigned long	u64;
typedef long			int64_t;
typedef unsigned long	uint64_t;

typedef int bool;
typedef unsigned long ulong;
typedef unsigned long uintptr_t;
typedef unsigned long size_t;

#define true        1
#define false       0
#define NULL        ((void*)0)

#define __packed		        __attribute__((packed))
#define __noreturn		        __attribute__((noreturn))
#define __aligned(x)		    __attribute__((aligned(x)))
#define __always_inline	inline  __attribute__((always_inline))

#define likely(x)               __builtin_expect((x), 1)
#define unlikely(x)             __builtin_expect((x), 0)

#undef offsetof
#define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

#endif
