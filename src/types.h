#ifndef _TYPES_H_
#define _TYPES_H_

#include "./nat-types.h"

/* Types & Sizes */

typedef u8  Byte; /* Unsigned Byte */
typedef i8  Char; /* Signed Byte */
typedef u32 Unsi; /* Unsigned Integer */
typedef i32 Inte; /* Signed Integer */
typedef u64 Long; /* Unsigned Long Integer */
typedef i64 Sign; /* Signed Long Integer */
typedef f32 Flot; /* Single Floating Point */
typedef f64 Doub; /* Double Floating Point */

#define Byte_SIZE sizeof(Byte)
#define Char_SIZE sizeof(Char)
#define Unsi_SIZE sizeof(Unsi)
#define Inte_SIZE sizeof(Inte)
#define Long_SIZE sizeof(Long)
#define Sign_SIZE sizeof(Sign)
#define Flot_SIZE sizeof(Flot)
#define Doub_SIZE sizeof(Doub)

typedef u32 Word;
typedef u64 TwoW;

#define Word_SIZE sizeof(Word)
#define TwoW_SIZE sizeof(TwoW)

#define Word_MAX   (((Word) 0x0U) - 1U)
#define TwoW_MAX   (((TwoW) 0x0U) - 1U)
#define TwoW_RHALF (((TwoW) Word_MAX))
#define TwoW_LHALF (~TwoW_RHALF)

typedef bool Bool;

#endif /* #ifndef _TYPES_H_ */
