import random

CAR = "the car"
GOAT = "a goat"
    
    
class Doors:
    
    def __init__(self, car):
        self.car = car
        self.num = range(3)
    
    def open(self, index):
        return CAR if index == self.car else GOAT    


class Contestant:

    def make_initial_choice(self):
        self.choice = random.randint(0, 2)
        print("C: I choose door number {}.".format(self.choice + 1))
        return self.choice


class NaiveContestant(Contestant):

    def make_final_choice(self, option):
        print("C: I keep door number {}.".format(self.choice + 1))
        return self.choice


class SmartContestant(Contestant):

    def make_final_choice(self, option):
        print("C: I pick door {}.".format(option + 1))
        return option


class Host:

    def start_game(self, doors, contestant):
        print("H: Pick a door...")
        initial_choice = contestant.make_initial_choice()
        my_door = self.choose_a_door(doors, initial_choice)
        prize_behind_my_door = doors.open(my_door)
        print("H: Behind door number {} there's... {}!".format(
            my_door + 1, prize_behind_my_door))
        if prize_behind_my_door == CAR:
            print("H: Ops, you loose...")
            return GOAT
        option = [x for x in doors.num if x not in [initial_choice, my_door]][0]
        print("H: Do you want to pick door number {}?".format(option + 1))
        final_choice = contestant.make_final_choice(option)
        if final_choice == initial_choice:
            print("H: You keep door number {}...".format(final_choice + 1))
        else:
            print("H: You choose door number {}...".format(final_choice + 1))
        prize = doors.open(final_choice)
        print("H: You won... {}!".format(prize))
        return prize


class AwareHost(Host):

    def choose_a_door(self, doors, initial_choice):
        unfit_doors = [initial_choice, doors.car]
        suitable_doors = [x for x in doors.num if x not in unfit_doors]
        return random.choice(suitable_doors)


class UnawareHost(Host):

    def choose_a_door(self, doors, initial_choice):
        suitable_doors = [x for x in doors.num if x != initial_choice]
        return random.choice(suitable_doors)


def play():
    doors = Doors(random.randint(0, 2))
    contestant = NaiveContestant()
    host = UnawareHost()
    return host.start_game(doors, contestant)


if __name__ == "__main__":
    GAMES = 1000
    wins = sum(1 for x in range(GAMES) if play() == CAR)
    print("{} wins on {} games ({:.1f}%)".format(
        wins, GAMES, wins * 100. / GAMES))
