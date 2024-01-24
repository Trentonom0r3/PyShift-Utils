#include "pch.h"
#include "MessageQueue.h"

std::string createUUID() {
    GUID guid;
    HRESULT result = CoCreateGuid(&guid);  // Generate a new GUID/UUID

    if (FAILED(result)) {
        // Handle error if CoCreateGuid fails
        return "";
    }

    char buffer[39];
    snprintf(buffer, sizeof(buffer),
        "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2],
        guid.Data4[3], guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);

    return std::string(buffer);
}