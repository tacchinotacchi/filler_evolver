import random
import os
import re
import itertools
import threading
import champion

class Arena:
	def __init__(self, initial_population = 30, make_folder=".."):
		self.initial_population = initial_population
		if not make_folder.endswith("/"):
			make_folder = make_folder + "/"
		self.make_folder = make_folder
		self.fight_semaphore = threading.BoundedSemaphore(value=8)
		self.fight_count = 0
		fixed_filenames = [
			"jaelee.filler",
		]
		self.fix_champions = [champion.FixedChampion(filename) for filename in fixed_filenames]
		self.dyn_champions = [champion.DynamicChampion(make_folder=self.make_folder) for i in range(self.initial_population)]
	def fight(self, first, second, fight_map=("resources/maps/map01", 984)):
		first.compile()
		second.compile()
		output = os.popen("%sresources/filler_vm -q -p1 %s -p2 %s -f %s" % (
			self.make_folder,
			self.make_folder + first.get_filename(),
			self.make_folder + second.get_filename(),
			self.make_folder + fight_map[0]
		))
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
	def fight_worker(self, first, second, maps, map_weights, verbose = False):
		self.fight_semaphore.acquire()
		map = random.choices(maps, map_weights)[0]
		print("Fight number %d" % self.fight_count)
		print("Players %s and %s in map %s, fight!" % (first.get_basename(), second.get_basename(), map[0]))
		self.fight_count += 1
		self.fight(first, second, map)
		self.fight_semaphore.release()
	def	get_champions(self):
		return self.dyn_champions + self.fix_champions
	def measure_fitness(self, dyn_tries = 120, fix_tries=240):
		maps = [
			("resources/maps/map01", 984),
			("resources/maps/map02", 10000)
		]
		matches = random.choices(list(itertools.combinations(self.dyn_champions, 2)), k=dyn_tries)
		threads = list()
		for opponents in matches:
			th = threading.Thread(target=self.fight_worker,
			args=(opponents[0], opponents[1], maps, [0, 1], True))
			th.start()
			threads.append(th)
		fixed_matches = list(itertools.product(self.dyn_champions, self.fix_champions))
		for opponents in fixed_matches:
			for i in range(fix_tries // len(fixed_matches) + 1):
				opponents = list(opponents)
				random.shuffle(opponents)
				th = threading.Thread(target=self.fight_worker,
					args=(opponents[0], opponents[1], maps, [0, 1], True))
				th.start()
				threads.append(th)
		for th in threads:
			th.join()
