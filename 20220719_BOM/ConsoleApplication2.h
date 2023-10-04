#pragma once

#include <tchar.h>
#include <atlstr.h>
/*
    BOM - Byte Order Mark
    https://ko.wikipedia.org/wiki/%EB%B0%94%EC%9D%B4%ED%8A%B8_%EC%88%9C%EC%84%9C_%ED%91%9C%EC%8B%9D
    https://docs.microsoft.com/ko-kr/globalization/encoding/byte-order-mark

    바이트 순서 표시(Byte Order Mark, BOM)는 유니코드 문자 U+FEFF byte order mark로, 매직 넘버로서 문서의 가장 앞에 추가하여 텍스트를 읽는 프로그램에 여러 정보를 전달할 수 있다.[1]
    16비트 혹은 32비트 인코딩의 경우, 문서의 바이트 순서 또는 엔디언 문서의 인코딩이 거의 확실히 유니코드임 문서에 사용한 유니코드 문자 인코딩 방식
 */

enum class eBOM {
    eUTF8 = 0x01,   // EF BB BF
    eUTF16BE,       // FE FF
    eUTF16LE,       // FF FE
    eUTF32BE,       // 00 00 FE FF
    eUTF32LE,       // FF FE 00 00
    eNoneBom = 0xFF
};

int main();

BOOL GetBomType(const TCHAR* filepath, eBOM& bom);
