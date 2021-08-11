﻿namespace Platform::Collections
{
    namespace Internal
    {
        template<typename TChar>
        static auto IsMasks(const std::basic_string<TChar>& string)
        {
            using ctype = std::ctype<wchar_t>;
            using mask_type = std::ctype_base::mask;

            auto& facet = std::use_facet<ctype>(std::locale());
            std::vector<mask_type> masks(string.size());

            facet.is(
                static_cast<const wchar_t*>(&*string.begin()),
                static_cast<const wchar_t*>(&*string.begin() + string.size()),
                &*masks.begin()
            );
        }
    }

    // Maybe internal
    template<typename TChar>
    static auto IsWhiteSpace(const std::basic_string<TChar>& string)
    {
        using ctype = std::ctype<wchar_t>;
        using mask_type = std::ctype_base::mask;

        auto masks = Internal::IsMasks(string);
        return std::ranges::all_of(masks, [](mask_type mask) { return mask & ctype::space; });
    }

    template<typename TChar>
    static auto CapitalizeFirstLetter(std::basic_string<TChar> string)
    {
        using ctype = std::ctype<wchar_t>;
        auto& facet = std::use_facet<ctype>(std::locale());

        for (auto& symbol : string)
        {
            if (facet.is(ctype::alpha, symbol))
            {
                symbol = facet.toupper(symbol);
                return string;
            }
        }
        return string;
    }

    template<typename TChar>
    static auto Truncate(std::basic_string<TChar> string, std::size_t maxLength) { return string.substr(0, maxLength); }

    template<typename TChar>
    static auto TrimSingle(std::basic_string<TChar> string, TChar charToTrim) -> std::basic_string<TChar>
    {
        if (string.empty())
        {
            return string;
        }

        if (string.size() == 1)
        {
            if (string[0] == charToTrim)
            {
                return {};
            }
            else
            {
                return string;
            }
        }

        auto left = 0;
        auto right = string.size() - 1;
        if (string[left] == charToTrim)
        {
            left++;
        }
        if (string[right] == charToTrim)
        {
            right--;
        }
        return string.substr(left, right - left + 1);
    }
}
