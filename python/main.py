import random
import time
import tkinter as tk
from colorama import Fore, Back, init
import os

#===========#
#=Constants=#
#===========#

init(autoreset=True)

NAME = "Yuki Kazue"
ROMANCE = 0
MONEY = 0
RESPONSES = ["Hello", "What you up to?", "Mwah~"]
IMAGES = ['yuki.png', 'yuki_angry.png', 'yuki_clingy.png', 'yuki_embarrassed.png', 'yuki_happy.png', 'yuki_jealous.png', 'yuki_soft.png', 'yuki_surprised.png']
SHOP_ITEMS = ["cake", "gift", "ring"]
STARTUP = True

#=Changeable=#

INVENTORY = []


#=Settings=#

SKETCHY = False

#=Saves=#

money = 0
romance = 0
inventory = 0

saves_dir = os.path.join(os.getcwd(), 'saves')
save_location1 = os.path.join(saves_dir, 'numsave.txt')
save_location2 = os.path.join(saves_dir, 'lisave.txt')

#=Story=#

story_dir = os.path.join(os.getcwd(), 'story')
date_story = os.path.join(story_dir, 'beach.txt')

#==========#
#=Commands=#
#==========#

def clear():
    
    if os.name != 'nt':
        os.system('clear')
    else:
        os.system('cls')

def loading_animation(sec):
    while sec > 0:
        print(random.choice(['.', '..', '...', '....']))
        time.sleep(1)
        clear()
        sec -= 1

def load_save():
    
    global money, romance, inventory, saves_dir, save_location1, save_location2, MONEY, ROMANCE, INVENTORY
    
    
    os.makedirs(saves_dir, exist_ok=True)
    
    if os.path.isfile(save_location1): 
        try:
            with open(save_location1, "r") as f:
        
        
                money = int(f.readline())
                romance = int(f.readline())
                f.close()
        
            if money > 0:
                MONEY = money
                ROMANCE = romance
        except:
            MONEY = 0
            ROMANCE = 0
    else:
        with open(save_location1, "x") as f:
            pass
    if os.path.isfile(save_location2):
        with open(save_location2, "r") as f:
            inventory = list(f.read().splitlines())
            f.close()
        for item in inventory:
            INVENTORY.append(item)
    else:
        with open(save_location2, "x") as f:
            pass
    time.sleep(4)

def save():
    
    with open(save_location1, "w") as f:
        
        f.write(f"{MONEY}\n")
        f.write(f'{ROMANCE}\n')
        f.close()
    with open(save_location2, "w") as f:
        
        for g in INVENTORY:
            f.write(f"{g}\n")
    loading_animation(2)

def start():
    
    print(f'Welcome to {Fore.RED}Date-ify')
    print('Loading save:')
    load_save()
    print(f'{Fore.GREEN} Done!')
    print('Loading Game:')
    time.sleep(2)
    print(f'{Fore.GREEN} Done!')
    
    

def work():
    x = 1
    print("working")
    while x <= 5:
        if x <= 5:
            time.sleep(1)
            print('.')
            x += 1
    print(f'{Fore.GREEN} Done!')

    global MONEY
    MONEY += 5

def talk():
    resp = random.choice(RESPONSES)
    print(f'Yuki: {resp}')

def shop():
    
    shopping = True
    
    while shopping:
    
    
        print(f"Welcome to the shop! Type {Fore.RED}'exit'{Fore.WHITE} to exit to the main game!\n")
        
        i = input(f"What do you want to buy {SHOP_ITEMS}? ")
        global MONEY
        
        if i.lower() == 'exit':    
            break
        else:
            if 'cake' in INVENTORY:
                if i.lower() == "cake" and MONEY >= 5:
                    print(f'{Fore.RED}You already have a cake')
                else:    
                    print("You bought cake")
                    MONEY -= 5
                    INVENTORY.append('cake')
                    print(INVENTORY)
            if 'gift' in INVENTORY:
                if i.lower() == "gift" and MONEY >= 10:
                    print(f'{Fore.RED}You already have a gift')
                else:
                    MONEY -= 10
                    print("You bought gift")
                    INVENTORY.append('gift')
                    print(INVENTORY)
            if 'ring' in INVENTORY:
                
                if i.lower() == "ring" and MONEY >= 100:
                    print(f'{Fore.RED}You already have a ring')
                else:
                    MONEY -= 100
                    print("You bought ring")
                    INVENTORY.append('ring')
                    print(INVENTORY)
            else:
                print(f"{Fore.RED}You're too poor to afford anything")

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


    if ROMANCE <= 49:
        decided_image = random.choice(["yuki.png", "yuki_angry.png", "yuki_jealous.png"])
    elif ROMANCE > 49  and ROMANCE < 100:
        decided_image = random.choice(["yuki.png", "yuki_soft.png", "yuki_embarrassed.png"])
    elif ROMANCE >= 100 and ROMANCE :
        decided_image = random.choice(["yuki.png", "yuki_soft.png", "yuki_embarrassed.png", "yuki_happy.png", "yuki_surprised.png", "yuki_clingy.png"])

    image = tk.PhotoImage(file=f'images/{decided_image}')

    frame = tk.Frame()
    frame.pack()

    photo_label = tk.Label(frame, image=image)
    photo_label.pack()
    
    root.mainloop()


def settings():
    
    global SKETCHY
    
    print('Settings available to change:')
    print(f'Sketchy Content = {SKETCHY}')
    
    s = input('What setting would you like to change? ')
    
    if s.lower() == 'sketchy content' and SKETCHY == False:
        SKETCHY = True
        print('Sketchy Content Allowed')
    elif s.lower() == 'sketchy content' and SKETCHY == True:
        SKETCHY = False
        print('Sketchy Content Blocked')
    else:
        print('Setting not found')

def commands():

    print(f'List of current commands:\n {Fore.RED} talk- {Fore.WHITE} Yuki will say something\n {Fore.RED} shop- {Fore.WHITE} Opens the shop\n {Fore.RED} give- {Fore.WHITE} Give Yuki an item\n {Fore.RED} work- {Fore.WHITE} Work for money to spend in the shop\n {Fore.RED} look- {Fore.WHITE} Opens a picture of Yuki (Changes via romance level)\n {Fore.RED} settings- {Fore.WHITE} Change the settings\n story- {Fore.WHITE} Play story shorts\n {Fore.RED} exit- {Fore.WHITE} Exit the game with after saving\n{Fore.Red} !exit- {Fore.WHITE} Exit without saving\n {Fore.RED} check- {Fore.WHITE} Check stats\n {Fore.RED} help- {Fore.WHITE} Open this menu\n {Fore.RED} save- {Fore.WHITE} Save\n {Fore.RED} clear- {Fore.WHITE} Clear the screen')

#=======#
#=Story=#
#=======#



def beach():
    
    with open(date_story, "r") as f:
        date = f.read().splitlines()
        
        for thing in date:
            print(thing)

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

while STARTUP == True:
    start()
    STARTUP = False

while True:
    n = input(f"{Fore.BLUE}> ")
    
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
        print('Saving')
        save()
        break
    elif n.lower() == '!exit':
        break
    elif n.lower() == 'look':
        view_window()
    elif n.lower() == 'story':
        story()
    elif n.lower() == 'settings':
        settings()
    elif n.lower() == 'help':
        commands()
    elif n.lower() == 'save':
        save()
    elif n.lower() == 'clear':
        clear()
    else:
        print(f"{Fore.RED} Action not found- type 'help' for list of commands")