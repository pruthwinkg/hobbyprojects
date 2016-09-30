names = 'raymond rachel matthew'.split()
colors = 'red blue yellow green'.split()
cities = 'austin dallas chicago dallas austin chicago'.split()

# Show the colors in sequence ################################

for i in range(len(names)):
    print names[i].upper()

for name in names:
    print name.title()

# Show names and the numeric position of each name ###########

for i in range(1, len(names) + 1):
    print i, '-->', names[i-1]

for i, name in enumerate(names):
    print i, '-->', name

# Show the colors in reverse order ###########################    

for i in range(len(colors) - 1, -1, -1):
    print colors[i].upper()

for color in reversed(colors):
    print color.title()

# Show the names and colors pairwise, ignoring unmatched #####

nn, nc = len(names), len(colors)
n = nn if nn < nc else nc
for i in range(n):
    print names[i], '-->', colors[i]

n = min(len(names), len(colors))
for i in range(n):
    print names[i], '-->', colors[i]    

for name, color in zip(names, colors):
    print name, '-->', color

# Show the colors in alphabetical order title cased ##########

for color in sorted(colors):
    print color.title()

# Show the colors arranged by size of the color uppercased ###

for color in sorted(colors, key=len):
    print color.upper()

# Show the cities alphabetically without duplicates ##########

for city in sorted(set(cities)):
    print city.title()

