# TODO

from cs50 import get_string

def main():
    text = get_string("Text: ")

    letters = float(count_letters(text))
    words = float(count_words(text))
    sentences = float(count_sentences(text))

    l = letters / words * 100
    s = sentences / words * 100
    index = int(round((0.0588 * l - 0.296 * s - 15.8),0))


    if (index >= 1 and index <= 16):
        print(f"Grade {index}")
    elif (index < 1):
        print("Before Grade 1")
    elif (index > 16):
        print("Grade 16+")

def count_letters(text):
    n = len(text)
    counter = 0
    for i in range(n):
        if ((text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z')):
            counter += 1
        else:
            counter += 0
    return counter

def count_words(text):
    n = len(text)
    counter = 1
    for i in range(n):
        if (text[i] == " "):
            counter += 1
        else:
            counter += 0
    return counter


def count_sentences(text):
    n = len(text)
    counter = 0
    for i in range(n):
        if (text[i] == '.' or text[i] == '!' or text[i] == '?'):
            counter += 1
        else:
            counter += 0
    return counter

main ()
