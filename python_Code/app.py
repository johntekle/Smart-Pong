from flask import Flask, render_template
from threading import Thread
import time
from simple_rpc import Interface
from rpc import Smart_Pong_RPC

app = Flask(__name__)

smart_rpc = None

cupA_detected = False
cupB_detected = False
button_detected = False

smart_rpc = Smart_Pong_RPC("COM11")
time.sleep(3)

def poll_sensors():
    global cupA_detected, cupB_detected, button_detected

    while True:
        try:
            if smart_rpc.get_cup_A():
                if not cupA_detected:
                    cupA_detected = True
                # time.sleep(0.05)
            else:
                if cupA_detected:
                    cupA_detected = False
                # time.sleep(0.05)

            if smart_rpc.get_cup_B():
                if not cupB_detected:
                    cupB_detected = True
                # time.sleep(0.05)
            else:
                if cupB_detected:
                    cupB_detected = False
                # time.sleep(0.05)

            button_detected = smart_rpc.get_button()

        except KeyboardInterrupt as e:
            print("\nProgramm is interrupted!\n")
            break

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_status')
def get_status():
    global cupA_detected, cupB_detected, button_detected
    # print(button_detected)
    return {'cup_A_status': cupA_detected, 'cup_B_status': cupB_detected, 'button_status': button_detected}

if __name__ == '__main__':
    poll_thread = Thread(target=poll_sensors)
    poll_thread.daemon = True
    poll_thread.start()
    app.run(debug=False)
