def convert(text):
    if (":)" in text):
        text = text.replace(":)", 🙂)
    elif (":(" in text):
        text = text.replace(":(", 🙁)
    return text


def main():
    
