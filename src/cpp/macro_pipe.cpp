#include "pipe_name.h"
#include "key_utils.hpp"

#define BUFFER_SIZE 1024

int main() {

    HANDLE pipeHandle;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    const wchar_t* pipeName = Config::PipeName;

    pipeHandle = CreateNamedPipeW(
        pipeName,
        PIPE_ACCESS_INBOUND | PIPE_ACCESS_OUTBOUND,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        0,
        0,
        NMPWAIT_USE_DEFAULT_WAIT,
        nullptr
    );

    if (pipeHandle == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        LPVOID errorMessage;
        FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr,
            error,
            0, // Default language
            reinterpret_cast<LPWSTR>(&errorMessage),
            0,
            nullptr
        );
        std::wcerr << L"Error creating named pipe: " << errorMessage << L"\n";
        LocalFree(errorMessage);
        return -1;
    }


    std::cout << "C++ Server waiting for connection\n";

    while (ConnectNamedPipe(pipeHandle, nullptr)) {
        while (ReadFile(pipeHandle, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::string receivedCommand(buffer);
            processCommand(receivedCommand);
        }
        // Disconnect from the client to allow another connection
        DisconnectNamedPipe(pipeHandle);
    }

    CloseHandle(pipeHandle);

    return 0;
}
