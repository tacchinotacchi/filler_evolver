import random

class Attribute:
	def __init__(self, size=32, name=None):
		self.name = name
		self.size = size
		self.loc = 0
	def get(self, genome):
		uniform = 0
		for base in zip(genome[self.loc:(self.loc + self.size)], range(self.size - 1, -1, -1)):
			if base[0]:
				uniform += (1 << base[1])
		return uniform

class FloatAttribute(Attribute):
	def __init__(self, size=32, name=None, min=-1.0, max=1.0):
		super().__init__(size, name)
		self.min = min
		self.max = max
	def get(self, genome):
		uniform = super().get(genome)
		# TODO custom distribution
		return (float(uniform) / ((1 << self.size) - 1)) * (self.max - self.min) + self.min


class Chromosome:
	def __init__(self, attributes, genome=None):
		length_so_far = 0
		self.attributes = attributes
		if genome is None:
			self.genome = []
		else:
			self.genome = genome
		for attr in self.attributes:
			attr.loc = length_so_far
			length_so_far += attr.size
			if genome is None:
				self.genome.extend([random.choice([True, False]) for i in range(attr.size)])
	def get_attr(self, index=0, name=None):
		if name is not None:
			attr = self.find_by_name(name)
		else:
			attr = self.attributes[index]
		return attr.get(self.genome)
	def find_by_name(self, name):
		for attr in self.attributes:
			if attr.name == name:
				return attr