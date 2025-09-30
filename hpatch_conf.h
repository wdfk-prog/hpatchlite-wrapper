/**
 * Copyright (c) 2024, sulfurandcu.github.io
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date             Author              Notes
 * 2024-10-24       liujitong           first version
 * 2025-09-30       wdfk_prog           add decompresser config
 */

#ifndef __hpatch_conf_h__
#define __hpatch_conf_h__

#include "rtthread.h"

#ifdef PKG_HPATCHLITE_DECOMPRESSER_TUZ
/* 启用tuz解压功能 */
#define _CompressPlugin_tuz 1
/* 
 * 0 (默认): Tinyuz 将使用自己独立的一套类型定义，如 tuz_byte, tuz_BOOL, _tuz_TInputCache 等。
 * 1: Tinyuz 将会直接使用 HPatchLite 的类型定义，例如 tuz_byte 会被 #define 成 hpi_byte，_tuz_TInputCache 会被 #define 成 _hpi_TInputCache。
 * 当 Tinyuz 和 HPatchLite 在同一个项目中紧密集成时，将此宏设为 1 可以减少代码体积。因为两种输入缓存结构体 (_TInputCache) 的实现可以被复用，从而节省几十到上百字节的Flash空间。
 */
#define _IS_USED_SHARE_hpatch_lite_types 1

/* 
 * 作用: 控制 Tinyuz 是否启用一种特殊的**“原文数据块（Literal Line）”**处理模式。
 * 1 (默认，用于解压): 启用该模式。解压器能够处理一种特殊的指令，该指令表示“接下来的一段数据是未压缩的原文，请直接复制”。这对于处理那些本身就难以压缩的数据（如已压缩的图片、加密数据）非常有效，可以避免压缩算法在这些数据上“白费力气”，甚至防止压缩后体积变大的情况。
 * 0: 禁用该模式。解压器将不认识“原文数据块”指令。
 * 重要联动: 压缩端和解压端的这个宏设置必须完全一致！
 * 如果您在PC端使用 hdiffi.exe -c-tuz ... 来打包，那么您在MCU端的 tuz_isNeedLiteralLine 必须是 1。
 * 如果您在PC端使用 hdiffi.exe -c-tuzi ... (注意后面的 i) 来打包，那么您在MCU端的 tuz_isNeedLiteralLine 必须是 0。
 * 设置为 0 可以减少解压端的代码体积（节省大约54字节），但代价是可能降低对混合数据的压缩率。
 */
// #define tuz_isNeedLiteralLine 0

/* 禁用tuz断言 */
// #define NDEBUG

/* 
 * 作用: 控制是否在代码中加入运行时的内存安全检查。
 * 1 (默认): 启用检查。代码中会包含一些 assert 或类似的检查，用于在解压过程中判断是否存在缓冲区溢出、数据损坏等风险。这会使代码更健壮，但会稍微增加一点代码体积和运行开销。
 * 0: 禁用检查。移除所有的安全断言。可以获得极致的代码大小和性能，但牺牲了运行时的安全性。通常只在经过充分测试、准备发布最终产品时才考虑关闭它。
 */
// #define _IS_RUN_MEM_SAFE_CHECK 1

/*  
 * tuz_kMaxOfDictSize 和 tuz_kDictSizeSavedBytes
 * tuz_kMaxOfDictSize:
 * 作用: 定义了 Tinyuz 算法理论上支持的最大字典大小。它不是您实际使用的字典大小，而是一个编译时的上限。
 * 这个值会影响 tuz_kDictSizeSavedBytes 的计算。
 * 
 * tuz_kDictSizeSavedBytes:
 * 作用: 这个宏非常重要。它决定了在压缩数据流的开头，用多少个字节来存储实际的字典大小值。
 * 计算逻辑: 它是根据 tuz_kMaxOfDictSize 的大小自动计算的。
 * 如果 tuz_kMaxOfDictSize 在 2^8-1 (255) 以内，就用1个字节存储。
 * 如果在 2^16-1 (65535) 以内，就用2个字节存储。
 * ... 以此类推。
 * 目的: 这是一种空间优化。如果知道一个系统永远不会使用超过64KB的字典，就可以通过 tuz_kMaxOfDictSize 限制它，从而使存储字典大小的头部字段更小。 
*/
// #define tuz_kMaxOfDictSize (1<<30)

/* 
 * 作用: 这个宏定义了 Tinyuz 算法所能接受的最小字典大小（Minimum Dictionary Size）。
 * 默认值: 1。
 * 目的:
 * 参数校验: 它主要用于参数合法性检查。当 hdiffi (压缩端) 或 tuz_dec (解压端) 接收到一个字典大小参数时，会检查这个值是否大于或等于 tuz_kMinOfDictSize。如果用户试图提供一个为0或无效的字典大小，这个检查可以防止程序出错。
 * 算法下限: 它从理论上确立了算法可以工作的最小资源条件。虽然使用只有1个字节的字典几乎没有任何压缩效果，但算法本身在这种极端情况下依然是正确和有效的 */
// #define tuz_kMinOfDictSize 1
#endif

// Future decompressors can be added here
// #ifdef PKG_HPATCHLITE_DECOMPRESSER_ZLIB
// #   define _CompressPlugin_zlib 1
// #endif

#define hpi_malloc(x) rt_malloc(x)
#define hpi_free(x)   rt_free(x)

#endif /* __hpatch_conf_h__ */
