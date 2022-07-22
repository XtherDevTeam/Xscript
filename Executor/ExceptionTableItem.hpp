//
// Created by XIaokang00010 on 2022/7/22.
//

#ifndef XSCRIPT2_EXCEPTIONTABLEITEM_HPP
#define XSCRIPT2_EXCEPTIONTABLEITEM_HPP

#include "../Share/Config.hpp"

namespace XScript {

    class ExceptionTableItem {
    public:
        XIndexType ExceptionRegisterCommandPosition; // Exception Register嘅位置
        XIndexType CatchBlockOffset; // 異常位置同埋Exception Register位置嘅Offset
        XIndexType StackItemCnt; // 當發生異常嘅時候，fallback到catch嘅stack_frame, 執行catch塊嘅代碼
    };

} // XScript

#endif //XSCRIPT2_EXCEPTIONTABLEITEM_HPP
