import socket
import win32file
from dotenv import load_dotenv
import os
import time
import select
import re

def read_macros(command):
    file_path = "user_values.txt"
    with open(file_path, 'r') as file:
        content = file.readlines()
    entries = []
    for i in range(1, 16):  # Loop through 1 to 15
        entry = content[i - 1].strip().split(':')[-1] if i <= len(content) else ''  # Extract text or use empty string
        if entry.startswith("Entry"):
            entries.append("")
        else:
            entries.append(entry)
    return entries[command]

load_dotenv()
PORT = int(os.getenv("PORT"))
PIPE = str(os.getenv("PIPE_CLIENT")) 
IP = socket.gethostbyname(socket.gethostname())

def send_command_to_cpp(command):
    pipe_name = PIPE

    try:
        pipe_handle = win32file.CreateFile(
            pipe_name,
            win32file.GENERIC_WRITE,
            0,
            None,
            win32file.OPEN_EXISTING,
            0,
            None
        )

        win32file.WriteFile(pipe_handle, command.encode('utf-8'))

    except Exception as e:
        print(f"Error sending command to C++: {str(e)}")

    finally:
        win32file.CloseHandle(pipe_handle)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((IP, PORT))
    server_socket.listen(1)

    print("Python Server waiting for connections from Java")

    client_socket = None
    pattern = r'^(1[0-5]|[0-9])$'
    try:
        while True:
            readable, _, _ = select.select([server_socket], [], [], 0.1)
            if server_socket in readable:
                client_socket, addr = server_socket.accept()
                print('Connected by', addr)

            if client_socket:
                command = client_socket.recv(1024).decode('utf-8')
                time.sleep(0.06)
                command = command.strip()  # reduces white spaces
                if re.match(pattern, command):
                    print(f'Received command from Java: {command}')
                    send_command_to_cpp(read_macros(int(command)))

    except KeyboardInterrupt:
        print("CTRL+C detected. Closing the server.")
        if client_socket:
            client_socket.close()
        server_socket.close()
