import random
import os
import re
import itertools
import threading
import champion

class Arena:
	fight_semaphore = threading.BoundedSemaphore(value=8)
	@staticmethod
	def fight(first, second, fight_map=("resources/maps/map01", 984)):
		first.compile()
		second.compile()
		output = os.popen("resources/filler_vm -q -p1 %s -p2 %s -f %s" % (first.get_filename(), second.get_filename(), fight_map[0]))
		pattern = re.compile("== ([OX]) fin: ([0-9]+)")
		for line in output:
			match = pattern.match(line)
			if match is not None:
				if match.group(1) == "O":
					first_score = match.group(2)
				elif match.group(1) == "X":
					second_score = match.group(2)
		# TODO error if first_score or second score are None?
		first.matches += 1
		second.matches += 1
		first.score += float(first_score) / fight_map[1]
		second.score += float(second_score) / fight_map[1]
		return [int(first_score), int(second_score)]
	@staticmethod
	def fight_worker(first, second, maps, map_weights, verbose = False):
		Arena.fight_semaphore.acquire()
		map = random.choices(maps, map_weights)[0]
		print("Players %s and %s in map %s, fight!" % (first.get_basename(), second.get_basename(), map[0]))
		Arena.fight(first, second, map)
		Arena.fight_semaphore.release()
	def __init__(self, initial_population = 30):
		self.initial_population = initial_population
		fixed_filenames = [
			"mnishimo.filler",
			"jaelee.filler",
		]
		self.fix_champions = [champion.FixedChampion(filename) for filename in fixed_filenames]
		self.dyn_champions = [champion.DynamicChampion() for i in range(self.initial_population)]
	def	get_champions(self):
		return self.dyn_champions + self.fix_champions
	def measure_fitness(self, dyn_tries = 180, fix_tries=250):
		maps = [
			("resources/maps/map01", 984),
			("resources/maps/map02", 10000)
		]
		matches = random.choices(list(itertools.combinations(self.dyn_champions, 2)), k=dyn_tries)
		threads = list()
		for opponents in matches:
			th = threading.Thread(target=Arena.fight_worker,
			args=(opponents[0], opponents[1], maps, [0, 1], True))
			th.start()
		threads.append(th)
		fixed_matches = list(itertools.product(self.dyn_champions, self.fix_champions))
		for opponents in random.choices(fixed_matches, k=fix_tries):
			opponents = list(opponents)
			random.shuffle(opponents)
			th = threading.Thread(target=Arena.fight_worker,
				args=(opponents[0], opponents[1], maps, [0, 1], True))
			th.start()
			threads.append(th)
		for th in threads:
			th.join()
