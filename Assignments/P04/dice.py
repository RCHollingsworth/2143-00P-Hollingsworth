from random import shuffle
class Die(object):

  def __init__(this, sides=None):
    if not sides:
      this.sides = 6
    else:
      if not isinstance(sides, int):
        print("No sides")
        sys.exit()
      this.sides = sides

  def roll(this):
    val = [x for x in range(this.sides)]

    shuffle(val)
    shuffle(val)
    shuffle(val)

    return val[0] + 1

  def __str__(this):
    return f"Sides:{this.sides}"



class Dice:

  def __init__(this, sides=None, num_dice=1):
    if not sides:
      this.sides = 6
    else:
      if not isinstance(sides, int):
        print("No sides")
        sys.exit()
      this.sides = sides

    this.dice = []

    for die in range(num_dice):
      this.dice.append(Die(sides))

  def __str__(this):
    s = "Dice:[\n    "
    for d in this.dice:
      s = s + str(d)
    s = s + "\n]\n"
    return s
    
  def roll(this):
    v = [x for x in range(this.sides)]

    shuffle(v)
    shuffle(v)
    shuffle(v)

    return v[0] + 1
    
  
  def rolling(die, runs=10, num_dice=1):
    print(f"Rolling {len(die.dice)} d {die.sides}")
    sum = 0
    max = 0
    min = 9999999
    for i in range(runs):
      print(f"Roll {i+1}:")
      for i in range(num_dice):
        val = die.roll()
        print(f" [{val}]")
        sum += val
        if val > max:
          max = val
        if val < min:
          min = val
    avg = int(sum/(runs*num_dice))
    print(f"Sum: {sum} Avergae: {avg} Max: {max} Min: {min}")