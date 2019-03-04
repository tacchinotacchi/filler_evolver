import random
import os
import re

class FixedChampion:
    def __init__(self, filename):
        self.filename = filename
    def get_filename(self):
        return "resources/players/" + self.filename

class DynamicChampion:
    global_id = 0
    def __init__(self):
        random.seed()
        self.opponent_decay = random.random()
        self.self_decay = random.random() * 2 - 1
        self.wall_decay = random.random() * 2 - 1
        self.penetration_bonus = random.random() * 10 - 5
        self.wall_bonus = random.random() * 2 - 1
        self.id = DynamicChampion.global_id + 1
        DynamicChampion.global_id = DynamicChampion.global_id + 1
    def get_filename(self):
        return "pool/champion%d.filler" % self.id
    def get_sourcename(self)
        return "pool/params/champion%d.c" % self.id
    def output_file(self):
        file = open(self.get_sourcename(), "w+")
        write(file, "const float g_op_decay =%d" % self.opponent_decay)
        write(file, "const float g_me_decay =%d" % self.self_decay)
        write(file, "const float g_wall_decay =%d" % self.wall_decay)
        write(file, "const float g_penetration_bonus =%d" % self.penetration_bonus)
        write(file, "const float g_wall_bonus =%d" % self.wall_bonus)
        file.close()

class Arena:
    def __init__(self, initial_population = 10):
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
        self.fix_champions = [FixedChampion(filename) for filename in fixed_filenames]
        self.dyn_champions = [DynamicChampion() for i in range(self.initial_population)]
    @staticmethod
    def fight(first, second, fight_map="resources/maps/map01"):
        output = os.popen("resources/filler_vm -q -p1 %s -p2 %s -f %s" % (first.get_filename(), second.get_filename(), fight_map))
        pattern = re.compile("== ([OX]) fin: ([0-9]+)")
        for line in output:
            match = pattern.match(line)
            if match is not None:
                if match.group(1) == "O":
                    first_score = match.group(2)
                elif match.group(1) == "X":
                    second_score = match.group(2)
        # TODO error if first_score or second score are None?
        return [first_score, second_score]

