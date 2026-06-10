import random
import time
import tkinter as tk

NAME = "Yuki Kazue"
ROMANCE = 0
MONEY = 0
INVENTORY = []
SHOP_ITEMS = ["cake", "gift", "ring"]


RESPONSES = ["Hello", "What you up to?", "Mwah~"]



def work():
    x = 0
    print("working")
    while x <= 5:
        if x <= 5:
            time.sleep(1)
            x += 1

    global MONEY
    MONEY += 5

def talk():
    resp = random.choice(RESPONSES)
    print(resp)

def shop():
    i = input(f"What do you want to buy {SHOP_ITEMS}? ")
    global MONEY
    if i.lower() == "cake" and MONEY >= 5:
        print("You bought cake")
        MONEY -= 5
        INVENTORY.append('cake')
        print(INVENTORY)
    elif i.lower() == "gift" and MONEY >= 10:
        MONEY -= 10
        print("You bought gift")
        INVENTORY.append('gift')
        print(INVENTORY)
    elif i.lower() == "ring" and MONEY >= 100:
        MONEY -= 100
        print("You bought ring")
        INVENTORY.append('ring')
        print(INVENTORY)
    else:
        print("You poor")
    

def give_item():
    global ROMANCE
    x = input("What are you giving Yuki? ")
    if x == 'cake' and 'cake' in INVENTORY:
        print('Thank you!')
        INVENTORY.remove('cake')
        ROMANCE += 5
    elif x == 'gift' and 'gift' in INVENTORY:
        print('Really for me?!')
        INVENTORY.remove('gift')
        ROMANCE += 10
    elif x == 'ring' and 'ring' in INVENTORY:
        print("Wow it's beautiful!")
        INVENTORY.remove('ring')
        ROMANCE += 20
    else:
        print("you dont have any items")
        

def check():
    print("Your stats:")
    print(f"Romance: {ROMANCE}")
    print(f"Money: {MONEY}")
    print(f"Inventory: {INVENTORY}")

def view_window():
    
    root = tk.Tk()
    root.title("Yuki Kazue")

    image = tk.PhotoImage(file='images/yuki.png')

    frame = tk.Frame()
    frame.pack()

    photo_label = tk.Label(frame, image=image)
    photo_label.pack()
    
    root.mainloop()

while True:
    n = input(": ")
    if n.lower() == "talk":
        talk()
    elif n.lower() == "work":
        work()
    elif n.lower() == 'check':
        check()
    elif n.lower() == 'shop':
        shop()
    elif n.lower() == 'give':
        give_item()
    elif n.lower() == 'exit':
        break
    elif n.lower() == 'look':
        view_window()
    else:
        print("Action not found")
