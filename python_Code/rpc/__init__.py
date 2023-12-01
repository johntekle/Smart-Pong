from simple_rpc import Interface


class Smart_Pong_RPC():

    def __init__(self, port='', baudrate=230400) -> None:
        try:
            self.interface = Interface(port, baudrate)
        except Exception as e:
            print(e)

    def get_cup_A(self) -> bool:
        try:
            if self.interface.get_sensor1():
                return True
            return False
        except Exception as e:
            print(e)

    def get_cup_B(self) -> bool:
        try:
            if self.interface.get_sensor2():
                return True
            return False
        except Exception as e:
            print(e)

    def get_button(self) -> bool:
        try:
            if self.interface.get_button():
                return True
            return False
        except Exception as e:
            print(e)
