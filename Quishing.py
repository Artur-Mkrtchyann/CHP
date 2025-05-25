import cv2
from pyzbar.pyzbar import decode
import hashlib
from reedsolo import RSCodec, ReedSolomonError

rs = RSCodec(10)  # 10 բայթ սխալների ուղղման համար

def decode_qr(image_path):
    # Սկանավորում է QR-ն ու ստանում տվյալը
    image = cv2.imread(image_path)
    decoded = decode(image)
    if not decoded:
        return None, image
    try:
        raw_data = decoded[0].data
        corrected = rs.decode(raw_data)[0]  # Ստանում ենք միայն տվյալը (առանց parity)
        return corrected.decode('utf-8'), image
    except ReedSolomonError:
        return None, image

def is_blurry(image, threshold=100):
  # Ստուգում է պատկերի աղոտ լինելը՝ լապլասի միջոցով
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    focus = cv2.Laplacian(gray, cv2.CV_64F).var()
    return focus < threshold

def analyze_qr_pattern(image):
    # Ստուգում է սև-սպիտակ պիքսելների հարաբերակցությունը
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, binary = cv2.threshold(gray, 128, 255, cv2.THRESH_BINARY)
    black = (binary == 0).sum()
    white = (binary == 255).sum()
    ratio = black / (white + 1)
    return 0.5 < ratio < 2.0

def simple_hash(data):
    """Հեշավորում է տվյալը SHA256-ով"""
    return hashlib.sha256(data.encode()).hexdigest()

def validate_qr(image_path):
    data, image = decode_qr(image_path)
    if not data:
        return " QR չի հայտնաբերվել կամ տվյալը վնասված է"

    if is_blurry(image):
        return "Պատկերը աղոտ է – կեղծ կամ վնասված QR"

    if not analyze_qr_pattern(image):
        return "QR պատկերի կառուցվածքը կասկածելի է – հնարավոր կեղծ QR"

    if "::" in data:
        payload, signature = data.split("::")
        hashed = simple_hash(payload)
        if hashed[:10] == signature[:10]:
            return f" Իրական QR – տվյալներ՝ {payload}"
        else:
            return "Սխալ կամ կեղծ ստորագրություն QR-ում"
    else:
        return " Չկա ստորագրություն – հնարավոր կեղծ QR"

if __name__ == "__main__":
    path = "your_qr_code.png"
    result = validate_qr(path)
    print(result)


