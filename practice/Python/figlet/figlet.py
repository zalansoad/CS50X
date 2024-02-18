import sys
from pyfiglet import Figlet
import random

if len(sys.argv) != 3 and len(sys.argv) != 1:
    sys.exit(1)

if len(sys.argv) == 3 and (sys.argv[1] != "-f" and sys.argv[1] != "--font"):
    sys.exit(1)

figlet = Figlet()

if len(sys.argv) == 3 and (sys.argv[2] not in figlet.getFonts()):
    sys.exit(1)

# prompting for input
text = input("Input: ")

# 0 commant line aregument - random font
if len(sys.argv) == 1:
    figlet.setFont(font=random.choice(figlet.getFonts()))
    print(figlet.renderText(text))

# 2 commant line aregument - random font
elif len(sys.argv) == 3:
    figlet.setFont(font=sys.argv[2])
    print(figlet.renderText(text))