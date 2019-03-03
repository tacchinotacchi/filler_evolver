import random
import os
import re

class FixedChampion:
    def __init__(self, filename)
        self.filename = filename
    def get_filename(self)
        return self.filename

class DynamicChampion:
    current_id = 0
    def __init__(self):
        random.seed()
        self.opponent_decay = random.random()
        self.self_decay = random.random() * 2 - 1
        self.wall_decay = random.random() * 2 - 1
        self.penetration_bonus = random.random() * 10 - 5
        self.wall_bonus = random.random() * 2 - 1
        self.current_id = current_id + 1
        current_id = current_id + 1
    def get_filename(self):
        return "champion%d.filler" % current_id
    def output_file(self):
        file = open(self.filename(), "w+")
        write(file, "const float g_op_decay =%d" % self.opponent_decay)
        write(file, "const float g_me_decay =%d" % self.self_decay)
        write(file, "const float g_wall_decay =%d" % self.wall_decay)
        write(file, "const float g_penetration_bonus =%d" % self.penetration_bonus)
        write(file, "const float g_wall_bonus =%d" % self.wall_bonus)
        file.close()

class Arena:
    def __init__(self, initial_population = 10):
        self.champions = []
        self.initial_population = initial_population
        fixed_filenames = [
            "abanlin.filler",
            "champely.filler",
            "hcao.filler",
            "mnishimo.filler",
           "carli.filler",
            "grati.filler",
            "jaelee.filler",
            "superjeannot.filler"
        ]
        self.fix_champions.append(FixedChampion(filename) for filename in fixed_filenames)
    def new_champions(self):
        dyn_champions.append(DynamicChampion() for i in range(self.initial_population))
    def fight(self, first, second, fight_map="resources/maps/map01"):
        output = os.popen("resources/filler_vm -q -p1 %s -p2 %s -f %s" % (first.get_filename(), second.get_filename(), fight_map))
        for line in output:
            o_pattern = re.compile("== O fin: [0-9]")
            x_pattern = re.compile("X fin:")
        return [first_score, second_score]

