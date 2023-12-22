import subprocess
import threading
import atexit

gui_process = None
cpp_process = None
python_process = None

def run_gui():
    global gui_process
    gui_process = subprocess.Popen(["dist/gui.exe"])
    gui_process.wait()

def run_cpp():
    global cpp_process
    cpp_process = subprocess.Popen(["dist/server.exe"])
    cpp_process.wait()

def run_python():
    global python_process
    python_process = subprocess.Popen(["dist/socket_pipe.exe"])
    python_process.wait()

def cleanup():
    global gui_process, cpp_process, python_process

    # Terminate subprocesses if they are still running
    if gui_process and gui_process.poll() is None:
        gui_process.terminate()
        cpp_process.terminate()
        python_process.terminate()

    if cpp_process and cpp_process.poll() is None:
        gui_process.terminate()
        cpp_process.terminate()
        python_process.terminate()

    if python_process and python_process.poll() is None:
        gui_process.terminate()
        cpp_process.terminate()
        python_process.terminate()

if __name__ == "__main__":
    # Register the cleanup function to be called at exit
    atexit.register(cleanup)

    # Create threads for each component
    gui_thread = threading.Thread(target=run_gui)
    cpp_thread = threading.Thread(target=run_cpp)
    python_thread = threading.Thread(target=run_python)

    # Start the threads
    gui_thread.start()
    cpp_thread.start()
    python_thread.start()

    # Wait for threads to finish
    gui_thread.join()
    cpp_thread.join()
    python_thread.join()
