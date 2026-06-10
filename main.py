import random
import time
import tkinter as tk

#===========#
#=Constants=#
#===========#

NAME = "Yuki Kazue"
ROMANCE = 0
MONEY = 0
RESPONSES = ["Hello", "What you up to?", "Mwah~"]
IMAGES = ['yuki.png', 'yuki_angry.png', 'yuki_clingy.png', 'yuki_embarrased.png', 'yuki_happy.png', 'yuki_jealous.png', 'yuki_soft.png', 'yuki_surprised.png']
SHOP_ITEMS = ["cake", "gift", "ring"]

#=Changeable=#

INVENTORY = []


#=Settings=#

SKETCHY = False

#==========#
#=Commands=#
#==========#


def work():
    x = 1
    print("working")
    while x <= 5:
        if x <= 5:
            time.sleep(1)
            print('.')
            x += 1
    print('Done!')

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

    decided_image = random.choice(IMAGES)

    image = tk.PhotoImage(file=f'images/{decided_image}')

    frame = tk.Frame()
    frame.pack()

    photo_label = tk.Label(frame, image=image)
    photo_label.pack()
    
    root.mainloop()


def settings():
    
    global SKETCHY
    
    print('Settings to change:')
    print(f'Sketchy Content = {SKETCHY}')
    
    s = input('What setting would you like to change? ')
    
    if s.lower() == 'sketchy content' and SKETCHY == False:
        SKETCHY = True
        print('Sketchy Content Allowed')
    else:
        SKETCHY = False
        print('Sketchy Content Blocked')

def commands():
    
    print('List of current commands:')
    print('talk')
    print('shop')
    print('give')
    print('work')
    print('look')
    print('settings')
    print('story')
    print('exit')
    print('check')
    print('help')

#=======#
#=Story=#
#=======#

def beach():
    pass

def date():
    pass

def kiss():
    pass

def her_room():
    pass


def story():
    print('Current story levels available:')
    # print('beach (min romance level: 25)')
    # print('date (min romance level: 50)')
    # print('kiss (min romance level: 75)')
    # print('her_room (min romance level: 100)')
    print('Nothing to see here...') # Placeholder
    
    
    t = input('What story short do you want to play? ')
    
    if t.lower() == 'beach' and ROMANCE >= 25:
        beach()
    
    elif t.lower() == 'date' and ROMANCE >= 50:
        date()
        
    elif t.lower() == 'kiss' and ROMANCE >= 75:
        kiss()
        
    elif t.lower() == 'her_room' and ROMANCE >= 100:
        her_room()
    else:
        print('Something went wrong')



#=================#
#=Main=Input=Loop=#
#=================#

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
    elif n.lower() == 'story':
        story()
    elif n.lower() == 'settings':
        settings()
    elif n.lower() == 'help':
        commands()
    else:
        print("Action not found- type 'help' for list of commands")