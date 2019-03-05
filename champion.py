import random
import os
import math

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
    @staticmethod
    def gene_to_float(bits):
        uniform = 0
        for base in zip(bits, range(31, -1, -1)):
            if base[0]:
                uniform += (1 << base[1])
        # TODO use normal distribution
        return (float(uniform) / (1 << 32)) * 2 - 1
    def __init__(self, chromosome = None):
        self.id = DynamicChampion.global_id + 1
        DynamicChampion.global_id = DynamicChampion.global_id + 1
        super().__init__("champion%d.filler" % self.id)
        self.updated = False
        if chromosome is None:
            self.chromosome = list()
            for i in range(32 * 5):
                self.chromosome.append(random.choice([False, True]))
        else:
            self.chromosome = chromosome
    def get_filename(self):
        return "pool/" + self.get_basename()
    def get_sourcename(self):
        return "pool/params/champion%d.c" % self.id
    def output_file(self):
        opponent_decay = DynamicChampion.gene_to_float(self.chromosome[0:32])
        self_decay = DynamicChampion.gene_to_float(self.chromosome[32:64])
        wall_decay = DynamicChampion.gene_to_float(self.chromosome[64:96])
        penetration_bonus = DynamicChampion.gene_to_float(self.chromosome[96:128])
        wall_bonus = DynamicChampion.gene_to_float(self.chromosome[128:160])
        file = open(self.get_sourcename(), "w+")
        file.write("const float g_op_decay = %f;\n" % opponent_decay)
        file.write("const float g_me_decay = %f;\n" % self_decay)
        file.write("const float g_wall_decay = %f;\n" % wall_decay)
        file.write("const float g_penetration_bonus = %f;\n" % penetration_bonus)
        file.write("const float g_wall_bonus = %f;\n" % wall_bonus)
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