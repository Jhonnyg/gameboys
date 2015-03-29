#############################
# Gameboys' Dungeon Gen 1.0 #
#############################

import sys
import random
import math
import os


DUNG_HEADER = "\
#ifndef __DUNGEON_H__\n\
#define __DUNGEON_H__\n\
"

DUNG_FOOTER = "\
#endif\n\n\
"

# extend a with items from b
def extend(a,b):
	try:
		for k,v in b.items():
			a[k] = v
	except:
		pass
	return a

# Modified from build/pack_sprite.py
def hexify(name, data):
    hex_chunk = [ "0x%02X" % b + ("\n    " if index % 16 == 15  and index != len(data)-1 else "") 
    				for index,b in enumerate(data) ]
    hex_data = "const unsigned char %s[] = {\n     " % name
    hex_data += ",".join(hex_chunk)
    hex_data += "\n};\n"

    return hex_data

tileSize = 8
items 	 = {
	"ITEM_WALL"  : { "probability" : 0.4, "printchar" : "#" },
	"ITEM_FLOOR" : { "probability" : 0.55, "printchar" : "." }
}

defaultDungeonConfig 	= { "refinementSteps" : 8, "items" : { "ITEM_WALL", "ITEM_FLOOR" }  } # todo: add items
defaultDungeonGenerator = { "numdungs" : 1, "numchunks" : 1 }

class NeighbourInfo(object):
	"""docstring for NeighbourInfo"""
	neighbours = []

	def __init__(self,dim = 3):
		super(NeighbourInfo, self).__init__()
		self.dim 		= dim
		self.neighbours = []

		for y in range(dim):
			self.neighbours.append([])
			for x in range(dim):
				self.neighbours[y].append(-1)

	def Count(self,typ = None):
		valid = 0
		for y in self.neighbours:
			for x in y:
				if x != -1:
					if typ != None:
						if x == typ:
							valid += 1
					else:
						valid += 1

		# print(valid)

		return valid

class Dungeon(object):
	"""docstring for Dungeon"""

	chunks = []

	def __init__( self, name, config = {}):
		super(Dungeon, self).__init__()
		self.config = extend(defaultDungeonConfig,config)
		self.name 	= name

	def GetNeighbours(self,chunk,x,y):
		max_w = len( chunk )
		max_h = len( chunk[0] )

		info = NeighbourInfo()

		for xi in range( x-1, x+2 ):
			for yi in range( y-1, y+2 ):
				if ( xi < 0 or xi >= max_w ):
					continue
				if ( yi < 0 or yi >= max_h ):
					continue

				info.neighbours[ xi - (x-1) ][ yi - (y-1) ] = chunk[xi][yi]

		# print(x,y,info.neighbours)

		return info


	def Build( self, chunks = 0 ):
		print("Building " + self.name + ":")

		wall 	= items["ITEM_WALL"]["printchar"]
		floor 	= items["ITEM_FLOOR"]["printchar"]

		def get_by_type(tile,num_walls):
			if tile == wall:
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
			chunk_width 	= 128 #int(random.random() * defaultDungeonGenerator["minchunkdimW"]) + defaultDungeonGenerator["maxchunkdimW"]
			chunk_height 	= 128 #int(random.random() * defaultDungeonGenerator["minchunkdimH"]) + defaultDungeonGenerator["maxchunkdimH"]

			print("    %s.chunk[%d] : (%d,%d)" % (self.name, c,chunk_width,chunk_height))

			chunk = [] # [ [items["ITEM_FLOOR"]["printchar"]] * chunk_height ] * chunk_width

			# initialize chunks
			for w in range(chunk_width):

				chunk.append([])

				# print(chunk)

				for h in range(chunk_height):
					# select tile type by probability
					rnd = random.random()

					chunk[w].append(floor)

					if rnd < items["ITEM_WALL"]["probability"]:
						chunk[w][h] = wall

			self.chunks.append(chunk)

			for r in range(self.config["refinementSteps"]):
				print("  %s.refinementStep %d" % ( self.name, r ))
				for cw in range(len(chunk)):
					chunk_row = chunk[cw]
					for ch in range(len(chunk_row)):
						cell_item = chunk_row[ch]

						# gather all neighbours
						neighbourInfo 	= self.GetNeighbours(chunk,cw,ch)
						num_neighs 		= neighbourInfo.Count()
						num_walls 		= neighbourInfo.Count(wall)
						num_floor 		= num_neighs - num_walls

						chunk_row[ch] = get_by_type(cell_item,num_walls)				

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

	def Finalize(self):
		wall 	= items["ITEM_WALL"]["printchar"]
		floor 	= items["ITEM_FLOOR"]["printchar"]

		def is_valid(n):
			return n != -1

		def is_floor(c):
			return c == floor

		def is_wall(c):
			return c == wall

		def match(wall_str,neighbours):
			cnt = 0
			for s in wall_str:
				x = cnt % 3
				y = cnt / 3

				cnt += 1
				if s == "-":
					continue

				if s != neighbours[y][x]:
					return False
			return True				

		# dungeon file
		outdir = os.path.normpath(os.path.abspath("../build/gen/"))

		try:
			os.mkdir(outdir)
		except:
			pass

		dungfile = open( os.path.normpath(outdir + "/dungeon.h"), "w")
		dungfile.write( DUNG_HEADER )

		chunks_copy 		= []
		chunks_bytebuffer 	= []

		for c in self.chunks:

			chunk_copy = []

			bytebuffer = []

			for cw in range(len(c)):
				chunk_row = c[cw]
				chunk_copy.append([])
				for ch in range(len(chunk_row)):
					chunk_copy[cw].append(chunk_row[ch])

					# gather all neighbours
					neighbourInfo 	= self.GetNeighbours(c,cw,ch)

					this = chunk_row[ch]
					byte = 0x00 # floor byte?

					if is_wall(this):
						"""
						mask legend:

						# wall
						. floor
						- dontcare

						WALL_LEFT:
						-#-
						.##
						-#-

						WALL_RIGHT:
						-#-
						##.
						-#-

						WALL_NORTH:
						-.-
						###
						-#-

						WALL_SOUTH:
						-#-
						###
						-.-

						CORNER_NORTH_WEST:
						..-
						.##
						-#-

						CORNER_NORTH_EAST:
						-..
						##.
						-#-

						CORNER_SOUTH_WEST:
						-#-
						.##
						..-

						CORNER_SOUTH_WEST:
						-#-
						##.
						-..

						"""

						byte = 0x01

						if ( match( "-#-.##-#-", neighbourInfo.neighbours ) ): # WALL_LEFT
							chunk_copy[cw][ch] = "]"
						elif ( match( "-#-##.-#-", neighbourInfo.neighbours ) ): # WALL_RIGHT
							chunk_copy[cw][ch] = "["
						elif ( match( "-.-###-#-", neighbourInfo.neighbours ) ): # WALL_NORTH
							chunk_copy[cw][ch] = "_"
						elif ( match( "-#-###-.-", neighbourInfo.neighbours ) ): # WALL_SOUTH
							chunk_copy[cw][ch] = "-"
						elif ( match( "..-.##-#-", neighbourInfo.neighbours ) ): # CORNER_NORTH_WEST
							chunk_copy[cw][ch] = "/"
						elif ( match( "-..##.-#-", neighbourInfo.neighbours ) ): # CORNER_NORTH_EAST
							chunk_copy[cw][ch] = "\\"
						elif ( match( "-#-.##..-", neighbourInfo.neighbours ) ): # CORNER_SOUTH_WEST
							chunk_copy[cw][ch] = "\\"
						elif ( match( "-#-##.-..", neighbourInfo.neighbours ) ): # CORNER_SOUTH_WEST
							chunk_copy[cw][ch] = "/"

					bytebuffer.append(byte)

			chunks_copy.append(chunk_copy)
			chunks_bytebuffer.append(bytebuffer)

		bb_cnt = 0
		for bb in chunks_bytebuffer:
			hex_str = hexify( "%s_chunk_%d" % (self.name,bb_cnt), bb)
			bb_cnt+=1

			dungfile.write(hex_str)

		dungfile.write( DUNG_FOOTER )
		dungfile.close()
		self.chunks = chunks_copy	

print("Running Gameboy's Dungeon Generator 1.0")
print("---------------------------------------")

if len(sys.argv) > 1 and sys.argv[1].startswith("-h"):
	print("Usage: dungeon_gen.py min_dungeon_width max_dungeon_width min_dungeon_height max_dungeon_height")
	print("Example: dungeon_gen.py 100 200 100 200")
	sys.exit(0)
else:

	extend( defaultDungeonGenerator, 
			{
				"numchunks"    : len(sys.argv) > 1 and int(sys.argv[1]) or  1,
				"minchunkdimW" : len(sys.argv) > 2 and int(sys.argv[2]) or 20,
 				"maxchunkdimW" : len(sys.argv) > 3 and int(sys.argv[3]) or 40,
				"minchunkdimH" : len(sys.argv) > 4 and int(sys.argv[4]) or 18,
				"maxchunkdimH" : len(sys.argv) > 5 and int(sys.argv[5]) or 36
			})

	print("Settings")
	print("  #Dungeons       : %s" % defaultDungeonGenerator["numdungs"])
	print("  #Dungeon.chunks : %s" % defaultDungeonGenerator["numchunks"])
	print("---------------------------------------")
	print("")

for d in range(defaultDungeonGenerator["numdungs"]):
	dung = Dungeon( "Dungeon_%d" % d )
	dung.Build(defaultDungeonGenerator["numchunks"])


	print("---------------------------------------")
	print("Pre-finalized dungeon:")
	dung.PrettyPrint()

	dung.Finalize()

	print("---------------------------------------")
	print("Finalized dungeon:")
	dung.PrettyPrint()


print("---------------------------------------")
print("All done.")