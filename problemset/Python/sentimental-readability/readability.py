import cs50

# TODO
# (Letter/words) * 100
# (sencences / words) * 100
# 0.0588 * L - 0.296 * S - 15.8

string = cs50.get_string("Text: ")

# counting words
word = len(string.split())

# counting chars 29
charcount = 0
for i in string:
    if i.isalpha():
        charcount += 1

# sentences
sentence = 0
for i in string:
    if i == "?" or i == "!" or i == ".":
        sentence += 1
# calculating Grade
l = (charcount / word) * 100
s = (sentence / word) * 100
Grade = round(0.0588 * l - 0.296 * s - 15.8)

# printing results
if Grade > 16:
    print("Grade 16+")
elif Grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade: {Grade}")
