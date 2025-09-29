#include "set_ops_io.h"

namespace setops {

ValueSet parseSet(std::string line) {
    
    ValueSet result;
    std::string raw_token;
    uint8_t flags = 0;
    bool inQuotes = false;  // used to track if inside of quotes

    for (char c : line) {

        // everything inside of quotes read as string
        if (c == '"') {                 // toggle quotes, don't consume
            inQuotes = !inQuotes;
            flags |= STR_VAL;        // quotes => definitely a string
            continue;
        }

        if (inQuotes) {                 // consume everything inside quotes
            raw_token += c;
            continue;
        }

        // commas separate tokens
        if (c == ',') {
            if (!raw_token.empty())     // ignore empty tokens like ",,"
                parseToken(result, raw_token, flags);
            raw_token.clear();
            flags = 0;
            continue;
        }

        // skip whitespace outside quotes
        if (std::isspace(c)) {
            continue;
        }

        // ---- classification ----
        if (flags & STR_VAL) {
            // already string: just consume
        } else if ((flags & NUM_VAL) && std::isdigit(c)) {
            // still numeric: keep going
        } else if (!(flags & NUM_VAL) && (std::isdigit(c) || c == '+' || c == '-')) {
            flags |= NUM_VAL;           // starting a number (allow leading sign)
        } else if ((flags & NUM_VAL) && c == '.') {
            if (!(flags & DBL_VAL))   // first dot -> float
                flags |= DBL_VAL;
            else
                flags = STR_VAL;    // second dot -> string
        } else if ((flags & NUM_VAL) && !std::isdigit(c)) {
            // any other non-digit while numeric -> string (unless you also want to handle exponents)
            flags = STR_VAL;
        } else {
            flags = STR_VAL;        // default to string
        }

        // consume char
        raw_token += c;
    }

    // flush last token
    if (!raw_token.empty())
        parseToken(result, raw_token, flags);

    return result;
}

void parseToken(ValueSet& set, std::string raw_token, uint8_t flags) {
    Value token;

    if (flags & STR_VAL) {
        // strings of "true" or "false" are treated as booleans
        if (raw_token == "true") {
            token = true;
        } else if (raw_token == "false") {
            token = false;
        } else {
            token = raw_token;
        }
    } else if (flags & NUM_VAL) {
        try {
            if (flags & DBL_VAL) token = std::stod(raw_token);
            else                   token = std::stoi(raw_token);
        } catch (...) {
            token = raw_token;  // fallback to string on parse error
        }
    } else {
        token = raw_token;      // fallback to string if nothing else works
    }
    set.emplace(token);
}

} // namespace setops