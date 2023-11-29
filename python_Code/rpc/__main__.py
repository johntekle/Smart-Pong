from rpc import Smart_Pong_RPC
from colorama import Fore, Style
import time
import sys

smart_rpc = Smart_Pong_RPC("COM11")

time.sleep(2)

cup1_detected = False
cup2_detected = False

def clear_output():
    print("\033[H\033[J")  # Löscht das Terminal


while True:
    try:
        if smart_rpc.get_cup_A():
            if not cup1_detected:
                cup1_detected = True
            time.sleep(0.05)
        else:
            if cup1_detected:
                cup1_detected = False
            time.sleep(0.05)

        if smart_rpc.get_cup_B():
            if not cup2_detected:
                cup2_detected = True
            time.sleep(0.05)
        else:
            if cup2_detected:
                cup2_detected = False
            time.sleep(0.05)

        clear_output()
        if cup1_detected:
            print(Fore.GREEN + 'Erster Becher ist platziert.' + Style.RESET_ALL)
        else:
            print(Fore.GREEN + 'Erster Becher wurde entfernt.' + Style.RESET_ALL)

        if cup2_detected:
            print(Fore.YELLOW + 'Zweiter Becher ist platziert.' + Style.RESET_ALL)
        else:
            print(Fore.YELLOW + 'Zweiter Becher wurde entfernt.' + Style.RESET_ALL)

    except KeyboardInterrupt as e:
        print("\nProgramm is interrupted!\n")
        sys.exit()
        