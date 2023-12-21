import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk

class MultiPageApp(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        
        self.title("Multi-Page App")
        
        # Container to hold all the frames/pages
        self.container = ttk.Frame(self)
        self.container.pack(side="top", fill="both", expand=True)
        self.container.grid_rowconfigure(0, weight=1)
        self.container.grid_columnconfigure(0, weight=1)
        
        # Dictionary to store references to all pages
        self.frames = {}

        # Create and add pages to the dictionary
        for PageClass in (PageOne, PageTwo):
            frame = PageClass(self.container, self)
            self.frames[PageClass] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        
        # Show the initial page
        self.show_page(PageOne)

    def show_page(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

# Define the first page with a QR code
class PageOne(ttk.Frame):
    def __init__(self, parent, controller):
        ttk.Frame.__init__(self, parent)

        # Load the QR code image
        image_path = r'src/python/qrcode.png'
        img = Image.open(image_path)

        # Convert the Pillow Image to a Tkinter PhotoImage
        tk_img = ImageTk.PhotoImage(img)

        # Create a label to display the QR code image
        label = ttk.Label(self, image=tk_img)
        label.image = tk_img  # Keep a reference to avoid garbage collection
        label.pack(pady=10, padx=10)

        button = ttk.Button(self, text="Go to Page Two", command=lambda: controller.show_page(PageTwo))
        button.pack()

# Define the second page with grid of buttons
class PageTwo(ttk.Frame):
    def __init__(self, parent, controller):
        ttk.Frame.__init__(self, parent)

        # Initialize entry widgets
        self.entry1 = ttk.Entry(self)
        self.entry1.grid(row=1, column=1, padx=20, pady=10)

        self.entry2 = ttk.Entry(self)
        self.entry2.grid(row=1, column=2, padx=20, pady=10)

        self.entry3 = ttk.Entry(self)
        self.entry3.grid(row=1, column=3, padx=20, pady=10)

        self.entry4 = ttk.Entry(self)
        self.entry4.grid(row=1, column=4, padx=20, pady=10)

        self.entry5 = ttk.Entry(self)
        self.entry5.grid(row=1, column=5, padx=20, pady=10)

        # SECOND ROW
        self.entry6 = ttk.Entry(self)
        self.entry6.grid(row=2, column=1, padx=20, pady=10)

        self.entry7 = ttk.Entry(self)
        self.entry7.grid(row=2, column=2, padx=20, pady=10)

        self.entry8 = ttk.Entry(self)
        self.entry8.grid(row=2, column=3, padx=20, pady=10)

        self.entry9 = ttk.Entry(self)
        self.entry9.grid(row=2, column=4, padx=20, pady=10)

        self.entry10 = ttk.Entry(self)
        self.entry10.grid(row=2, column=5, padx=20, pady=10)

        # THIRD ROW
        self.entry11 = ttk.Entry(self)
        self.entry11.grid(row=3, column=1, padx=20, pady=10)

        self.entry12 = ttk.Entry(self)
        self.entry12.grid(row=3, column=2, padx=20, pady=10)

        self.entry13 = ttk.Entry(self)
        self.entry13.grid(row=3, column=3, padx=20, pady=10)

        self.entry14 = ttk.Entry(self)
        self.entry14.grid(row=3, column=4, padx=20, pady=10)

        self.entry15 = ttk.Entry(self)
        self.entry15.grid(row=3, column=5, padx=20, pady=10)

        # Load previous/saved values
        self.load_values()

        # Save values button
        save_button = ttk.Button(self, text="Save Values", command=self.save_values)
        save_button.grid(row=4, column=0, columnspan=6, pady=10)

        # Label to display save status
        self.save_status_label = ttk.Label(self, text="")
        self.save_status_label.grid(row=5, column=0, columnspan=6, pady=10)

        # Go to Page One button
        button = ttk.Button(self, text="Go to Page One", command=lambda: controller.show_page(PageOne))
        button.grid(row=6, column=0, columnspan=6, pady=10)

    def load_values(self):
        # Read values from the file and fill corresponding entries
        file_path = "src/python/user_values.txt"
        try:
            with open(file_path, "r") as file:
                lines = file.readlines()
                for i, line in enumerate(lines, start=1):
                    entry_value = line.strip().split(":")[-1]
                    entry_widget = getattr(self, f"entry{i}")
                    if not entry_value.startswith("Entry"):
                        entry_widget.insert(0, entry_value)
        except FileNotFoundError:
            print(f"File {file_path} not found.")        


    def save_values(self):
        # Retrieve values from entry widgets
        values = [
            self.entry1.get(), self.entry2.get(), self.entry3.get(), self.entry4.get(), self.entry5.get(),
            self.entry6.get(), self.entry7.get(), self.entry8.get(), self.entry9.get(), self.entry10.get(),
            self.entry11.get(), self.entry12.get(), self.entry13.get(), self.entry14.get(), self.entry15.get()
        ]

        # Save values to a text file
        file_path = "src/python/user_values.txt"
        with open(file_path, "w") as file:
            for i, value in enumerate(values, start=1):
                # Check if the entry is empty
                if value.startswith("Entry"):
                    file.write(f"Entry{i}:\n")
                elif value.strip() != "":
                    file.write(f"Entry{i}:{value}\n")
                else:
                    file.write(f"Entry{i}\n")

        self.save_status_label["text"] = f"Values saved to {file_path}"


# Run the application
if __name__ == "__main__":
    app = MultiPageApp()
    app.geometry("850x400")
    app.mainloop()
