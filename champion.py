import random
import os

class Champion:
    def __init__(self, basename):
        self.basename = basename
        self.matches = 0
        self.score = 0
    def get_fitness(self):
        return self.score / self.matches
    def get_basename(self):
        return self.basename
    def compile(self):
        return
    def recompile(self):
        return
    def is_dynamic(self):
        return False
    def __lt__(self, other):
        return self.get_fitness() < other.get_fitness()

class FixedChampion(Champion):
    def __init__(self, basename):
        super().__init__(basename)
    def get_filename(self):
        return "resources/players/" + self.basename

class DynamicChampion(Champion):
    global_id = 0
    def __init__(self):
        self.id = DynamicChampion.global_id + 1
        DynamicChampion.global_id = DynamicChampion.global_id + 1
        super().__init__("champion%d.filler" % self.id)
        # TODO do bitfield genes, then get floats from a bell curve using chromosomes as input
        self.opponent_decay = random.random()
        self.self_decay = random.random() * 2 - 1
        self.wall_decay = random.random() * 2 - 1
        self.penetration_bonus = random.random() * 10 - 5
        self.wall_bonus = random.random() * 2 - 1
        self.updated = False
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