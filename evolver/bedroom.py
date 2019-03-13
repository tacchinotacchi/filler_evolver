import champion
import chromosome
import operator
import random
import itertools
from copy import deepcopy

class Bedroom:
	def __init__(self, mutation_rate=0.02, crossover_rate=0.80, extinction_rate=0.50, elitism=2, make_folder=".."):
		self.mutation_rate = mutation_rate
		self.crossover_rate = crossover_rate
		self.extinction_rate = extinction_rate
		self.elitism = elitism
		if not make_folder.endswith("/"):
			make_folder = make_folder + "/"
		self.make_folder = make_folder
	def mutate(self, champions):
		for ch in champions:
			mutation = random.choices([True, False], [self.mutation_rate, 1.0 - self.mutation_rate], k=len(ch.chrom.genome))
			for (index, invert) in zip(range(len(ch.chrom.genome)), mutation):
				if invert:
					ch.chrom.genome[index] = False if ch.chrom.genome[index] else True
	def crossover(self, champions, target):
		children = list()
		combs = list(itertools.combinations(champions, 2))
		for parents in random.sample(combs, target):
			cross_point = random.choice(range(len(parents[0].chrom.genome)))
			recombined = chromosome.Chromosome(
				attributes = parents[0].chrom.attributes,
				genome = parents[0].chrom.genome[:cross_point] + parents[1].chrom.genome[cross_point:]
			)
			children.append(champion.DynamicChampion(recombined, make_folder=self.make_folder))
		return children
	def reproduce(self, original_pool):
		pool = deepcopy(original_pool)
		pool.sort(reverse=True)
		# kill off low end
		pool = pool[:int((1.0 - self.extinction_rate) * len(pool))]
		offspring = list()
		# pass along elitists
		for ch in pool[:self.elitism]:
			offspring.append(champion.DynamicChampion(ch.chrom, make_folder=self.make_folder))
		# apply mutation
		self.mutate(pool[self.elitism:])
		# pass along non cross over'd champions
		random.shuffle(pool)
		for ch in pool[int(self.crossover_rate * len(pool)):]:
			offspring.append(champion.DynamicChampion(ch.chrom, make_folder=self.make_folder))
		pool = pool[:int(self.crossover_rate * len(pool))]
		target_length = len(original_pool) - len(offspring)
		offspring.extend(self.crossover(pool, target_length))
		return offspring

