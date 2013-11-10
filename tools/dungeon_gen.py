#############################
# Gameboys' Dungeon Gen 1.0 #
#############################

import sys
import random
import math

# configure random
# random.seed()

# extend a with items from b
def extend(a,b):
	try:
		for k,v in b.items():
			a[k] = v
	except:
		pass
	return a

tileSize = 8
items 	 = {
	"ITEM_WALL"  : { "probability" : 0.4, "printchar" : "#" },
	"ITEM_FLOOR" : { "probability" : 0.55, "printchar" : "." }
}

defaultDungeonConfig 	= { "refinementSteps" : 8, "items" : { "ITEM_WALL", "ITEM_FLOOR" }  } # todo: add items
defaultDungeonGenerator = { "numdungs" : 1, "numchunks" : 1 }

class Dungeon(object):
	"""docstring for Dungeon"""

	chunks = []

	def __init__( self, name, config = {}):
		super(Dungeon, self).__init__()
		self.config = extend(defaultDungeonConfig,config)
		self.name 	= "\"" + name + "\""

	def Build( self, chunks = 0 ):
		print("Building " + self.name + ":")

		wall = items["ITEM_WALL"]["printchar"]
		floor = items["ITEM_FLOOR"]["printchar"]

		# helpers
		def get_neighbours(chunk,x,y):
			max_w = len( chunk )
			max_h = len( chunk[0] )
			nlist = []

			for xi in range( x-1, x+2 ):
				for yi in range( y-1, y+2 ):
					if ( xi < 0 or xi >= max_w ):
						continue
					if ( yi < 0 or yi >= max_h ):
						continue

					nlist.append( chunk[xi][yi] )

			return nlist

		def get_by_type(tile,num_walls):
			if tile == items["ITEM_WALL"]["printchar"]:
				if num_walls >= 4:
					return wall
				if num_walls < 2:
					return floor
			else:
				if num_walls >= 5:
					return wall
			return floor


		for c in range(chunks):
			# build random initial state
			chunk_width = int(random.random() * defaultDungeonGenerator["minchunkdimW"]) + defaultDungeonGenerator["maxchunkdimW"]
			chunk_height = int(random.random() * defaultDungeonGenerator["minchunkdimH"]) + defaultDungeonGenerator["maxchunkdimH"]

			print("    %s.chunk[%d] : (%d,%d)" % (self.name, c,chunk_width,chunk_height))

			chunk = [] # [ [items["ITEM_FLOOR"]["printchar"]] * chunk_height ] * chunk_width

			# initialize chunks
			for w in range(chunk_width):

				chunk.append([])

				# print(chunk)

				for h in range(chunk_height):
					# select tile type by probability
					rnd = random.random()

					chunk[w].append(items["ITEM_FLOOR"]["printchar"])

					if rnd < items["ITEM_WALL"]["probability"]:
						chunk[w][h] = items["ITEM_WALL"]["printchar"]

			self.chunks.append(chunk)

			for r in range(self.config["refinementSteps"]):
				for cw in range(len(chunk)):
					chunk_row = chunk[cw]
					for ch in range(len(chunk_row)):
						cell_item = chunk_row[ch]

						# gather all neighbours
						neighbours = get_neighbours(chunk,cw,ch)
						num_neighs = len(neighbours)
						num_walls  = len([ x for x in neighbours if x == items["ITEM_WALL"]["printchar"] ])
						num_floor  = num_neighs - num_walls

						chunk_row[ch] = get_by_type(cell_item,num_walls)


						"""
						if cell_item == items["ITEM_WALL"]["printchar"]:
							acceptrate = int((4.0/9.0) * num_neighs)
						else:
							acceptrate = int((5.0/9.0) * num_neighs)

						if ( num_walls > acceptrate ):
							chunk_row[ch] = items["ITEM_WALL"]["printchar"]
						else:
							chunk_row[ch] = items["ITEM_FLOOR"]["printchar"]
						"""
				

	def PrettyPrint(self):
		ccount = 0
		for c in self.chunks:
			print("  %s.chunk[%d]:" % (self.name,ccount))

			for w in c:
				row = ""
				for x in w:
					row += x
					# pass
				print(row)
			print("")

			ccount += 1

	def Serialize(self):
		pass

print("Running Gameboy's Dungeon Generator 1.0")
print("---------------------------------------")

if len(sys.argv) > 1 and sys.argv[1].startswith("-h"):
	print("Usage: dungeon_gen.py min_dungeon_width max_dungeon_width min_dungeon_height max_dungeon_height")
	print("Example: dungeon_gen.py 100 200 100 200")
	sys.exit(0)
else:

	extend( defaultDungeonGenerator, 
			{"minchunkdimW" : len(sys.argv) > 1 and int(sys.argv[1]) or 20,
 			 "maxchunkdimW" : len(sys.argv) > 2 and int(sys.argv[2]) or 40,
			 "minchunkdimH" : len(sys.argv) > 3 and int(sys.argv[3]) or 18,
			 "maxchunkdimH" : len(sys.argv) > 4 and int(sys.argv[4]) or 36,})

	print("Settings")
	print("  #Dungeons       : %s" % defaultDungeonGenerator["numdungs"])
	print("  #Dungeon.chunks : %s" % defaultDungeonGenerator["numchunks"])
	print("---------------------------------------")
	print("")

for d in range(defaultDungeonGenerator["numdungs"]):
	dung = Dungeon( "Dungeon_%d" % d )
	dung.Build(defaultDungeonGenerator["numchunks"])

	print("---------------------------------------")
	print("Finished dungeon:")
	dung.PrettyPrint()

print("---------------------------------------")
print("All done.")