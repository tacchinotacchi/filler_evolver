import champion
import operator
import random
import itertools
from copy import deepcopy

class Bedroom:
    def __init__(self, mutation_rate=0.04, crossover_rate=0.80, extinction_rate=0.40, elitism=1):
        self.mutation_rate = mutation_rate
        self.crossover_rate = crossover_rate
        self.extinction_rate = extinction_rate
        self.elitism = elitism
    def mutate(self, champions):
        for ch in champions:
            inverted_bits = random.sample(range(len(ch.chromosome)), int(self.mutation_rate * 32 * 5))
            for index in inverted_bits:
                ch.chromosome[index] = True if ch.chromosome[index] else False
    def crossover(self, champions, target):
        children = list()
        for i in range(target):
            parents = random.sample(champions, 2)
            cross_point = random.choice(range(len(parents[0].chromosome)))
            new_chromosome = deepcopy(parents[0].chromosome[:cross_point]) + deepcopy(parents[1].chromosome[cross_point:])
            children.append(champion.DynamicChampion(new_chromosome))
        return children
    def reproduce(self, old_champions):
        champions = deepcopy(old_champions)
        original_length = len(champions)
        champions.sort(reverse=True)
        #kill off worse champions
        extinct = int(self.extinction_rate * len(champions))
        champions = champions[:extinct]
        offspring = list()
        #apply elitism
        offspring.extend(champions[:self.elitism])
        champions = champions[self.elitism:]
        #apply mutations
        self.mutate(champions)
        #apply crossover
        random.shuffle(champions)
        crossed = champions[:int(self.crossover_rate * len(champions))]
        champions = champions[int(self.crossover_rate * len(champions)):]
        #pass the remaining champions along
        offspring.extend(champions)
        offspring.extend(self.crossover(crossed, original_length - len(offspring)))
        return offspring
