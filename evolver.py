import random
import os
import re
import itertools
import threading

class FixedChampion:
    def __init__(self, basename):
        self.basename = basename
        self.fitness = 0
    def get_basename(self):
        return self.basename
    def get_filename(self):
        return "resources/players/" + self.basename
    def compile(self):
        return
    def recompile(self):
        return
    def is_dynamic(self):
        return False

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
        self.updated = False
        self.fitness = 0
    def get_basename(self):
        return "champion%d.filler" % self.id
    def get_filename(self):
        return "pool/" + self.get_basename()
    def get_sourcename(self):
        return "pool/params/champion%d.c" % self.id
    def output_file(self):
        file = open(self.get_sourcename(), "w+")
        file.write("const float g_op_decay = %f;\n" % self.opponent_decay)
        file.write("const float g_me_decay = %f;\n" % self.self_decay)
        file.write("const float g_wall_decay = %f;\n" % self.wall_decay)
        file.write("const float g_penetration_bonus = %f;\n" % self.penetration_bonus)
        file.write("const float g_wall_bonus = %f;\n" % self.wall_bonus)
        file.write("const char *g_champion_name = \"%s\";\n" % self.get_basename())
        file.close()
    def compile(self):
        if not self.updated:
            self.output_file()
            os.system("make " + self.get_filename())
        self.updated = True
    def recompile(self):
        self.updated = False
        self.compile()
    def is_dynamic(self):
        return True

class Arena:
    fight_semaphore = threading.BoundedSemaphore(value=8)
    @staticmethod
    def fight(first, second, fight_map="resources/maps/map01"):
        first.compile()
        second.compile()
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
        first.fitness += int(first_score)
        second.fitness += int(second_score)
        return [int(first_score), int(second_score)]
    @staticmethod
    def fight_worker(first, second, maps, map_weights, verbose = False):
        Arena.fight_semaphore.acquire()
        map = random.choices(maps, map_weights)[0]
        print("Players %s and %s in map %s, fight!" % (first.get_basename(), second.get_basename(), map))
        Arena.fight(first, second, map)
        Arena.fight_semaphore.release()
    def __init__(self, initial_population = 30):
        self.initial_population = initial_population
        fixed_filenames = [
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
        self.champions = self.fix_champions + self.dyn_champions
    def measure_fitness(self, dyn_tries = 300):
        maps = [
            "resources/maps/map01",
            "resources/maps/map02"
        ]
        matches = random.sample(list(itertools.combinations(self.dyn_champions, 2)), dyn_tries)
        threads = list()
        for opponents in matches:
            th = threading.Thread(target=Arena.fight_worker,
                args=(opponents[0], opponents[1], maps, [0.85, 0.15], True))
            th.start()
            threads.append(th)
        fixed_matches = list(itertools.product(self.dyn_champions, self.fix_champions))
        for opponents in fixed_matches:
            th = threading.Thread(target=Arena.fight_worker,
                args=(opponents[0], opponents[1], maps, [0, 1], True))
            th.start()
            threads.append(th)
        for th in threads:
            th.join()
