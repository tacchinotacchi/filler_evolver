import champion
import operator
import random
import itertools
from copy import deepcopy

class Bedroom:
	def __init__(self, mutation_rate=0.02, crossover_rate=0.80, extinction_rate=0.50, elitism=2):
		self.mutation_rate = mutation_rate
		self.crossover_rate = crossover_rate
		self.extinction_rate = extinction_rate
		self.elitism = elitism
	def mutate(self, champions):
		for ch in champions:
			mutation = random.choices([True, False], [self.mutation_rate, 1.0 - self.mutation_rate], k=len(ch.chromosome))
			invert = (bit for bit in mutation if bit)
			for index in invert:
				mutated_genes[index] = False if mutated_genes[index] else True
	def crossover(self, champions, target):
		children = list()
		combs = list(itertools.combinations(champions, 2))
		for parents in random.sample(combs, target):
			cross_point = random.choice(range(len(parents[0].chromosome)))
			recombined = parents[0].chromosome[:cross_point] + parents[1].chromosome[cross_point:]
			children.append(champion.DynamicChampion(recombined))
		return children
	def reproduce(self, original_pool):
		pool = deepcopy(original_pool)
		pool.sort(reverse=True)
		# kill off low end
		pool = pool[:int((1.0 - self.extinction_rate) * len(pool))]
		offspring = list()
		# pass along elitists
		for ch in pool[:self.elitism]:
			offspring.append(champion.DynamicChampion(ch.chromosome))
		# apply mutation
		self.mutate(pool[self.elitism:])
		# pass along non cross over'd champions
		random.shuffle(pool)
		for ch in pool[int(self.crossover_rate * len(pool)):]:
			offspring.append(champion.DynamicChampion(ch.chromosome))
		pool = pool[:int(self.crossover_rate * len(pool))]
		target_length = len(original_pool) - len(offspring)
		offspring.extend(self.crossover(pool, target_length))
		return offspring

