import socket
import win32pipe, win32file
from dotenv import load_dotenv
import os
import time

load_dotenv()
PORT = int(os.getenv("PORT"))
PIPE_CLIENT = str(os.getenv("PIPE_CLIENT"))
IP = socket.gethostbyname(socket.gethostname())

def send_command_to_cpp(command):
    pipe_name = PIPE_CLIENT

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
    conn, addr = server_socket.accept()
    while True:
        print('Connected by', addr)
        command = conn.recv(1024).decode('utf-8')
        time.sleep(0.125)
        command = command.strip() # reduces white spaces
        print(f'Received command from Java: {command}')
        send_command_to_cpp(command)
        

