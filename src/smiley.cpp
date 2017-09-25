#include <string>
#include <algorithm>
#include "smiley.h"

namespace smiley {

    static const std::wstring positive_smileys[] = {
            L":‑)", L":)", L":-]", L":]", L":-3", L":3", L":->", L":>", L"8-)", L"8)", L":-}", L":}", L":o)", L":c)",
            L":^)", L"=]", L"=)", L":-))", L":‑D", L":D", L"8‑D", L"8D", L"x‑D", L"xD", L"X‑D", L"XD", L"=D", L"=3",
            L"B^D", L":'‑)", L":'))", L";‑)", L";)", L"*-)", L"*)", L";‑]", L";]", L";^)", L":‑,", L";D", L":-*", L":*",
            L":×", L"O:‑)", L"O:)", L"0:‑3", L"0:3", L"0:‑)", L"0:)", L"0;^)", L">:‑)", L">:)", L"}:‑)", L"}:)",
            L"3:‑)", L"3:)", L">;)", L"|;‑)", L":‑J", L"#‑)", L"%‑)", L"%)", L"5:‑)", L"*<|:‑)", L",:‑)", L"<3",
            L"\\o/", L"*\\0/*", L"^5", L"o/\\o", L">_>^ ^<_<", L"(^_-)", L"(^_-)-*", L"^_^", L"(^_^)/", L"(^O^)／",
            L"(^o^)／", L"(^^)/", L"(·w·)", L"^w^", L"^m^", L">^_^<", L"<^!^>", L"^/^", L"(*^_^*)", L"§^.^§", L"(^<^)",
            L"(^.^)", L"(^·^)", L"(^.^)", L"(^_^.)", L"(^_^)", L"(^^)", L"(^J^)", L"(*^.^*)", L"^_^", L"(#^.^#)",
            L"(^—^)", L"＼(~o~)／", L"＼(^o^)／", L"＼(-o-)／", L"(*^0^*)", L"(*_*)", L"(*_*;", L"(+_+)", L"(@_@)",
            L"(@_@。", L"(@_@;)", L"(*^^)v", L"(^^)v", L"(^_^)v", L"(’-’*)", L"( ^)o(^ )", L"(^O^)", L"(^o^)", L"(^○^)",
            L")^o^("
    };

    static const std::wstring negative_smileys[] = {
            L":‑(", L":(", L":‑c", L":c", L":‑<", L":<", L":‑[", L":[", L":-||", L">:[", L":{", L":@", L">:(", L":'‑(",
            L":'(", L"D‑':", L"D:<", L"D:", L"D8", L"D;", L"D=", L"DX", L":‑O", L":O", L":‑o", L":o", L":-0", L"8‑0",
            L">:O", L":‑/", L":/", L":‑.", L">:\\", L">:/", L":\\", L"=/", L"=\\", L":L", L"=L", L":S", L":$", L":‑X",
            L":X", L":‑#", L":#", L":‑&", L":&", L":‑###..", L":###..", L"<:‑|", L"~:‑\\", L"</3", L"<\\3", L"><>",
            L"<*)))‑{", L"v.v", L"O_O", L"o‑o", L"O_o", L"o_O", L"o_o", L"O-O", L">.<", L"(>_<)", L"(>_<)>", L"(^_^;)",
            L"(-_-;)", L"(~_~;)", L"^_^;", L"(#^.^#)", L"(^^;)", L"((+_+))", L"(+o+)", L"('_')", L"(/_;)", L"(T_T)",
            L"(;_;)", L"(;_;", L"(;_:)", L"(;O;)", L"(:_;)", L"(ToT)", L";_;", L";-;", L";n;", L";;", L"Q.Q", L"T.T",
            L"QQ", L"Q_Q", L"(-.-)", L"(-_-)", L"(..)", L"(._.)", L"(..?", L"(?_?)", L"(-\"-)", L"(^_^x)", L"(-_-x)",
            L"(~_~x)", L"(--x)", L"(0^0)", L"(T_T)/~~~", L"(ToT)/~~~", L"(;_;)/~~~"
    };

    static const std::wstring neutral_smileys[] = {
            L":‑P", L":P", L"X‑P", L"XP", L"x‑p", L"xp", L":‑p", L":p", L":‑Þ", L":Þ", L":‑þ", L":þ", L":‑b", L":b",
            L"d:", L"=p", L">:P", L":‑|", L":|", L"|‑O", L"~(_8^(I)", L"=:o]", L"7:^]", L"@};-", L"@}->--",
            L"@}‑;‑'‑‑‑", L"@>‑‑>‑‑", L"><(((*>", L"//0‑0\\\\", L"(';')", L"(^.^)y-.o○", L"(-.-)y", L"(-_-)zzz",
            L"(o|o)", L"<(｀^´)>", L"(__)", L"_(._.)_", L"_(_^_)_", L"<(_ _)>", L"<m(__)m>", L"m(__)m", L"m(_ _)m",
            L"(=_=)", L"(=^·^=)", L"(=^··^=)", L"=_^=", L"(^^)/~~~", L"(^_^)/~", L"(^.^)/~~~", L"(-_-)/~~~",
            L"($··)/~~~", L"(@^^)/~~~", L"!(^^)!", L"(~o~)", L"(~_~)", L"(p_-)", L"((d[-_-]b))", L"(^0_0^)", L":O o_O",
            L"o_0", L"o.O", L"(o.o)", L"oO"
    };

    bool is_positive(const std::wstring &word) {
        return std::find(std::begin(positive_smileys), std::end(positive_smileys), word) != std::end(positive_smileys);
    }

    bool is_negative(const std::wstring &word) {
        return std::find(std::begin(negative_smileys), std::end(negative_smileys), word) != std::end(negative_smileys);
    }

    bool is_neutral(const std::wstring &word) {
        return std::find(std::begin(neutral_smileys), std::end(neutral_smileys), word) != std::end(neutral_smileys);
    }

    bool is_smiley(const std::wstring &word) {
        return is_positive(word) || is_negative(word) || is_neutral(word);
    }

}