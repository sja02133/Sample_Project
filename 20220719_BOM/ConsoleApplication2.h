#pragma once

#include <tchar.h>
#include <atlstr.h>
/*
    BOM - Byte Order Mark
    https://ko.wikipedia.org/wiki/%EB%B0%94%EC%9D%B4%ED%8A%B8_%EC%88%9C%EC%84%9C_%ED%91%9C%EC%8B%9D
    https://docs.microsoft.com/ko-kr/globalization/encoding/byte-order-mark

    ����Ʈ ���� ǥ��(Byte Order Mark, BOM)�� �����ڵ� ���� U+FEFF byte order mark��, ���� �ѹ��μ� ������ ���� �տ� �߰��Ͽ� �ؽ�Ʈ�� �д� ���α׷��� ���� ������ ������ �� �ִ�.[1]
    16��Ʈ Ȥ�� 32��Ʈ ���ڵ��� ���, ������ ����Ʈ ���� �Ǵ� ����� ������ ���ڵ��� ���� Ȯ���� �����ڵ��� ������ ����� �����ڵ� ���� ���ڵ� ���
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
