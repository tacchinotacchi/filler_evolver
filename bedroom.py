import operator
import random

class Bedroom:
    def __init__(self, mutation_rate=0.04, crossover_rate=0.80, extinction_rate=0.40, elitism=1):
        self.mutation_rate = mutation_rate
        self.crossover_rate = crossover_rate
        self.extinction_rate = extinction_rate
        self.elitism = elitism
    def mutate(self, champions):
        #TODO
        return
    def crossover(self, champions):
        #TODO
        return
    def reproduce(self, champions):
        champions.sort(reverse=True)
        #kill off worse champions
        extinct = int(self.extinction_rate * len(champions))
        champions = champions[:extinct]
        offspring = list()
        #apply elitism
        offspring.extend(champions[elitism:])
        champions = champions[:elitism]
        #apply mutations
        mutated = random.sample(champions, int(self.mutation_rate * len(champions)))
        self.mutate(mutated)
        #apply crossover
        random.shuffle(champions)
        crossed = champions[:int(self.crossover_rate * len(champions)))]
        champions = champions[int(self.crossover_rate * len(champions))):]
        offspring.extend(self.crossover(crossed))
        #pass the remaining champions along
        offspring.extend(champions)
        return offspring
