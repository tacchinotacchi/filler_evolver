import random
import os
import chromosome

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
	def __str__(self):
		return "%s %f" % (self.get_basename(), self.get_fitness())

class FixedChampion(Champion):
	def __init__(self, basename):
		super().__init__(basename)
	def get_filename(self):
		return "resources/players/" + self.basename

class DynamicChampion(Champion):
	global_id = 0
	def __init__(self, chrom = None, make_folder=".."):
		self.id = DynamicChampion.global_id + 1
		DynamicChampion.global_id = DynamicChampion.global_id + 1
		super().__init__("champion%d.filler" % self.id)
		self.updated = False
		if not make_folder.endswith("/"):
			make_folder = make_folder + "/"
		self.make_folder = make_folder
		if chrom is None:
			attributes = [
				chromosome.FloatAttribute(size=32, name="g_op_decay", min=0.0, max=1.0),
				chromosome.FloatAttribute(size=32, name="g_me_decay", min=0.0, max=1.0),
				chromosome.FloatAttribute(size=32, name="g_wall_decay", min=0.0, max=1.0),
				chromosome.FloatAttribute(size=32, name="g_penetration_bonus", min=-1.0, max=1.0),
				chromosome.FloatAttribute(size=32, name="g_wall_bonus", min=-1.0, max=1.0),
				chromosome.FloatAttribute(size=32, name="g_meop_importance", min=0.00, max=1.0),
				chromosome.FloatAttribute(size=32, name="g_wallop_importance", min=0.00, max=1.0)
			]
			self.chrom = chromosome.Chromosome(attributes)
		else:
			self.chrom = chrom
	def get_filename(self):
		return "pool/" + self.get_basename()
	def get_sourcename(self):
		return "pool/params/champion%d.c" % self.id
	def output_file(self):
		file = open(self.make_folder + self.get_sourcename(), "w+")
		file.write("const float g_op_decay = %f;\n" % self.chrom.get_attr(name="g_op_decay"))
		file.write("const float g_me_decay = %f;\n" % self.chrom.get_attr(name="g_me_decay"))
		file.write("const float g_wall_decay = %f;\n" % self.chrom.get_attr(name="g_wall_decay"))
		file.write("const float g_penetration_bonus = %f;\n" % self.chrom.get_attr(name="g_penetration_bonus"))
		file.write("const float g_wall_bonus = %f;\n" % self.chrom.get_attr(name="g_wall_bonus"))
		file.write("const float g_meop_importance = %f;\n" % self.chrom.get_attr(name="g_meop_importance"))
		file.write("const float g_wallop_importance = %f;\n" % self.chrom.get_attr(name="g_wallop_importance"))
		file.write("const char *g_champion_name = \"%s\";\n" % self.get_basename())
		file.close()
	def compile(self):
		if not self.updated:
			self.output_file()
			os.system("make -C %s %s" % (self.make_folder, self.get_filename()))
		self.updated = True
	def recompile(self):
		self.updated = False
		self.compile()
	def is_dynamic(self):
		return True
