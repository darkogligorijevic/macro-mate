import qrcode
from dotenv import load_dotenv
import socket
import os

load_dotenv()
PORT = int(os.getenv("PORT"))
IP = socket.gethostbyname(socket.gethostname())

# Combine IP and port into a string
data_to_send = f"{IP}+{PORT}"

# Generate QR code
qr = qrcode.QRCode(
    version=1,
    error_correction=qrcode.constants.ERROR_CORRECT_L,
    box_size=10,
    border=4,
)
qr.add_data(data_to_send)
qr.make(fit=True)

# Create an image from the QR code
img = qr.make_image(fill_color="black", back_color="white")

# Save the QR code image
img.save("qrcode.png")
